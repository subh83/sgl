#ifndef _SGL_GL_UTILS_H
#define _SGL_GL_UTILS_H

#include <vector>
#include <GL/glut.h>

void glColor (std::vector<double> color, double alpha) {
    if (alpha >= 0.0) 
        glColor4f (color[0], color[1], color[2], alpha);
    else 
        glColor3f (color[0], color[1], color[2]);
}

#endif
