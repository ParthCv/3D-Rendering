#include <stdio.h>
#include <SDL.h>
#include <stdbool.h>
#include <stdint.h>

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

// Flag to check if the window and renderer were initialized.
bool is_running = false;

// Our color buffer 
uint32_t* color_buffer = NULL;

// Texture for color buffer
SDL_Texture* color_buffer_texture = NULL;

int window_width = 800;
int window_height = 600;

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
		"Red Window",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		window_width,
		window_height,
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

void setup(void) {
	//Allocate memory for the color buffer
	color_buffer = (uint32_t*) malloc(sizeof(uint32_t) * window_width * window_height);

	//Double check memory allocation.
	if (!color_buffer) {
		fprintf(stderr, "Error allocating memory for color buffer");
	}

	// Creating an SDL Texture to display a color
	// Params - 1 - the renderer
	//			2 - the format for the encoding
	//			3 - texture access
	color_buffer_texture = SDL_CreateTexture(
		renderer,
		SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING,
		window_width,
		window_height
	);
}



void process_input(void) {
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

void update(void) {

}

void render_color_buffer(void) {
	// Update the texture for the renderer
	// Params - 1 - texture to update
	//			2 - the SDL_Rect or parth of the texture to update (NULL if it the entire texture)
	//			3 - pixel data
	//			4 - pitch aka number of bytes in a row of picel data
	SDL_UpdateTexture(
		color_buffer_texture,
		NULL,
		color_buffer,
		(sizeof(uint32_t) * window_width)
	);

	// Copy the portion of the texture to the current render texture
	// Params - 1 - rendere
	//			2 - rect in the texture (Null for all)
	//			3 - rect on the new texture (Null for all)
	SDL_RenderCopy(
		renderer,
		color_buffer_texture,
		NULL,
		NULL
	);
}

void clear_color_buffer(uint32_t color) {
	for (int i = 0; i < window_height; i++) {
		for (int j = 0; j < window_width; j++) {
			color_buffer[(window_width * i) + j] = color;
		}
	}
}

void render(void) {
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Drawing the renderer with a color
	SDL_RenderClear(renderer); // Clearing the renderer before we update it

	// render the new color on the buffer
	render_color_buffer();
	clear_color_buffer(0xFFFFFF00);

	SDL_RenderPresent(renderer); // Now once its clear we present it.
}

void destroy_window() {
	free(color_buffer);

	// Now destroy the renderer
	// We destroy in the inverse order of creation
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	// Destroy the initializer
	SDL_Quit();
}

int main(int argc, char* args[]) {
	is_running = initialize_window();

	setup();

	while (is_running) {
		process_input();
		update();
		render();
	}

	destroy_window();

	return 0;
}


