```
**************************************************************************
*                                                                        *
*  Simple OpenGL (SGL)                                                   *
*  A simplified, threaded C++ wrapper for OpenGL and GLUT                *
*  Version 1.0a                                                          *
*  ----------------------------------------------------------            *
*  Copyright (C) 2017  Subhrajit Bhattacharya                            *
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


Developers / contributors:
-------------------------
  - Subhrajit Bhattacarya (maintainer): subhrajit@gmail.com


Accompanying modules (code included -- see individual code file/folder):
-----------------------------------------------------------------------
  - GLT-ZPR
    Zoom-pan-rotate mouse manipulation module for GLUT
    Version 0.4, October 2003
    by Nigel Stewart
    License: GNU Lesser General Public License
    Link: http://www.nigels.com/glt/gltzpr/


**************************************************************************

Features/Objectives:
-------------------

- Simplify the OpenGL and GLUT interface to make it intuitive like MATLAB.
- Automatic threading for OpenGL windows and processes.
- Allow easy creation of objects and maintenance of object hierarchy.
- Object properties computed/modified according to object hierarchy.
- Easy access & modification to object properties and transformations.
- Allow easy creation and management of multiple windows.

TODO:
- Add more objects to the 'sgl_objects' folder.
  See the '_template.h' file for a template.

**************************************************************************

Install:
-------
- cd to the folder containg this README file
- Run:

    sudo make install


Basic usage:
-----------
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

Suggested compilation options:
-----------------------------
```
-std=gnu++11 -O3 -g -w -lm -lglut -lGLU -lGL -lXi -lXmu -lX11 -lXext
```

**************************************************************************

Compiling and examples:
----------------------

- This library is template-based.
  There is nothing to build. Simply include the file "sgl.h" in your code.
  You can install the headers by running
  
        sudo make install

- For compiling your program, you'll need to link to the GL, glut and X11
  libraries. Besides that, you'll need the Boost library.

- Most of the functionalities are intuitive and easy to find from the code.
  See the 'examples' folder for examples (run 'make all' to compile).
