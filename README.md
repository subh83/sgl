Simple OpenGL (SGL)                                                  
-------------------
A simplified, threaded C++ wrapper for OpenGL and GLUT

### Features/Objectives:

- Simplify the OpenGL and GLUT interface to make it intuitive like MATLAB.
- Automatic threading for OpenGL windows and processes.
- Allow easy creation of objects and maintenance of object hierarchy.
- Object properties computed/modified according to object hierarchy.
- Easy access & modification to object properties and transformations.
- Allow easy creation and management of multiple windows.

### Illustrative Example:


```C++
#include <iostream>
#include "sgl/sgl"

#define rand_d (2.0 * ((double)rand()) / ((double)RAND_MAX) - 1.0)  // random number between -1 and 1

int main(int argc, char *argv[])
{
    
    sglFigure myFig; // create sglFigure instance
    myFig.init (); // Display the figure
    
    // draw a sphere
    myFig.addChild ( sglSphere (0.0,0.0,2.0, 1.0, 1.0,0.2,0.0) );
    //                    ^^     cx, cy, cz, rad,   r,  g,  b
    
    // draw multiple random boxes and rotate them about random axes
    for (int i=0; i<10; ++i) {
        sglBox* bx = myFig.addChild ( sglBox (rand_d, rand_d, rand_d,  // x1,y1,z1
                                              rand_d, rand_d, rand_d,  // x2,y2,z2
                                              0.4,0.4,0.8, 0.6) );     // r,g,b, alpha
        bx->addTransformation ( sglRotate (30, rand_d, rand_d, rand_d) );
        //                         ^^   angle,      x,      y,      z   (angle and axis of rotation)
    }
    
    myFig.get_key("press any key to save file.\n");  // Pause for keyboard input
    myFig.save_as_image("crystal_red_dwarf.png");  // save as image (required OpenCV)
    myFig.get_key("press any key to exit.\n");
}

```


**Output screenshot ("crystal_red_dwarf.png"):**

<img src="http://subhrajit.net/files/externally-linked-files/images/github-sgl/crystal_red_dwarf.png" width="400" style="border:solid 2px #eee"/>



**************************************************************************

### Developers / contributors:

  - Subhrajit Bhattacarya (maintainer): subhrajit@gmail.com


### Accompanying modules (code included -- see individual code file/folder):

  - GLT-ZPR:
    Zoom-pan-rotate mouse manipulation module for GLUT.
    Version 0.4, October 2003
    by Nigel Stewart.
    License: GNU Lesser General Public License.
    Link: http://www.nigels.com/glt/gltzpr/


### Dependencies:

- OpenGL, GLUT
- Boost
- OpenCV (optional - for saving screenshots)

TODO:
- Add more objects to the 'sgl_objects' folder.
  See the '_template.h' file for a template.
- Allow user to change light and display settings.
- Implement textures.

**************************************************************************

Use:
----

### Install headers in the system folder and compile example programs:

- `cd` to the folder containing this README file
- Install headers (optional) by running:
  
        sudo make install

- Compile the example programs by running:
  
        make examples


### Basic usage:

```C++

#include "sgl/sgl.h"
// ...

int main(int argc, char *argv[])
{
    sglFigure my_fig;               // create SGL figure instance
    my_fig.init ();                 // Display the figure
    
    // ...
    
    // Add objects to figure. e.g, sglLine (x0,y0,z0, x1,y1,z1)
    auto my_line = my_fig.addChild ( sglLine (-2.0,0.0,0.0, 2.0,0.0,0.0) );
    // etc...
    
    // Set a property of an object
    my_line->linewidth() = 3.0;
    
    // Access a sub-object of an object (a point for a line)
    my_line->points[0]->color() = sglMake3vec (1.0, 0.0, 0.0);
    
    // Add transformation to an object
    my_line->addTransformation ( sglRotate(30.0,  0.0, 0.0, 1.0) );
    
    // ...
    
    // Pause for keystroke
    my_fig.get_key();
    
    // Animation
    while (true) {
        // change some properties, add/modify objects or sub-objects, etc.
        // ...
        my_fig.flush ();  // flush all pending changes to the figure
        // pause for 100ms, etc.
    }
    
    // ...
}
```

### Available Objects

For the currently available objects, see the `sgl/sgl_objects` folder. The constructors of each object should be self-explanatory. The `template_.icc` acts as a guide for creating new objects. More extensive documentation will be created in future.

### Suggested compilation options:

Without OpenCV:
```
g++ -std=gnu++11 -O3 -g -o <program> <program>.cpp -lm -lglut -lGLU -lGL -lXi -lXmu -lX11 -lXext
```

With OpenCV:
```
g++ -std=gnu++11 -O3 -g -o <program> <program>.cpp -lm -lglut -lGLU -lGL -lXi -lXmu -lX11 -lXext `pkg-config --cflags --libs --silence-errors opencv` -D__opencv=1
```

**************************************************************************

Compiling and examples:
----------------------

- This library is (to a large extent) template-based.
  There is nothing to build. Simply include the file "sgl.h" in your code.
  You can (optionally) install the headers in the system folder by running
  `sudo make install`.

- For compiling your program, you'll need to link to the GL, glut and X11
  libraries. Besides that, you'll need the Boost library.

- Most of the functionalities are intuitive and easy to find from the code.
  See the 'examples' folder for examples (run `make examples` to compile).

**************************************************************************

License:
-------
```
**************************************************************************
*                                                                        *
*  Simple OpenGL (SGL)                                                   *
*  A simplified, threaded C++ wrapper for OpenGL and GLUT                *
*  Version 1.1b                                                          *
*  ----------------------------------------------------------            *
*  Copyright (C) 2018  Subhrajit Bhattacharya                            *
*                                                                        *
*  This program is free software: you can redistribute it and/or modify  *
*  it under the terms of the GNU General Public License as published by  *
*  the Free Software Foundation, either version 3 of the License, or     *
*  (at your option) any later version.                                   *
*                                                                        *
*  This program is distributed in the hope that it will be useful,       *
*  but WITHOUT ANY WARRANTY; without even the implied warranty of        *
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
*  GNU General Public License for more details                           *
*  <http://www.gnu.org/licenses/>                                        *
*                                                                        *
*                                                                        *
*  Contact: subhrajit@gmail.com, http://subhrajit.net/                   *
*                                                                        *
*                                                                        *
**************************************************************************
```
