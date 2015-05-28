#include <cmath>
#include <iostream>
#include "../sgl.h"

int main(int argc, char *argv[])
{
    sglViewProperties prop; // figure properties
    // prop.__ = <value>; // set properties if required
    sglFigure my_fig (prop); // create OpenGL figure instance with desired properties
    my_fig.show (); // Display the figure
    
    // -----------------------------------------
    
    // Add a line and get a handle to the line
    auto myLine1 = my_fig.addObject( sglLine (0.0,0.0,0.0, 1.0,1.0,1.0, {1.0,0.0,0.0,1.0}, 2.5) );
    /* Syntax: sglLine (double x0, double y0, double z0, double x1, double y1, double z1,
                            std::vector<double> color={0.0,0.0,0.0,1.0}, double width=2.0, std::string style="flat") */
    
    std::cin.get(); // Pause for keyboard input
    
    auto myLine2 = my_fig.addObject( sglLine (1.0,1.0,1.0, 2.0,0.0,0.0, {0.0,0.0,1.0,1.0}, 2.5) ); // add another line
    myLine1->width = 8.0; // change a property of first line
    
    std::cin.get(); // Pause for keyboard input
}


