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
	 - After all this our code builds properly but we still need to include the `.dll` file. This file can be found in the lib folder, and then we can add it to folder for the project.

# SDL Setup and Color Buffer
Lets try and set the color of a single pixel
## Creating an SDL Window
To see our pixels and 3D objects, we need a window and renderer added to that window. To do this we need to initialize both. SDL has functions to create both for us, both functions take params that can help modify the window. `SDL_CreateWindow()` and `SDL_CreateRenderer()`

## Rendering an SDL Window
Same idea as the game loop where we setup first, then enter a loop where we get the users input, then update the frame and the render the new the frame, which is the skeleton of a game.

For our process input we can add and event to check for user events. The only events we can check for now our if the user clicks the x button. To do this SDL has `SDL_QUIT` which is an event that get called when the x button is pressed and we need to stop the renderer too. Other is for pressing escape, so when the event is a key down and the key symbol is escape we need to exit out of the loop. 

Then we can draw a color to the rendering by using `SDL_SetRendererDrawColor()` and passing the renderer and color. And then we need to clear the renderer and present the view. We need to clear the renderer before because we are drawing over the entire screen. And there are other thing that change the renderer and also another reason would be since the draw color is another API call.

**Note - for linker error we could pass the lib dependencies as a flag.**

