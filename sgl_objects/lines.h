#ifndef _SGL_LINES_H
#define _SGL_LINES_H

#include <vector>
#include <string>
#include <GL/glut.h>

#include "object_base.h"

class sglLine : public sglObject {
public:
    std::vector<double> x, y, z;
    std::vector<double> color;
    double width;
    std::string style, pattern;
    
    // constructors
    sglLine (double x0, double y0, double z0, double x1, double y1, double z1,
                std::vector<double> c={0.0,0.0,0.0,1.0}, double w=2.0, std::string s="flat")
    {
        x.push_back (x0); x.push_back (x1);
        y.push_back (y0); y.push_back (y1);
        z.push_back (z0); z.push_back (z1);
        
        color = {0.0,0.0,0.0,1.0};
        for(int a=0; a<c.size(); ++a) color[a] = c[a];
        width = w; style = s;
    }
    
    // drawing functions
    void draw (void);
};

// ====================================================

void sglLine::draw (void)
{
    if (style == "flat") {
            glLineWidth (width);
            glColor4f (color[0], color[1], color[2], color[3]);
            glBegin(GL_LINES);
                for (int a=0; a<x.size(); ++a)
                    glVertex3f (x[a], y[a], z[a]);
            glEnd();
            //printf ("\tdrawn a line with %d points (%f,%f,%f)-(%f,%f,%f)-... color=(%f,%f,%f,%f)\n", x.size(), x[0],y[0],z[0], x[1],y[1],z[1], color[0],color[1],color[2],color[3]);
            
            /* GLUquadric* sphere_quad = gluNewQuadric();
	        glMatrixMode(GL_MODELVIEW);
	        glPushMatrix();
		        glTranslated(0.0, 0.0, 0.0);
		        gluSphere(sphere_quad, 1.0, 10, 10);
	        glPopMatrix();
	        gluDeleteQuadric(sphere_quad); */
    }
}


#endif
