#ifndef _SGL_SPHERE_H
#define _SGL_SPHERE_H

#include <vector>
#include <GL/glut.h>

#include "sgl/sgl_utils/stl_utils.h"
#include "sgl/sgl_utils/gl_utils.h"
#include "sgl/sgl_objects/object_base.h"

// --------------------------------------------

class sglSphere : public sglObject
{
public:
    // +++++++++++++++++++++++++
    // Properties:
    //     Members derived from 'sglObject':
    //       - OPropertiesMap    this_OP;    // will contain all native object properties (OP)
    //       - CPropertiesMap    this_CP;  // temporary variable (can be private)
    //    sglObject already declares following object properties (OP):
    //       - visible, color, alpha
    //    sglObject already declares following link properties (LP):
    //       - visible
    
    // object properties (generate functions for quick access)
    declare_OP (double, radius, 0.02);
    
    // non-heritable object properties
    declare_OP (std::vector<double>, coords, sglMake3vec(0.0,0.0,0.0) );
    declare_OP (int, slices, 50 );
    declare_OP (int, stacks, 25 );
    
    // Aiases
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
    
    sglSphere (const std::vector<double>& _coords=sglMake3vec (0.0, 0.0, 0.0),  double rad=0.02,
                    const std::vector<double>& _color=sglMake3vec (1.0, 0.0, 0.0), double a=1.0,
                    int _slices=50, int _stacks=25) 
            : sglObject (_color, a) {
        radius() = rad;
        // --
        coords() = _coords;
        slices() = _slices;
        stacks() = _stacks;
        // --
        sphere_quad = NULL;
    }
    
    sglSphere (double x, double y, double z, double rad=0.02, double r=1.0, double g=0.0, double b=0.0, double a=1.0) : 
        sglSphere (sglMake3vec(x,y,z), rad, sglMake3vec(r,g,b), a) { }
    
    // -------------------------
    // Mix parents' and self properties
    void computeProperties (CPropertiesMap&  parent_CP,  LPropertiesMap&  parent_child_LP) {
        // Use base class function to compute visible, color, alpha
        sglObject::computeProperties (parent_CP, parent_child_LP);
        // Other object properties computation
        radius(this_CP) = radius();
    }
    
    // +++++++++++++++++++++++++
    // -------------------------
    // Drawing function
    
    virtual void draw (CPropertiesMap&  parent_CP,  LPropertiesMap&  parent_child_LP) {
        sgl_draw_function_head; // computes 'this_CP'
        // --
        if ( visible (this_CP) ) {
            // --
            // Apply transformations
            for (int a=transformations_p.size()-1; a>=0; --a)
                transformations_p[a]->apply();
            // --
            if (!sphere_quad) {
                sphere_quad = gluNewQuadric();
            }
            glColor (color(this_CP), alpha(this_CP)); // set color from 'this_CP'
            // 
            glMatrixMode(GL_MODELVIEW);
            glPushMatrix();
            glTranslated (coords()[0], coords()[1], coords()[2]); // Note: we don't use computed value since GL stacks 
                                                                  // will take care of that when 'glTranslated' is called for parents
	            gluSphere(sphere_quad, radius(this_CP), slices(), stacks());
            glPopMatrix();
            // --
            // Remove transformations
            for (int a=0; a<transformations_p.size(); ++a)
                transformations_p[a]->remove();
        }
    }
    
    // +++++++++++++++++++++++++
    // ---------------------
    // Destructor
    ~sglSphere () {
        if (sphere_quad)
            gluDeleteQuadric(sphere_quad);
        // ~sglObject() takes care of destroying the children
    }
};

#endif
