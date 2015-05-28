#ifndef _SIMPLE_GL_BASE_H
#define _SIMPLE_GL_BASE_H

#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include <X11/Xlib.h>
#include <GL/glut.h>
#include <pthread.h>

#include "glt_zpr/zpr.h"
#include "sgl_objects/object_base.h"

// Properties of the OpenGL window:

class sglViewProperties {
public:
    int width, height;
    bool alpha;
    std::string win_name;
    
    sglViewProperties() : width(600), height(600), alpha (true), win_name("") { }
};

// ------------------------------

/*class sglColor {
public:
    std::vector<double> c;
    sglColor (double r, double g, double b);
    sglColor (double r, double g, double b, double a);
};*/


// -------------------------------------

// Objects 

//class 

/* // Sending requests to the OpenGL window

struct sglRequests {
public:
    bool saveImage, showSurfaces, showLabels, showTrajectories;
    std::vector<int> trajectoriesToDraw;
    
    sglRequests() : saveImage(false), showSurfaces(true), showTrajectories(true) { }
}; */

// ==========================================

class sglFigure
{
public:
    // Member variables for figure properties
    sglViewProperties properties;
    int winID;
    bool initiated;
    // objects
    std::unordered_set<sglObject*> objects;
    
    // Static variabes for all windows
    // void (*drawing_callback)(void);
    static bool glutInitiated;
    static bool glutMainLoopCalled;
    static int sglThreadID;
    static pthread_t sglThreadStruct;
    
    // Figure/window functions
    sglFigure (const sglViewProperties& p=sglViewProperties()) : properties(p), initiated(false) {  }
    void setProperties (sglViewProperties& p) { properties = p; }
    void init (int argc=0, char *argv[]=NULL);
    void flush (void);
    ~sglFigure(); // destructor dereferences the global
    
    // Object functions
    //sglObject* addObject (const sglObject& obj);
    template <class objType> objType* addObject (const objType& obj); // objType must be derived from sglObject
    
    void removeObject (sglObject* obj_p);
    
    // The main function for drawing
    void draw_objects (void);
    
};

// -------------------------------------

void _globalDisplayFunction (void);

// ================================================================

bool sglFigure::glutInitiated = false;
bool sglFigure::glutMainLoopCalled = false;
int sglFigure::sglThreadID;
pthread_t sglFigure::sglThreadStruct;

// -------------------------------------

std::unordered_map <int, sglFigure*> allGlFigures;

// -------------------------------------

// definitions

void sglFigure::init (int argc, char *argv[]) {
    if (!glutInitiated) {
        XInitThreads();
        glutInit(&argc, argv);
        glutInitiated = true;
    }
    
    static GLfloat light_ambient[]  = { 0.0, 0.0, 0.0, 1.0 };
    static GLfloat bright_light_ambient[]  = { 1.0, 1.0, 1.0, 1.0 };
    static GLfloat light_diffuse[]  = { 0.5, 0.5, 0.5, 1.0 };
    static GLfloat light_specular[] = { 0.2, 0.2, 0.2, 1.0 };

    static GLfloat mat_ambient[]    = { 0.7, 0.7, 0.7, 1.0 };
    static GLfloat mat_diffuse[]    = { 0.8, 0.8, 0.8, 1.0 };
    static GLfloat mat_specular[]   = { 1.0, 1.0, 1.0, 1.0 };
    static GLfloat high_shininess[] = { 100.0 };
    
	//glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE); //glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	//glutInitWindowSize(OPENGL_WIN_SIZE, OPENGL_WIN_SIZE);
	if (properties.alpha) {
    	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);  //(GLUT_SINGLE|GLUT_RGBA);
        /*glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_BLEND);*/
        //glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
        //glEnable(GL_BLEND); // Add alpha blending
        //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }
    else
        glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
    
    glutInitWindowSize (properties.width, properties.height);
    if (properties.win_name == "")
        properties.win_name = "OpenGL window " + std::to_string (allGlFigures.size());
	winID = glutCreateWindow (properties.win_name.c_str());
	
	allGlFigures[winID] = this;
    
    if (properties.alpha) {
        glEnable(GL_BLEND); // Add alpha blending
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }
    
	glShadeModel(GL_SMOOTH);
	//glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glClearColor(1.0f,1.0f,1.0f,0.0f);
	glClearDepth(1.0f);
	
	//glViewport(-2.0, -2.0, 4.0, 4.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glRotated(90.0, 1.0, 0.0, 0.0);
	
	//gluPerspective(30.0, 1.0, 0.1, 100.0); // perspective proj.
	glOrtho(-2.0, 2.0, -2.0, 2.0, 0.1, 100.0);
	//glScalef(1.0f, -1.0f, 1.0f);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glScalef(-1.0f, 1.0f, 1.0f);
	gluLookAt (	0.0, 0.0, -5.0, // camera location
				0.0, 0.0, 0.0, // look at point
				0.0, 1.0, 0.0 ); // camera "up" direction
    
	glutDisplayFunc (_globalDisplayFunction);
	glutIdleFunc (_globalDisplayFunction);
	//glutKeyboardUpFunc(KeyDownHandlerOpenGL);
	
	zprReferencePoint[0] = 0.0; zprReferencePoint[1] = 0.0; zprReferencePoint[2] = 0.0; 
	zprInit(); 
	//zprSelectionFunc(drawAxes);     /* Selection mode draw function */
	//zprPickFunc(pick);              /* Pick event client callback   */
	
	// Setting up lights
	
    // LIGHT0
    static GLfloat light_position0[] = { 0.0, 0.0, -5.0, 0.0 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position0);
	
	// LIGHT1
	static GLfloat light_position1[] = { 0.0, 0.0, 5.0, 0.0 };
	glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT1, GL_POSITION, light_position1);

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

    /* glEnable(GL_CULL_FACE); //<-- missing
    glCullFace(GL_BACK); */
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, bright_light_ambient);
    //glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light_ambient);
    
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	
	if (!glutMainLoopCalled) { // active
        glutMainLoopCalled = true;
        sglThreadID = pthread_create (&sglThreadStruct, NULL, 
                                        [](void* d) -> void* { glutMainLoop(); }, 
                                                NULL);
    }
	
	// -------------
	initiated = true;
}

// -------------------------

sglFigure::~sglFigure () {
    for (auto it=objects.begin(); it!=objects.end(); ++it)
        delete (*it);
    allGlFigures[winID] = NULL;
}

// -------------------------

template <class objType> // objType must be derived from sglObject
objType* sglFigure::addObject (const objType& obj) {
    objType* new_obj = new objType (obj); // make copy
    new_obj->figure_p = this;
    objects.insert (new_obj); // type casting
    return (new_obj);
}

void sglFigure::removeObject (sglObject* obj_p) {
    objects.erase (obj_p);
    delete obj_p;
}

void sglFigure::draw_objects (void) {
    for (auto it=objects.begin(); it!=objects.end(); ++it)
        (*it)->draw();
}

// -----------------------------

void sglFigure::flush (void) {
    int oldWinID = glutGetWindow();
    glutSetWindow(winID);
    glutPostRedisplay(); //glFlush();
    glutSetWindow(oldWinID);
}

// ======================================

//bool sglGlobalDisplayFunctionCalled = false;

void _globalDisplayFunction (void)
{
    /* if (sglGlobalDisplayFunctionCalled)
        return;
    sglGlobalDisplayFunctionCalled = true; */
    
    int winID = glutGetWindow();
    //printf ("Current winID=%d (mem = %x, number of objects = %d)\n", winID, allGlFigures[winID], allGlFigures[winID]->objects.size());
    
    if (allGlFigures[winID]) {
        // clear
        if (allGlFigures[winID]->properties.alpha) {
            glEnable(GL_BLEND); // Add alpha blending
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        }
	    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        
        // draw
        allGlFigures[winID]->draw_objects();
        // printf ("Drawn %d objects in window %d.\n", allGlFigures[winID]->objects.size(), winID);
        
        // swap buffer
        glutSwapBuffers();
    }
    
    // sglGlobalDisplayFunctionCalled = false;
}

#endif
