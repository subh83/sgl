#ifndef _SGL_OBJ_BASE_H
#define _SGL_OBJ_BASE_H

class sglFigure; //declaration

class sglObject {
public:
    bool visible;
    sglFigure* figure_p;
    
    sglObject() : visible(true) { }
    virtual void draw (void) { printf("\tdrawn nothing!\n"); }
    // set properties
    /* virtual void setProperty (std::string name, bool value) { }
    virtual void setProperty (std::string name, int value) { }
    virtual void setProperty (std::string name, double value) { } */
};

#endif
