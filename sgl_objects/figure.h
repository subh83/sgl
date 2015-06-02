#ifndef _SGL_FIGURE_H
#define _SGL_FIGURE_H

#include <vector>
#include <unordered_map>
#include <string>
#include <X11/Xlib.h>
#include <GL/glut.h>
#include <pthread.h>
#include <thread>
#include <chrono>

#include "glt_zpr/zpr.h"

#include "../sgl_utils/stl_utils.h"
#include "object_base.h"

// --------------------------------------------

class sglFigure : public sglObject
{
public:
    // +++++++++++++++++++++++++
    // Properties:
    //     Members derived from 'sglObject':
    //       - OPropertiesMap    this_OP;    // will contain all native object properties (OP)
    //       - OPropertiesMap    this_CP;  // temporary variable (can be private)
    
    // non-object properties
    std::string name;
    double width, height;
    // Properties specific to figure (non-object)
    bool initiated;
    int winID;
    // Status defining variables
    bool waiting_for_keypress; unsigned char pressed_key;
    
    // Static variables specific to figure
    static bool  glutInitiated;
    static bool  glutMainLoopCalled;
    static int   sglThreadID;
    static pthread_t  sglThreadStruct;
    
    // Constructors for setting default properties
    sglFigure (std::string nm="<untitled>") : sglObject(sglMake3vec (1.0, 1.0, 1.0), 1.0) {
        name = nm;
        width = 600;
        height = 600;
        initiated = false;
        winID = -1;
        // --
        waiting_for_keypress = false;
    }
    
    // -------------------------
    // Mix parents' and self properties
    void computeProperties (CPropertiesMap&  parent_CP,  LPropertiesMap&  parent_child_LP) {
        sglObject::computeProperties (parent_CP, parent_child_LP);
    }
    
    // +++++++++++++++++++++++++
    // -------------------------
    // Drawing function
    
    virtual void draw (CPropertiesMap&  parent_CP,  LPropertiesMap&  parent_child_LP);
    
    // +++++++++++++++++++++++++
    // ---------------------
    // Destructor
    ~sglFigure ();
    
    // ---------------------
    // Functions specific to figure
    void init (int argc=0, char *argv[]=NULL);
    void flush (void);
    // --
    unsigned char get_key (void);
};

// ===========================================
// Variables and functions specefic to figure

bool sglFigure::glutInitiated = false;
bool sglFigure::glutMainLoopCalled = false;
int sglFigure::sglThreadID;
pthread_t sglFigure::sglThreadStruct;

// ------------------------------------------

std::unordered_map <int, sglFigure*> allGlFigures;

// ===========================================
// Global gl unctions

void _globalDisplayFunction (void) {
    int winID = glutGetWindow();
    
    if (allGlFigures.find(winID) != allGlFigures.end()) {
        allGlFigures[winID]->draw (sglFigure::empty_CP, sglFigure::empty_LP);
        // printf ("Drawn %d objects in window %d.\n", allGlFigures[winID]->childObjects_p.size(), winID);
    }
}

// --------------------------

void _globalKeyFunction (unsigned char key, int x, int y){
    int winID = glutGetWindow();
    
    if (allGlFigures.find(winID) != allGlFigures.end()) {
        if (allGlFigures[winID]->waiting_for_keypress) {
            allGlFigures[winID]->waiting_for_keypress = false;
            allGlFigures[winID]->pressed_key = key;
        }
    }
}

// ===========================================
// definitions of members

void sglFigure::draw (CPropertiesMap&  parent_CP,  LPropertiesMap&  parent_child_LP) {
    computeProperties (parent_CP, parent_child_LP); // computes 'this_CP'
    // --
    if ( visible(this_CP) ) {
        // Clear figure.
        std::vector<double>& c = color();
	    glClearColor (c[0], c[1], c[2], 0.0f);
	    glClearDepth (1.0f);
        if ( alpha() >= 0.0) {
            glEnable (GL_BLEND); // Add alpha blending
            glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        }
        glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // Draw the children
        for (auto it=childObjects_p.begin(); it!=childObjects_p.end(); ++it)
            it->first->draw (this_CP, it->second);
        // swap buffer
        glutSwapBuffers ();
    }
}

// -------------------------------

sglFigure::~sglFigure () {
    allGlFigures.erase (winID);
    // ~sglObject() takes care of destroying the children
    // TODO: Close window
}

// -------------------------------

void sglFigure::init (int argc, char *argv[]) {
    if (initiated) // nothing to initiate
        return;
    
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
	if (alpha() >= 0.0) {
    	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);  //(GLUT_SINGLE|GLUT_RGBA);
        /*glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_BLEND);*/
        //glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
        //glEnable(GL_BLEND); // Add alpha blending
        //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }
    else
        glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
    
    glutInitWindowSize (width, height);
    if (name == "<untitled>")
        name = "OpenGL window " + std::to_string (allGlFigures.size());
	winID = glutCreateWindow (name.c_str());
	
	allGlFigures[winID] = this;
    
    if (alpha() >= 0.0) {
        glEnable(GL_BLEND); // Add alpha blending
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }
    
	glShadeModel(GL_SMOOTH);
	//glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	std::vector<double>& c = color();
	glClearColor (c[0], c[1], c[2], 0.0f);
	glClearDepth (1.0f);
	
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
	glutKeyboardFunc(_globalKeyFunction);
	
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


// -------------------------------

void sglFigure::flush (void) {
    int oldWinID = glutGetWindow();
    glutSetWindow (winID);
    glutPostRedisplay (); //glFlush();
    glutSetWindow (oldWinID);
}

// -------------------------------

unsigned char sglFigure::get_key (void) {
    waiting_for_keypress = true;
    while (waiting_for_keypress) {
        std::this_thread::sleep_for (std::chrono::milliseconds(100)); // sleep
    }
    return (pressed_key);
}

#endif
