#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "tropa.h"
#include "baldosa.h"

bool init(SDL_Window* window, SDL_Renderer* renderer, char* titulo, int xpos, int ypos, int width, int height, bool fullscreen);

int main(void)
{
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	bool jokoaHasi = false;

	jokoaHasi = init(window, renderer, "MUwar", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 700, false);

	while (true)
	{

	}

	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}

bool init(SDL_Window* window, SDL_Renderer* renderer, char* titulo, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;
	bool ret = true;

	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN_DESKTOP;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		fprintf(stderr, SDL_GetError());
		ret = false;
	}

	if ((window = SDL_CreateWindow(titulo, xpos, ypos, width, height, flags | SDL_WINDOW_RESIZABLE | SDL_WINDOW_FOREIGN)) == NULL)
	{
		fprintf(stderr, SDL_GetError());
		ret = false;
	}

	if ((renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE | SDL_RENDERER_PRESENTVSYNC)) == NULL)
	{
		fprintf(stderr, SDL_GetError());
		ret = false;
	}

	if (SDL_SetRenderDrawColor(renderer, 0xaa, 0xaa, 0x3b, 0xFF) < 0)
	{
		fprintf(stderr, SDL_GetError());
		ret = false;
	}

	return ret;
}
