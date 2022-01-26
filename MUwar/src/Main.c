#include "Utils.h"


int poh = 500, paow = 500;
SDL_Event event;

int main(int argc, char* argv[])
{
	(void)(argc);
	(void)(argv);
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = SDL_CreateWindow("title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, heigth, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);
	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);


	bool running = true;

	int step = 0;

	hartu_running(&running);


	while (running)
	{

		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				running = false;
			}
		}
		menu(window, renderer, paow, poh, step);
		controlspantaila(renderer, window);
		menuFinala(renderer, paow, poh, window);

	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}

