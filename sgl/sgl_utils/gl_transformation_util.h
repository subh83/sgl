#ifndef _SGL_GL_TRANSFORMATION_UTIL_H
#define _SGL_GL_TRANSFORMATION_UTIL_H

#include <GL/glut.h>

class sglTransformation {
public:
    GLenum matrix_mode;
    
    void _push (void) { glMatrixMode(matrix_mode); glPushMatrix(); } // will be incorporated in push(). Not to be called by object classes.
    virtual void apply (void) { _push(); }
    void remove (void) { glMatrixMode(matrix_mode); glPopMatrix(); }
    
    // virtual destructor
    virtual ~sglTransformation() { }
};

// ================================

class sglRotate : public sglTransformation {
public:
    double angle, x, y, z;
    sglRotate (double ang, double xx, double yy, double zz, GLenum mode=GL_MODELVIEW) :
        angle(ang), x(xx), y(yy), z(zz) { matrix_mode = mode;}
    
    virtual void apply (void) { _push(); glRotated (angle, x, y, z); }
};


class sglTranslate : public sglTransformation {
public:
    double x, y, z;
    sglTranslate (double xx, double yy, double zz, GLenum mode=GL_MODELVIEW) :
        x(xx), y(yy), z(zz) { matrix_mode = mode;}
    
    virtual void apply (void) { _push(); glTranslated (x, y, z); }
};


class sglScale : public sglTransformation {
public:
    double x, y, z;
    sglScale (double xx, double yy, double zz, GLenum mode=GL_MODELVIEW) :
        x(xx), y(yy), z(zz) { matrix_mode = mode;}
    
    virtual void apply (void) { _push(); glScaled (x, y, z); }
};

#endif
