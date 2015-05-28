#include <cmath>
#include <stdlib.h>
#include <iostream>
#include <thread>
#include <chrono>

#include "../sgl.h"

#define PI 3.14159265359

int main(int argc, char *argv[])
{
    sglViewProperties prop; // figure properties
    prop.height = 400; // set properties if required
    sglFigure myFig1 (prop); // create OpenGL figure instance with desired properties
    myFig1.init (); // Display the figure
    
    // -----------------------------------------
    
    // Add lines and store the handles to the lines
    std::vector<sglLine*> linesA;
    double dth = 2*PI/100;
    for (double th=0.0; th<2*PI; th+=dth) {
        sglLine* pointer_to_line_object = myFig1.addObject( sglLine (cos(th),sin(th),0.0, cos(th+dth),sin(th+dth),0.0) );
        linesA.push_back (pointer_to_line_object);
    }
    /* sglLine constructor: sglLine (double x0, double y0, double z0, double x1, double y1, double z1,
                            std::vector<double> color={0.0,0.0,0.0,1.0}, double width=2.0, std::string style="flat") */
    
    std::cout << "press any key. "; std::cin.get(); // Pause for keyboard input
    
    // Create and show another window
    sglFigure myFig2;
    myFig2.init ();
    
    // Add lines to the new window
    std::vector<sglLine*> linesB;
    dth = 2*PI/10;
    for (double th=0.0; th<2*PI; th+=dth) {
        auto pointer_to_line_object = myFig2.addObject( sglLine (cos(th),sin(th),sin(th/4.0), cos(th+dth),sin(th+dth),sin((th+dth)/4.0)) );
        linesB.push_back (pointer_to_line_object);
        pointer_to_line_object->width = th; // set a property for the line.
    }
    
    // Change colors of the lines in the first figure to create an animation
    while (true) {
        for (auto it=linesA.begin(); it!=linesA.end(); ++it) {
            (*it)->color = sglMakeColor (((double)rand())/((double)RAND_MAX), ((double)rand())/((double)RAND_MAX), 
                                            ((double)rand())/((double)RAND_MAX), 1.0);  // random color
        }
        myFig1.flush(); // flush the changes
        std::this_thread::sleep_for (std::chrono::milliseconds(1000)); // sleep
    }
    
    std::cout << "press any key. "; std::cin.get(); // Pause for keyboard input
}


