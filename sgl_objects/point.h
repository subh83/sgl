#ifndef _SGL_LINES_H
#define _SGL_LINES_H

#include <vector>
#include <GL/glut.h>

#include "../sgl_utils/stl_utils.h"
#include "../sgl_utils/gl_utils.h"
#include "object_base.h"

// --------------------------------------------

class sglPoint : public sglObject
{
public:
    // +++++++++++++++++++++++++
    // Properties:
    //     Members derived from 'sglObject':
    //       - OPropertiesMap    this_OP;    // will contain all native object properties (OP)
    //       - CPropertiesMap    this_CP;  // temporary variable (can be private)
    //    sglObject already declares following object properties (OP):
    //       - visible, color, alpha, translation, scale
    //    sglObject already declares following link properties (LP):
    //       - visible
    
    // object properties (generate functions for quick access)
    declare_OP (double, radius, 0.02);
    
    // non-object properties
    // none.
    
    // Aiases
    std::vector<double>&  coords() { return translation(); }  // alias.
    double& x() { return coords()[0]; }
    double& y() { return coords()[1]; }
    double& z() { return coords()[2]; }
    
    // ------------------------------------------
    
    // Child pointers for reference and associated data storage
    // none.
    
    // Local storage variables
    GLUquadric* sphere_quad;
    
    // ------------------------------------------
    
    // Constructors for setting default properties
    
    sglPoint (const std::vector<double>& _coords=sglMake3vec (0.0, 0.0, 0.0), const std::vector<double>& _color=sglMake3vec (1.0, 0.0, 0.0), 
                double a=1.0, double rad=0.02) 
            : sglObject (_color, a) {
        radius() = rad;
        // --
        translation() = _coords;
        // --
        sphere_quad = NULL;
    }
    
    sglPoint (double x, double y, double z, double r=1.0, double g=0.0, double b=0.0, double a=1.0, double rad=0.02) : 
        sglPoint (sglMake3vec(x,y,z), sglMake3vec(r,g,b), a, rad) { }
    
    // -------------------------
    // Mix parents' and self properties
    void computeProperties (CPropertiesMap&  parent_CP,  LPropertiesMap&  parent_child_LP) {
        // Use base class function to compute visible, color, alpha, translation (a.k.a. coords)
        sglObject::computeProperties (parent_CP, parent_child_LP);
        // Other object properties computation
        radius(this_CP) = radius() * scale(parent_CP, 1.0);
    }
    
    // +++++++++++++++++++++++++
    // -------------------------
    // Drawing function
    
    virtual void draw (CPropertiesMap&  parent_CP,  LPropertiesMap&  parent_child_LP) {
        computeProperties (parent_CP, parent_child_LP); // computes 'this_CP'
        // --
        if ( visible (this_CP) ) {
            if (!sphere_quad) {
                sphere_quad = gluNewQuadric();
            }
            glMatrixMode(GL_MODELVIEW);
            //
            glColor (color(this_CP), alpha(this_CP)); // set color from 'this_CP'
            glPushMatrix();
            glTranslated (coords()[0], coords()[1], coords()[2]); // Note: we don't use computed value since GL stacks 
                                                                  // will take care of that when 'glTranslated' is called for parents
	            gluSphere(sphere_quad, radius(this_CP), 10, 10);
            glPopMatrix();
        }
    }
    
    // +++++++++++++++++++++++++
    // ---------------------
    // Destructor
    ~sglPoint () {
        if (sphere_quad)
            gluDeleteQuadric(sphere_quad);
        // ~sglObject() takes care of destroying the children
    }
};

#endif
