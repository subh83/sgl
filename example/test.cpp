#include <cmath>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <thread>
#include <chrono>

#include "../sgl.h"

#define PI 3.14159265359

int main(int argc, char *argv[])
{
    sglViewProperties prop; // figure properties
    prop.height = 400; // set properties
    prop.width = 400; 
    
    // -----------------------------------------
    
    sglFigure myFig1 (prop); // create OpenGL figure instance
    myFig1.init (); // Display the figure
    
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
    
    // -----------------------------------------
    
    sglFigure myFig2; // Create and show another figue window (uses default properties)
    myFig2.init ();
    
    // Add lines to the new window
    auto Xaxis = myFig2.addObject( sglLine (1.0,0.0,0.0, -1.0,0.0,0.0, {0.0,0.0,1.0,1.0}));
    auto Yaxis = myFig2.addObject( sglLine (0.0,1.0,0.0, 0.0,-1.0,0.0, {0.0,0.0,1.0,1.0}));
    auto Zaxis = myFig2.addObject( sglLine (0.0,0.0,1.0, 0.0,0.0,-1.0, {0.0,0.0,1.0,1.0}));
    
    // -----------------------------------------
    
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


