#include <cmath>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <thread>
#include <chrono>
#include <algorithm>

#include "sgl/sgl.h"

#define rand_d (2.0 * ((double)rand()) / ((double)RAND_MAX) - 1.0)

int main(int argc, char *argv[])
{
    
    sglFigure myFig1; // create sglFigure instance
    myFig1.width = 700; myFig1.height = 700; // set properties if required
    myFig1.init (); // Display the figure
    
    // -----------------------------------
    // -----------------------------------
    // draw lines representing the axes
    printf("[draw lines representing the axes]\n");
    
    sglLine* lnX = myFig1.addChild ( sglLine (-1.5,0.0,0.0, 1.5,0.0,0.0) );
    sglLine* lnY = myFig1.addChild ( sglLine (0.0,-1.5,0.0, 0.0,1.5,0.0, 0.0,1.0,0.0) ); // green
    sglLine* lnZ = myFig1.addChild ( sglLine (0.0,0.0,-1.5, 0.0,0.0,1.5) );
                                     // ^^^^   x0, y0, z0,   x1, y1, z1,   r,  g,  b
    // set color of x axis
    lnX->color() = sglMake3vec (0.0,0.0,1.0);
    
    std::cout << "press any key." << std::endl;
    myFig1.get_key(); // Pause for keyboard input on figure
    
    // -----------------------------------
    // -----------------------------------
    // change color of points on the lines and use those
    printf("[change color of points on the axes lines and use those]\n");
    
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
    // -----------------------------------
    // Draw a random chain of lines
    printf ("[draw a random chain of lines]\n");
    
    sglLine* chain = myFig1.addChild ( sglLine (0.0,0.0,1.0, 1.0, 3.0) );  // empty line (with properties)
                                     // ^^^^      r,  g,  b,  a,  width
    // Add 100 points to the line
    for (int a=0; a<100; ++a)
        chain->addPoint ( sglPoint (0.5*rand_d, 0.5*rand_d, 0.5*rand_d) );
    
    // Apply a translation (first) and a rotation (second) to this lines object
    auto chain_translation = chain->addTransformation ( sglTranslate(0.0, 0.0, 0.0) );
    auto chain_rotation = chain->addTransformation ( sglRotate(0.0, 0.0, 0.0, 1.0) );
                                                    // ^^^^  angle,   x,   y,   z
    
    // Direct line to use the point colors
    chain->use_vertex_color_all();
    
    std::cout << "press any key." << std::endl;
    myFig1.get_key();
    
    // -----------------------------------
    // -----------------------------------
    // Animation: Randomly change the colors and constantly increment the y-translation & z-rotation
    printf("[animation: randomly change the colors and constantly increment the y-translation & z-rotation]\n");
    
    while (true) {
        // iterate through the points in the line
        for (auto it=chain->points.begin(); it!=chain->points.end(); ++it)
            (*it)->color() = sglMake3vec ( 0.5*(rand_d+1.0), 0.5*(rand_d+1.0), 0.5*(rand_d+1.0)  );  // random color
        // translate the chain by 0.01 towards +z and rotate about x-axis by 1.0 degrees
        chain_translation->y += 0.01;
        chain_rotation->angle += 1.0;
        // flush the changes and pause
        myFig1.flush();
        std::this_thread::sleep_for (std::chrono::milliseconds(100)); // 100ms
    }
    
    std::cout << "press any key." << std::endl; std::cin.get(); // Pause for keyboard input
}


