#include"InitClose.h"

bool init(SDL_Window* window, SDL_Renderer* renderer, char* titulo, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;
	bool ret = true;

	if (fullscreen)flags = SDL_WINDOW_FULLSCREEN_DESKTOP;

	/*-----------------------------------------------------------------------------------------------
	SDL libreria guztiak hasieratzen ditu, hala ezean errore bat emango du
	-----------------------------------------------------------------------------------------------*/

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		fprintf(stderr, SDL_GetError());
		ret = false;
	}


	/*-----------------------------------------------------------------------------------------------
	Lehio bat sortzen du, hala ezean errore bat emango du
	-----------------------------------------------------------------------------------------------*/
	if ((window = SDL_CreateWindow(titulo, xpos, ypos, width, height, flags | SDL_WINDOW_RESIZABLE | SDL_WINDOW_FOREIGN)) == NULL)
	{
		fprintf(stderr, SDL_GetError());
		ret = false;
	}

	/*-----------------------------------------------------------------------------------------------
	Renderizadore bat sortzen du, hala ezean errore bat emango du
	-----------------------------------------------------------------------------------------------*/
	if ((renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE | SDL_RENDERER_PRESENTVSYNC)) == NULL)
	{
		fprintf(stderr, SDL_GetError());
		ret = false;
	}
	/*-----------------------------------------------------------------------------------------------
	Ze kolorearekin margtzea nahi det esaten da, hala ezean errore bat emango du
	-----------------------------------------------------------------------------------------------*/
	if (SDL_SetRenderDrawColor(renderer, 0xaa, 0xaa, 0x3b, 0x00) < 0)
	{
		fprintf(stderr, SDL_GetError());
		ret = false;
	}
	/*-----------------------------------------------------------------------------------------------
	Lehioa por defekto txuriz margotzen da, ze kolorearekin margotzea esan ondoren lehioan dagoena guztiz ezabatu eta berriro marrazteko esaten da
	-----------------------------------------------------------------------------------------------*/
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
	/*-----------------------------------------------------------------------------------------------
	jokoa hasteko prest dagoen edo ez itsuliko du
	-----------------------------------------------------------------------------------------------*/
	return ret;
}