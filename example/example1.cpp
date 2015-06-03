#include <cmath>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <thread>
#include <chrono>

#include "../sgl.h"

#define PI 3.14159265359
#define rand_d (2.0 * ((double)rand()) / ((double)RAND_MAX) - 1.0)

int main(int argc, char *argv[])
{
    
    sglFigure myFig1; // create sglFigure instance
    myFig1.width = 700; myFig1.height = 700; // set properties if required
    myFig1.init (); // Display the figure
    
    // -----------------------------------
    // draw lines reprsenting the axes
    sglLine* lnX = myFig1.addChild ( sglLine (-1.5,0.0,0.0, 1.5,0.0,0.0) );
    sglLine* lnY = myFig1.addChild ( sglLine (0.0,-1.5,0.0, 0.0,1.5,0.0, 0.0,1.0,0.0) ); // green
    sglLine* lnZ = myFig1.addChild ( sglLine (0.0,0.0,-1.5, 0.0,0.0,1.5) );
                                     // ^^^^   x0, y0, z0,   x1, y1, z1,   r,  g,  b
    // set color of x axis
    lnX->color() = sglMake3vec (0.0,0.0,1.0);
    
    std::cout << "press any key." << std::endl;
    myFig1.get_key(); // Pause for keyboard input on figure
    
    // change color of points on the lines and use those
    std::vector<double> white = sglMake3vec (1.0, 1.0, 1.0);
    lnX->use_vertex_color (lnX->points[0]) = true;  // Notifies that the point color be used
    lnX->points[0]->color() = white;                // Sets the point color
    lnY->use_vertex_color (lnY->points[0]) = true;
    lnY->points[0]->color() = white;
    lnZ->use_vertex_color (lnZ->points[0]) = true;
    lnZ->points[0]->color() = white;
    
    std::cout << "press any key." << std::endl;
    myFig1.get_key();
    
    // -----------------------------------
    // Draw a random chain of lines
    sglLine* chain = myFig1.addChild ( sglLine (0.0,0.0,1.0, 1.0, 3.0) );  // empty line (with properties)
                                     // ^^^^      r,  g,  b,  a,  width
    for (int a=0; a<100; ++a)
        chain->addPoint ( sglPoint (0.5*rand_d, 0.5*rand_d, 0.5*rand_d) );
    
    // Direct line to use the point colors
    chain->use_vertex_color_all();
    
    // Randomly change the colors
    while (true) {
        for (auto it=chain->points.begin(); it!=chain->points.end(); ++it) { // iterate through the points in the line
            (*it)->color() = sglMake3vec ( 0.5*(rand_d+1.0), 0.5*(rand_d+1.0), 0.5*(rand_d+1.0)  );  // random color
        }
        myFig1.flush(); // flush the changes
        std::this_thread::sleep_for (std::chrono::milliseconds(100)); // sleep
    }
    
    std::cout << "press any key." << std::endl; std::cin.get(); // Pause for keyboard input
}


