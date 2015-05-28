***************************************************************************
*                                                                         *
*    Simple OpenGL                                                        *
*    A simplified, template-based, muti-threaded C++ wrapper to OpenGL    *
*    Version 0.1b                                                         *
*    ----------------------------------------------------------           *
*    Copyright (C) 2015  Subhrajit Bhattacharya                           *
*                                                                         *
*    This program is free software: you can redistribute it and/or modify *
*    it under the terms of the GNU General Public License as published by *
*    the Free Software Foundation, either version 3 of the License, or    *
*    (at your option) any later version.                                  *
*                                                                         *
*    This program is distributed in the hope that it will be useful,      *
*    but WITHOUT ANY WARRANTY; without even the implied warranty of       *
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        *
*    GNU General Public License for more details                          *
*    <http://www.gnu.org/licenses/>                                       *
*                                                                         *
*                                                                         *
*    Contact: subhrajit@gmail.com, http://subhrajit.net/                  *
*                                                                         *
*                                                                         *
***************************************************************************

Basic usage:

#include "../sgl.h"
// ...

int main(int argc, char *argv[])
{
    sglFigure my_fig;               // create SGL figure instance
    my_fig.properties.width = 200;  // set a property for the figure window
    my_fig.init ();                 // Display the figure
    
    // ...
    
    // Add objects to figure. e.g, sglLine (x0,y0,z0, x1,y1,z1)
    auto my_line = my_fig.addObject( sglLine (0.0,0.0,0.0, 1.0,1.0,1.0) );
    // etc...
    
    // Set property of an object
    my_line->width = 8.0;
    
    // ...
    
    my_fig.flush ();  // flush all pending changes to the figure
    
    // ...
}

Compiling:
- This library is template-based.
- There is nothing to build. Simply include the file "sgl.h" in your code.
- For compiling, you'll need to link to the GL, glut, X11 and pthread libraries.
- See the 'example' folder for examples (sun the shell script to compile).

