#include <stdio.h>
#include <SDL.h>
#include <stdbool.h>
#include <stdint.h>
#include "display.h"
#include "vector.h"

// Flag to check if the window and renderer were initialized.
bool is_running = false;

// Array for out cube vectors
#define N_POINTS (9*9*9)
vec3_t cube_points[N_POINTS];
vec2_t projected_points[N_POINTS]; //Array for projected points.

float fov_factor = 128;

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

	// Load the array of vectors for the cube
	int point_counter = 0;

	// Iterate 9 vectors for each direction and create a vector and add it to the cube points
	for (float x = -1; x <= 1; x += 0.25) {
		for (float y = -1; y <= 1; y += 0.25) {
			for (float z = -1; z <= 1; z += 0.25) {
				vec3_t new_point = { .x = x, .y = y, .z = z };
				cube_points[point_counter++] = new_point;
			}
		}
	}
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

// Project points orthogrphically
vec2_t project(vec3_t point) {
	// Convering to a projected 3d point in 2d
	vec2_t projected_point = {
		.x = (fov_factor * point.x),
		.y = (fov_factor * point.y)
	};
	return projected_point;
}

void update(void) {
	for (int i = 0; i < N_POINTS; i++) {
		vec3_t point = cube_points[i];

		// Project the current point
		vec2_t projected_point = project(point);

		// Save the projected 2D vector in the array of projected points
		projected_points[i] = projected_point;
	}
}

void render(void) {
	//SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Drawing the renderer with a color
	//SDL_RenderClear(renderer); // Clearing the renderer before we update it

	//draw_grid(0xFF0000FF, 100);
	//draw_rect(100, 200, 100, 150, 0xFF5489A0);

	// Loop over projection points and draw
	for (int i = 0; i < N_POINTS; i++) {
		vec2_t projected_point = projected_points[i];
		draw_rect(
			projected_point.x + (window_width / 2),
			projected_point.y + (window_height / 2),
			4,
			4,
			0xFFFF8F00
		);
	}

	// render the new color on the buffer
	render_color_buffer();
	clear_color_buffer(0xFF000000);

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


