#!/bin/bash 

opts="-std=gnu++11 -O3 -g -w -I. -I.."
libs="-lm -lglut -lGLU -lGL -lXi -lXmu -lX11 -lXext"

for examplename in "example1" "example2"
do
	echo "Now compiling $examplename..."
	g++ $opts -c $examplename.cpp
	g++ $opts -o $examplename $examplename.o $libs
done

echo

