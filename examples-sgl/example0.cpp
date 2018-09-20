#include <iostream>
#include "sgl/sgl"

#define rand_d (2.0 * ((double)rand()) / ((double)RAND_MAX) - 1.0)  // random number between -1 and 1

int main(int argc, char *argv[])
{
    
    sglFigure myFig; // create sglFigure instance
    myFig.init (); // Display the figure
    
    // draw a sphere
    myFig.addChild ( sglSphere (0.0,0.0,2.0, 1.0, 1.0,0.2,0.0) );
    //                      ^^   cx, cy, cz, rad,   r,  g,  b
    
    // draw multiple rotated boxes
    for (int i=0; i<10; ++i) {
        sglBox* bx = myFig.addChild ( sglBox (rand_d, rand_d, rand_d, // x1,y1,z1
                                              rand_d, rand_d, rand_d, // x2,y2,z2
                                              0.4,0.4,0.8, 0.6) );    // r,g,b, alpha
        bx->addTransformation ( sglRotate(30, rand_d, rand_d, rand_d) );
                                    // ^^  angle,      x,      y,      z   --  axis-angle representation of rotation
    }
    
    myFig.get_key("press any key to save file.\n"); // Pause for keyboard input
    myFig.save_as_image("crystal_red_dwarf.png");
    myFig.get_key("press any key to exit.\n");
}


