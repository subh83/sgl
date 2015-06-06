#include <cmath>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <thread>
#include <chrono>
#include <algorithm>

#include "../sgl.h"

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
    std::cout << "press any key." << std::endl; std::cin.get(); // Pause for keyboard input
}


