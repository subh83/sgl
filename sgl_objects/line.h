#ifndef _SGL_LINE_H
#define _SGL_LINE_H

#include <vector>
#include <GL/glut.h>

#include "../sgl_utils/stl_utils.h"
#include "../sgl_utils/gl_utils.h"
#include "object_base.h"
#include "point.h"

class sglLine : public sglObject
{
public:
    // +++++++++++++++++++++++++
    // Properties:
    //     Members derived from 'sglObject':
    //       - OPropertiesMap    this_OP;    // will contain all native object properties (OP)
    //       - LPropertiesMap    this_CP;    // temporary variable (can be private)
    //    sglObject already declares following object properties (OP):
    //       - visible, color, alpha, translation, scale
    //    sglObject already declares following link properties (LP):
    //       - visible
    
    // object (self) properties
    declare_OP (double, linewidth, 1.0);
    declare_OP (GLenum, linemode, (GLenum)GL_LINE_STRIP);
    
    // link (to children) properties
    declare_LP (bool, use_vertex_color, false); // Don't use vertex color by default
    declare_LP (double, vertex_color_weight, -1.0); // use alpha as weight if negative
    
    // non-object properties
    // none.
    
    // ------------------------------------------
    
    // Child pointers for ordered entry
    std::vector <sglPoint*>  points;
    
    // Local storage variables
    // none.
    
    // ------------------------------------------
    
    // Constructors for setting default properties
    
    sglLine (double r=1.0, double g=0.0, double b=0.0, double a=1.0, double w=1.0) 
            : sglObject (sglMake3vec(r,g,b), a)  { linewidth() = w; }
    
    sglLine (const std::vector<double>& p1, const std::vector<double>& p2,
                const std::vector<double>& c=sglMake3vec (1.0, 0.0, 0.0), double a=1.0, double w=1.0) 
            : sglObject (c, a) {
        sglPoint* pp1 = addPoint ( sglPoint (p1) );
        sglPoint* pp2 = addPoint ( sglPoint (p2) );
        linewidth() = w;
    }
    
    sglLine (double x0, double y0, double z0, double x1, double y1, double z1,
                double r=1.0, double g=0.0, double b=0.0, double a=1.0) : 
        sglLine ( sglMake3vec(x0,y0,z0), sglMake3vec(x1,y1,z1), sglMake3vec(r,g,b), a )
    { }
    
    // -------------------------
    // Mix parents' and self properties
    void computeProperties (CPropertiesMap&  parent_CP,  LPropertiesMap&  parent_child_LP) {
        // Use base class function to compute visible, color, alpha, translation
        sglObject::computeProperties (parent_CP, parent_child_LP);
        // --
        // Other object properties computation
        linewidth(this_CP) = linewidth() * scale(parent_CP, 1.0);
    }
    
    // +++++++++++++++++++++++++
    // -------------------------
    // functions for adding/removing/showing points
    
    sglPoint* addPoint (const sglPoint& p) {
        // Add as child first
        sglPoint* pp = addChild (p);
        // insert in local refernce variables
        points.push_back (pp);
        // set some child properties
        pp->visible() = false;
        pp->color() = color();
        // set some link properties if required
        // ...
        // return
        return (pp);
    }
    
    sglPoint* addPoint (sglPoint* pp) {
        // Add as child first
        pp = addChild (pp);
        // insert in local variables
        points.push_back (pp);
        // set some link properties if required
        // ...
        // return
        return (pp);
    }
    
    // TODO: removePoint, insertPoint
    
    // -------------------------
    // Functions to change link properties en-masse
    
    void use_vertex_color_all (bool use=true) {
        for (auto it=points.begin(); it!=points.end(); ++it) // iterate through the local vector storing the points
            use_vertex_color(*it) = use;
    }
    
    // +++++++++++++++++++++++++
    // -------------------------
    // Drawing function
    
    virtual void draw (CPropertiesMap&  parent_CP,  LPropertiesMap&  parent_child_LP) {
        computeProperties (parent_CP, parent_child_LP); // computes 'this_CP'
        // --
        if ( visible(this_CP) ) {
            glMatrixMode(GL_MODELVIEW);
            // 
            glLineWidth (linewidth(this_CP));
            glColor (color(this_CP), alpha(this_CP)); // set color from 'this_CP'
            glPushMatrix();
            glTranslated (translation()[0], translation()[1], translation()[2]); // Note: we don't use computed value since GL stacks 
	                                                                  // will take care of that when 'glTranslated' is called for parents
	            // Draw the line
	            glBegin (linemode(this_CP));
                    for (auto it=points.begin(); it!=points.end(); ++it) { // iterate through the local vector storing the points
                        if ( use_vertex_color(*it) ) {
                            double w = (vertex_color_weight(*it) < 0.0) ? (*it)->alpha() : vertex_color_weight(*it);
                            glColor ( (1.0-w) * color(this_CP) + w * (*it)->color(),  alpha(this_CP) ); // point color
                        }
                        else
                            glColor (color(this_CP), alpha(this_CP)); // self color
                        glVertex3f ((*it)->coords()[0], (*it)->coords()[1], (*it)->coords()[2]);
                    }
                glEnd();
                
                // draw the points - iterate through the same points stored in 'childObjects_p'
                for (auto it=childObjects_p.begin(); it!=childObjects_p.end(); ++it)
                    it->first->draw (this_CP, it->second);
            //
            glPopMatrix();
        }
    }
};

#endif
