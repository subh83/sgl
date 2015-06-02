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
    
    // draw axes
    sglLine* lnX = myFig1.addChild ( sglLine (-2.0,0.0,0.0, 2.0,0.0,0.0) );
    sglLine* lnY = myFig1.addChild ( sglLine (0.0,-2.0,0.0, 0.0,2.0,0.0, 0.0,1.0,0.0) );
    sglLine* lnZ = myFig1.addChild ( sglLine (0.0,0.0,-2.0, 0.0,0.0,2.0) );
                                     // ^^^^   x0, y0, z0,   x1, y1, z1,   r,  g,  b
    // set color of x axis
    lnX->color() = sglMake3vec (0.0,0.0,1.0);
    
    std::cout << "press any key." << std::endl; std::cin.get(); // Pause for keyboard input
    
    // change color of points on the line and use those
    std::vector<double> white = sglMake3vec (1.0, 1.0, 1.0);
    lnX->use_vertex_color (lnX->points[0]) = true;
    lnX->points[0]->color() = white;
    lnY->use_vertex_color (lnY->points[0]) = true;
    lnY->points[0]->color() = white;
    lnZ->use_vertex_color (lnZ->points[0]) = true;
    lnZ->points[0]->color() = white;
    
    std::cout << "press any key." << std::endl; std::cin.get(); // Pause for keyboard input
    
    // Draw a random chain of lines
    sglLine* chain = myFig1.addChild ( sglLine (0.0,0.0,1.0, 1.0, 3.0) );  // empty line (with properties)
                                     // ^^^^      r,  g,  b,  a,  width
    for (int a=0; a<100; ++a)
        chain->addPoint ( sglPoint (rand_d, rand_d, rand_d) );
    
    myFig1.flush ();
    std::cout << "press any key." << std::endl; std::cin.get(); // Pause for keyboard input
}


