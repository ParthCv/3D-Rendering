#pragma once

#include <stdio.h>
#include <SDL.h>
#include <stdbool.h>
#include <stdint.h>

extern int window_width;
extern int window_height;
extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern uint32_t* color_buffer;
extern SDL_Texture* color_buffer_texture;

bool initialize_window(void);
void render_color_buffer(void);
void clear_color_buffer(uint32_t color);
void draw_grid(uint32_t color, int spacing);
void draw_rect(int x, int y, int height, int width, uint32_t color);
void destroy_window(void);