#include <stdio.h>
#include <SDL.h>
#include <stdbool.h>
#include <stdint.h>
#include "display.h"

// Flag to check if the window and renderer were initialized.
bool is_running = false;

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

void render(void) {
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Drawing the renderer with a color
	SDL_RenderClear(renderer); // Clearing the renderer before we update it

	draw_grid(0xFF0000FF, 100);
	draw_rect(100, 200, 100, 150, 0xFF5489A0);

	// render the new color on the buffer
	render_color_buffer();
	clear_color_buffer(0xFFCABFFF);

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

	destroy_window();

	return 0;
}


