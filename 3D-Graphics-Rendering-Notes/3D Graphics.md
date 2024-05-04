# Introduction

## Software Rendering
 - CPU based processing - software based rendering
 - GPU based processing - hardware based rendering
## Overview
- Pure C and SDL - why? for code to be portable. it is easy to go from C  to C++ or any other language or even OS.
- Foundation of 3D graphics - rasterize a line, drawing a pixel, mapping a triangle etc.
- Setup an env 
- Trigonometry and Lin Algebra
- Vertices and Meshes
- Displaying Pixels and Color Buffer
- 3D projection and perspective
- Rasterizing lines and triangles
- Handling textures and texture mapping
- Camera and view transformation
- Display 3D Models - lighting and reading data from files

# Compiling
Why C - pretty simple, fast, memory management, portable. SDL, the library we will use new, to have the correct permission to manipulate pixels, cuz every OS has its own functions do the sane things. SO SDL solves this problem and have a single code to accomplish the same thing in different OS.

## Setup for windows
 - We are tied with what windows wants us to use, so we need to use visual studio
 - Flow Compiling - we write our C code in the main.c file and then we need to translate that code into machine code using the gcc compiler which can be done using the command ```gcc file.c -o outputFile``` and that we can execute to run our code.
 - Some Compiler Flags
	 - ```-Wall``` - Show all warnings
	 - `-std=c99` - Standard for code, c99 is the standard we are using
 - It can get painful if we have to write the command to compile every time, this is why we have a makefile to list all the rules for building
 - Makefiles - make file take certain rules, `Build` the command to build the project, `run` to run the build and `clean` to remove the build
 - VS + SDL - 
	 - Make sure to have the C++ development in VS
	 - Make your new solution
	 - Download SDL2 from their website extract it and put it inside the C folder
	 - Now we can setup the VS to recognize SDL2 cause right now `#include<SDL.h>` give an error, cause the compiler doesn't know where the header file is
	 - Go to the properties of the solution, and add the lib and include folders to the Library Directories and Include Directories in the VC Directories.
	 - Also need to include these to the linker so we can build the project properly with files we need to include. The new dependencies are `SDL2.lib` and `SDL2main.lib`
	 - For SDL to work the main function should look like this with the args - `int main(int argc, char* args[]()` 
	 - After all this our code builds properly but we still need to include the `.dll` file. This file can be found in the lib folder, and then we can add it to 
