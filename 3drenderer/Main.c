#include <stdio.h>
#include <SDL.h>
#include <stdbool.h>

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

// Flag to check if the window and renderer were initialized.
bool is_running;

bool initialize_window(void) {
	//Initialize the hardware calls for SDL
	// We can be lazy right now initialize everything
	// We might run into some permissions errors
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		fprintf(stderr, "Error Initing SDL.\n");
		return false;
	}

	// Creating a SDL window and the renderer
	// We open a window and add the renderer to it

	// Params	1 - window name (NULL - basically give u no border) 
	//			2&3 - pos x and pos y
	//			3&4 - width and height
	//			5 - bunch of flags (broder, shadow etc)
	window = SDL_CreateWindow(
		NULL,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		800,
		600,
		SDL_WINDOW_BORDERLESS
	);

	if (!window) {
		fprintf(stderr, "Error creating sdl window");
		return false;
	}

	//Attaching a renderer
	// Params	1 - the window
	//			2 - default display device (-1 -> idc)
	//			3 - flags (0 - none)
	renderer = SDL_CreateRenderer(window,-1,0);

	if (!renderer) {
		fprintf(stderr, "Error creating the renderer");
		return false;
	}

	return true;
}

int main(int argc, char* args[]) {
	
	// Create a SDL window
	is_running = initialize_window();

	return 0;
}


