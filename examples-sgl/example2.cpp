#include <cmath>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <thread>
#include <chrono>
#include <algorithm>

#include "sgl/sgl.h"

#define rand_d (2.0 * ((double)rand()) / ((double)RAND_MAX) - 1.0)
#define rand_1 ( ((double)rand()) / ((double)RAND_MAX) )

int main(int argc, char *argv[])
{
    
    sglFigure myFig1; // create sglFigure instance
    myFig1.init (); // Display the figure
    
    // Add 5 random points
    srand (1);
    std::vector <sglPoint*> pts;
    for (int a=0; a<5; ++a)
        pts.push_back ( myFig1.addChild ( sglPoint (0.5*rand_d, 0.5*rand_d, 0.5*rand_d, rand_1, rand_1, rand_1) ) );
    
    std::cout << "press any key." << std::endl;
    myFig1.get_key();
    
    // -----------------------------------
    sglFigure myFig2; // create another sglFigure instance
    myFig2.init (); // Display the figure
    
    // Add 5 random points
    srand (2);
    for (int a=0; a<5; ++a)
        myFig2.addChild ( sglPoint (0.5*rand_d, 0.5*rand_d, 0.5*rand_d, rand_1, rand_1, rand_1) );
    
    // Add a closed line with shared points from myFig1
    sglLine* line = myFig2.addChild (sglLine ()); // empty line
    line->linewidth() = 3.0;
    line->linemode() = GL_LINE_LOOP;
    for (int a=0; a<5; ++a)
        line->addPoint (pts[a]); // note: this point is a pointer to a previously-created point
    
    // -----------------------------------
    sglFigure myFig3; // create another sglFigure instance
    myFig3.init (); // Display the figure
    
    sglBox* bx = myFig3.addChild ( sglBox (0,0,0, 1,1,1, 0.4,0.4,0.8, 0.6) ); // draw a box
    sglSphere* sph = myFig3.addChild ( sglSphere (0.5,0.5,2, 1.0, 1,0,0) ); // draw a sphere
    
    // -----------------------------------
    std::cout << "press any key." << std::endl; std::cin.get(); // Pause for keyboard input
}


