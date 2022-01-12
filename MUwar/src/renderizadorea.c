#include "renderizadorea.h"

/* Globalak (tenporalki) */
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

bool render_init(char* titulo, int xpos, int ypos, int width, int height, bool fullscreen)
{
	bool dena_ondo = true;
	int flags = fullscreen ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0;

	/* SDL libreria guztiak hasieratzen ditu, hala ezean errore bat emango du */
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		fprintf(stderr, SDL_GetError());
		dena_ondo = false;
		goto atera;
	}

	/* Lehio bat sortzen du, hala ezean errore bat emango du */
	if ((window = SDL_CreateWindow(titulo, xpos, ypos, width, height, flags | SDL_WINDOW_RESIZABLE | SDL_WINDOW_FOREIGN)) == NULL)
	{
		fprintf(stderr, SDL_GetError());
		dena_ondo = false;
		goto atera;
	}

	/* Renderizadore bat sortzen du, hala ezean errore bat emango du */
	if ((renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE | SDL_RENDERER_PRESENTVSYNC)) == NULL)
	{
		fprintf(stderr, SDL_GetError());
		dena_ondo = false;
		goto atera;
	}

	/* Ze kolorearekin margotzea nahi det esaten da, hala ezean errore bat emango du */
	if (SDL_SetRenderDrawColor(renderer, 0xAA, 0xAA, 0x3B, 0x00) < 0)
	{
		fprintf(stderr, SDL_GetError());
		dena_ondo = false;
	}

atera:
	return dena_ondo;
}

void render_garbitu(void)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

bool render_marraztu(void)
{
	bool dena_ondo = true;

	if (SDL_RenderClear(renderer) < 0)
	{
		fprintf(stderr, SDL_GetError());
		dena_ondo = false;
		goto atera;
	}

	SDL_RenderPresent(renderer);

atera:
	return dena_ondo;
}
