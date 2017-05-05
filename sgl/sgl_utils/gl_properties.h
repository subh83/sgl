#ifndef _SGL_GL_PROPERTIES_H
#define _SGL_GL_PROPERTIES_H

#include <vector>
#include <GL/glut.h>


std::vector<GLenum> light_names = {GL_LIGHT0, GL_LIGHT1, GL_LIGHT2, GL_LIGHT3, GL_LIGHT4, GL_LIGHT5};

class sglLight {
public:
    std::vector<GLfloat> ambient;
    std::vector<GLfloat> diffuse;
    std::vector<GLfloat> specular;
    
    std::vector<GLfloat> position;
    std::vector<GLfloat> spot_direction;
    
    sglLight 
    ( std::vector<GLfloat> la={0.0,0.0,0.0,1.0},  std::vector<GLfloat> ld={0.5,0.5,0.5,1.0}, std::vector<GLfloat> ls={0.8,0.8,0.8,1.0},
      std::vector<GLfloat> lpos={0.0,0.0,-5.0,0.0} )
        : ambient(la), diffuse(ld), specular(ls), position(lpos) { }
};


#endif
