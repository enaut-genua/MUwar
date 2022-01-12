#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "tropa.h"
#include "baldosa.h"

#pragma region FUNTZIOEN DEKLARAZIOAK

bool init( char* titulo, int xpos, int ypos, int width, int height, bool fullscreen);
void close();


#pragma endregion
#pragma region FUNTZIO ERREPIKAKORREN DEKLARAZIOAK

void ebentoakGestionatu();
void render();

#pragma endregion
/*-----------------------------------------------------------------------------------------------
Eñaut aldagai hauek global bezala ipini ditut gero beste funtzio guztietan erabiltzen direlako
-----------------------------------------------------------------------------------------------*/
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
bool jokoaMartxan = false;
int main(void)
{

	

	jokoaMartxan = init( "MUwar", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 700, false);

	while (jokoaMartxan)
	{
		ebentoakGestionatu();
		render();
	}

	close();

	return 0;
}

#pragma region MAIN FUNTZIOAN BAKARRIK ERABILTZEN DIREN FUNTZIOAK

bool init( char* titulo, int xpos, int ypos, int width, int height, bool fullscreen)
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
	jokoa hasteko prest dagoen edo ez itsuliko du
	-----------------------------------------------------------------------------------------------*/
	return ret;
}
void close() {
	/*-----------------------------------------------------------------------------------------------
	Memoria garbitzen du, hau jokoaren amaieran ipintzen da BETI!!!
	-----------------------------------------------------------------------------------------------*/
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	//hola ander
}

#pragma endregion

#pragma region BEHIN ETA BERRIRO ERREBISATUKO DIREN DUNTZIOAK

/*-----------------------------------------------------------------------------------------------
Funtzio honek eventuak gestionatzen ditu beraz, ebentoak uneoro errebisatzen joango dira jokoa martxan dabilen bitartean
-----------------------------------------------------------------------------------------------*/
void ebentoakGestionatu() {
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.key.type) {
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE: jokoaMartxan = false; break;
			}
		break;
	}
	/*-----------------------------------------------------------------------------------------------
	LEHIOAREN X botoia sakatzean jokoa amaituko da
	-----------------------------------------------------------------------------------------------*/
	switch (event.quit.type) {
	case SDL_QUIT: jokoaMartxan = false; break;
	}
}



/*-----------------------------------------------------------------------------------------------
Funtzio honek Behin eta berriz marraztuko du 
-----------------------------------------------------------------------------------------------*/
void render() {
	/*-----------------------------------------------------------------------------------------------
Behin eta berriro borratu eta marrazteko
	-----------------------------------------------------------------------------------------------*/
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
}
#pragma endregion






