#ifndef _SGL_TEMPLATE_H  // TODO: Change name
#define _SGL_TEMPLATE_H  // TODO: Change name

#include <GL/glut.h>
// #include <vector>
// TODO: Other includes

#include "../sgl_utils/stl_utils.h"
#include "../sgl_utils/gl_utils.h"
#include "../sgl_utils/gl_transformation_util.h"

#include "object_base.h" // Necessary
// #include "point.h"
// TODO: include files for other child objects

class sglTemplate : public sglObject // TODO: Change class name
{
public:
    // +++++++++++++++++++++++++
    // Properties:
    //     Members derived from 'sglObject':
    //       - OPropertiesMap    this_OP;    // will contain all native object properties (OP)
    //       - CPropertiesMap    this_CP;    // temporary variable (can be private)
    //    sglObject already declares following object properties (OP):
    //       - visible, color, alpha, translation, scale
    //    sglObject already declares following link properties (LP):
    //       - visible
    
    // object (self) properties
    // TODO: Add.
    //       Syntax:  declare_OP (type_name, variable_name, default_value);
    //       Example: declare_OP (double, linewidth, 1.0);
    
    // link (to children) properties
    // TODO: Add.
    //       Syntax: declare_LP (type_name, variable_name, default_value);
    //       Example: declare_LP (bool, use_vertex_color, false); // Don't use vertex color by default
    
    // non-heritable object properties
    // TODO: Add.
    //       Example: std::string name;
    
    // ------------------------------------------
    
    // Child pointers for convenience
    // TODO: Add.
    //       Example: std::vector <sglPoint*>  points;
    
    // Local storage variables
    // TODO: Add.
    
    // ------------------------------------------
    
    // Constructors for setting default properties
    // TODO: Add.
    /* Examples:
    
    sglTemplate (double r=1.0, double g=0.0, double b=0.0, double a=1.0, double w=1.0) 
            : sglObject (sglMake3vec(r,g,b), a)  { linewidth() = w; }
    
    sglTemplate (const std::vector<double>& p1, const std::vector<double>& p2,
                const std::vector<double>& c=sglMake3vec (1.0, 0.0, 0.0), double a=1.0, double w=1.0) 
            : sglObject (c, a) {
        sglPoint* pp1 = addPoint ( sglPoint (p1) );
        sglPoint* pp2 = addPoint ( sglPoint (p2) );
        linewidth() = w;
    } */
    
    // -------------------------
    // Mix parents' and self properties
    void computeProperties (CPropertiesMap&  parent_CP,  LPropertiesMap&  parent_child_LP) {
        // Use base class function to compute visible, color, alpha
        sglObject::computeProperties (parent_CP, parent_child_LP);
        // --
        // Other object properties computation
        // TODO: Add.
        //      Example: linewidth(this_CP) = linewidth();
    }
    
    // +++++++++++++++++++++++++
    // -------------------------
    // functions for adding/removing/showing child objects
    // Convention: Each add function has two versions:
    //                      i. One that accepts reference -- will create a distinct copy of the child object
    //                     ii. One that accepts pointer -- will link to a previously-created child object
    
    // TODO: Add.
    
    /* Examples:
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
    } */
    
    // -------------------------
    // Functions to change link-to-child properties en-masse
    
    // TODO: Add.
    /* Examples:
    void use_vertex_color_all (bool use=true) {
        for (auto it=points.begin(); it!=points.end(); ++it) // iterate through the local vector storing the points
            use_vertex_color(*it) = use;
    } */
    
    // +++++++++++++++++++++++++
    // -------------------------
    // Drawing function
    
    virtual void draw (CPropertiesMap&  parent_CP,  LPropertiesMap&  parent_child_LP) {
        sgl_draw_function_head; // computes 'this_CP'
        // --
        if ( visible(this_CP) ) {
        
            // --
            // Apply transformations
            for (int a=transformations_p.size()-1; a>=0; --a)
                transformations_p[a]->apply();
            
            // --
            // TODO: Execute OpenGL core functions to draw self
            /* Example:
            glMatrixMode(GL_MODELVIEW);
            glLineWidth (linewidth(this_CP));
            glColor (color(this_CP), alpha(this_CP)); // set color from 'this_CP'
            glBegin (linemode(this_CP));
                for (auto it=points.begin(); it!=points.end(); ++it) // iterate through the local vector storing the points
                    glVertex3f ((*it)->coords()[0], (*it)->coords()[1], (*it)->coords()[2]);
            glEnd(); */
            
            // TODO: Draw children if required
            /* Example:
            for (auto it=childObjects_p.begin(); it!=childObjects_p.end(); ++it)
                it->first->draw (this_CP, it->second); */
            
            // --
            // Remove transformations
            for (int a=0; a<transformations_p.size(); ++a)
                transformations_p[a]->remove();
        }
    }
};

#endif
