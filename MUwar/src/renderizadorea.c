#include "renderizadorea.h"

/*
 *	START: Estruktura pribatuak
 */

typedef struct
{
	SDL_Texture* aurrea;
	SDL_Texture* atzea;
	SDL_Texture* ezker;
	SDL_Texture* eskubi;
} Textura;

typedef struct
{
	/* Terrenoak */
	Textura larrea;
	Textura ibaia;
	Textura karretera;
	Textura basoa;
	Textura baso_moztua;
	Textura mendia;
	Textura mendi_hautsia;
	Textura hiria;
	Textura fabrika;
	Textura basea;

	/* Tropak */
	Textura infanteria;
	Textura infanteria_mek;
	Textura errekonozimentua;
	Textura tankea;

} ElementuenTexturak;

/*
 *	END: Estruktura pribatuak
 */

 /*
  *	START: Funtzio pribatuak
  */

static ElementuenTexturak* argazkiak_kargatu(SDL_Renderer* render);					/* Argazkiak memoriara kargatzen ditu */
static void argazkiak_garbitu(ElementuenTexturak** texturak);						/* Argazkiak memoriatik garbitzen ditu */

/*
 *	END: Funtzio pribatuak
 */


 /* Globalak (tenporalki) */
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
ElementuenTexturak* text = NULL;


bool render_sortu(char* titulo, int xpos, int ypos, int width, int height, bool fullscreen)
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
		goto atera;
	}

	/* IMG inzializatu */
	if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
	{
		fprintf(stderr, IMG_GetError());
		dena_ondo = false;
	}

	text = argazkiak_kargatu(renderer);

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

	SDL_Rect rekt = { 0 };

	rekt.x = 400;
	rekt.y = 400;

	rekt.w = 100;
	rekt.h = 100;


	if (SDL_RenderClear(renderer) < 0)
	{
		fprintf(stderr, SDL_GetError());
		dena_ondo = false;
		goto atera;
	}
	

	SDL_RenderCopy(renderer, text->infanteria.aurrea, NULL, &rekt);

	SDL_RenderPresent(renderer);

atera:
	return dena_ondo;
}

/*
 *	START: Funtzio pribatuen inplementazioa
 */

ElementuenTexturak* argazkiak_kargatu(SDL_Renderer* render)
{
	/* Sortu ElementuTexturak structa */
	ElementuenTexturak* texturak = (ElementuenTexturak*)calloc(1, sizeof(ElementuenTexturak));

	SDL_Surface* tmpsrf = NULL;

	/*
	 * Kargatu Terrenoaren Texturak
	 */

	/* Larrea */
	tmpsrf = IMG_Load("res\\img\\GRASS.png");
	texturak->larrea.aurrea = SDL_CreateTextureFromSurface(render, tmpsrf);
	SDL_FreeSurface(tmpsrf);

	/* Mendia */
	tmpsrf = IMG_Load("res\\img\\MOUNTAIN.png");
	texturak->mendia.aurrea = SDL_CreateTextureFromSurface(render, tmpsrf);
	SDL_FreeSurface(tmpsrf);

	/* Ibaia */
	tmpsrf = IMG_Load("res\\img\\WATER.png");
	texturak->mendia.aurrea = SDL_CreateTextureFromSurface(render, tmpsrf);
	SDL_FreeSurface(tmpsrf);

	/* 
	 * Kargatu Tropen Texturak 
	 */

	/* Infanteria */
	tmpsrf = IMG_Load("res\\img\\PERTSONA.png");
	texturak->infanteria.aurrea = SDL_CreateTextureFromSurface(render, tmpsrf);
	SDL_FreeSurface(tmpsrf);

	return texturak;
}

 /*
  *	END: Funtzio pribatuen inplementazioa
  */

