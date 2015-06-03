**************************************************************************
*                                                                        *
*  Simple OpenGL (SGL)                                                   *
*  A simplified, threaded C++ wrapper for OpenGL and GLUT                *
*  Version 0.2a                                                          *
*  ----------------------------------------------------------            *
*  Copyright (C) 2015  Subhrajit Bhattacharya                            *
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


Developers / contributors
--------------------------------------------------------------------------
  - Subhrajit Bhattacarya (maintainer): subhrajit@gmail.com
  - 
    [Add your name to the list above.]


Accompanying modules (code included -- see individual code file/folder)
--------------------------------------------------------------------------
  - GLT-ZPR
    Zoom-pan-rotate mouse manipulation module for GLUT
    Version 0.4, October 2003
    by Nigel Stewart
    License: GNU Lesser General Public License
    Link: http://www.nigels.com/glt/gltzpr/


**************************************************************************

Features/Objectives:
- Simplify the OpenGL and GLUT interface to make it intuitive like MATLAB.
- Automatic threading for OpenGL windows and processes.
- Allow easy creation and management of multiple windows.
- Allow easy creation of objects and change to their properties.

--------------------------------------------------------------------------

Basic usage:

#include "sgl.h"
// ...

int main(int argc, char *argv[])
{
    sglFigure my_fig;               // create SGL figure instance
    my_fig.init ();                 // Display the figure
    
    // ...
    
    // Add objects to figure. e.g, sglLine (x0,y0,z0, x1,y1,z1)
    auto my_line = my_fig.addChild ( sglLine (-2.0,0.0,0.0, 2.0,0.0,0.0) );
    // etc...
    
    // Set property of an object
    my_line->linewidth() = 3.0;
    
    // ...
    
    my_fig.flush ();  // flush all pending changes to the figure
    my_fig.get_key();  // Pause for keystroke
    
    // ...
}

Suggested compilation options:
-std=gnu++11 -O3 -g -w -lm -lglut -lGLU -lGL -lXi -lXmu -lX11 -lXext -lpthread

--------------------------------------------------------------------------

Compiling:
- This library is template-based.
- There is nothing to build. Simply include the file "sgl.h" in your code.
- For compiling, you'll need to link to the GL, glut, X11 and pthread libraries.
- See the 'example' folder for examples (run the shell script to compile).

