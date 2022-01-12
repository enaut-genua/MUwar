#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "tropa.h"
#include "baldosa.h"



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



