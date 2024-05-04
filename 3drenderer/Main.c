#include <stdio.h>
#include <SDL.h>
#include <stdbool.h>

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

// Flag to check if the window and renderer were initialized.
bool is_running = false;

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

void setup() {

}

void process_input() {
	SDL_Event event;	
	SDL_PollEvent(&event); // Stores the event happening into the passed event

	switch (event.type) {
		// SDL_QUIT - triggers when the X button on the window is clicked
		case SDL_QUIT:
			is_running = false;
			break;
		case SDL_KEYDOWN:
			// Key symbol check for esc
			if (event.key.keysym.sym == SDLK_ESCAPE)
				is_running = false;
			break;
		default:
			break;
	}
}

void update() {

}

void render() {
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Drawing the renderer with a color
	SDL_RenderClear(renderer); // Clearing the renderer before we update it

	SDL_RenderPresent(renderer); // Now once its clear we present it.
}

int main(int argc, char* args[]) {
	is_running = initialize_window();

	setup();

	while (is_running) {
		process_input();
		update();
		render();
	}

	return 0;
}


