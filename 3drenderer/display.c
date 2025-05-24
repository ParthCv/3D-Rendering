#include "display.h"

int window_width = 800;
int window_height = 600;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
uint32_t* color_buffer = NULL;
SDL_Texture* color_buffer_texture = NULL;

bool initialize_window(void) {
	//Initialize the hardware calls for SDL
	// We can be lazy right now initialize everything
	// We might run into some permissions errors
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		fprintf(stderr, "Error Initing SDL.\n");
		return false;
	}

	// Use SDL to query the fullsceen max width and height
	SDL_DisplayMode display_mode; //Struct for the display mode
	SDL_GetCurrentDisplayMode(0, &display_mode); //Need the info for main display and pointer to the struct we created

	//Now we have access to the width height and refresh rate of the display
	window_width = display_mode.w;
	window_height = display_mode.h;

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
	renderer = SDL_CreateRenderer(window, 3, 0);

	if (!renderer) {
		fprintf(stderr, "Error creating the renderer");
		return false;
	}

	// Set the window to real fullscreen with video mode
	//SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

	return true;
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

void draw_grid(uint32_t color, int spacing) {
	// Vertical Lines
	for (int i = 0; i < window_height; i++) {
		for (int j = 0; j < window_width; j += spacing) {
			color_buffer[(window_width * i) + j] = color;
		}
	}

	// Horizontal Lines
	for (int i = 0; i < window_height; i += spacing) {
		for (int j = 0; j < window_width; j++) {
			color_buffer[(window_width * i) + j] = color;
		}
	}
}

void draw_rect(int x, int y, int width, int height, uint32_t color) {
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			//color_buffer[(window_width * (y + i)) + (x + j)] = color;
			draw_pixel(x + i, y + j, color);
		}
	}
}

void draw_pixel(int x, int y, uint32_t color) {
	if (x >= 0 && x < window_width && y >= 0 && y < window_height) { //Check if the pixel is in the screen dimension
		color_buffer[(window_width * y) + x] = color;
	}
}

void destroy_window(void) {
	free(color_buffer);
	// Now destroy the renderer
	// We destroy in the inverse order of creation
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	// Destroy the initializer
	SDL_Quit();
}




