#ifndef INITCLOSE_H
#define INITCLOSE_H
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

bool init(SDL_Window* window, SDL_Renderer* renderer, char* titulo, int xpos, int ypos, int width, int height, bool fullscreen);
void close(SDL_Window* window, SDL_Renderer* renderer);
#endif // INITCLOSE_H