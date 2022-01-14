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
static SDL_Texture* textura_sortu(SDL_Renderer* render, const char* path);
static bool marraztu_baldosa(Baldosa* baldosa, SDL_Rect* rect);
static bool marraztu_tropa(Baldosa* baldosa, SDL_Rect* rect);
static void kalkulatu_iso(Bekt2D* iso_pos, float x, float y);

/*
 *	END: Funtzio pribatuak
 */


/*
 *	START: Aldagai globalak
 */

SDL_Window* WINDOW = NULL;
SDL_Renderer* RENDERER = NULL;
ElementuenTexturak* ELEM_TEXT = NULL;
Bekt2D mapa_pos = { 100, 300 };
int ARGAZKI_TAMAINA = 100;


/*
 *	END: Aldagai globalak
 */

bool render_sortu(char* titulo, int xpos, int ypos, int width, int height, bool fullscreen)
{
	bool dena_ondo = true;
	int flags = fullscreen ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0;

	/* SDL libreria guztiak hasieratzen ditu, hala ezean errore bat emango du */
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		fprintf(stderr, "Errorea: %s\n", SDL_GetError());
		dena_ondo = false;
		goto atera;
	}

	/* Lehio bat sortzen du, hala ezean errore bat emango du */
	if ((WINDOW = SDL_CreateWindow(titulo, xpos, ypos, width, height, flags | SDL_WINDOW_RESIZABLE | SDL_WINDOW_FOREIGN)) == NULL)
	{
		fprintf(stderr, "Errorea: %s\n", SDL_GetError());
		dena_ondo = false;
		goto atera;
	}

	/* Renderizadore bat sortzen du, hala ezean errore bat emango du */
	if ((RENDERER = SDL_CreateRenderer(WINDOW, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE | SDL_RENDERER_PRESENTVSYNC)) == NULL)
	{
		fprintf(stderr, "Errorea: %s\n", SDL_GetError());
		dena_ondo = false;
		goto atera;
	}

	/* Ze kolorearekin margotzea nahi det esaten da, hala ezean errore bat emango du */
	if (SDL_SetRenderDrawColor(RENDERER, 0xAA, 0xAA, 0x3B, 0x00) < 0)
	{
		fprintf(stderr, "Errorea: %s\n", SDL_GetError());
		dena_ondo = false;
		goto atera;
	}

	/* IMG inzializatu */
	if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
	{
		fprintf(stderr, "Errorea: %s\n", IMG_GetError());
		dena_ondo = false;
		goto atera;
	}

	ELEM_TEXT = argazkiak_kargatu(RENDERER);

atera:
	return dena_ondo;
}

void render_garbitu(void)
{
	argazkiak_garbitu(&ELEM_TEXT);
	SDL_DestroyRenderer(RENDERER);
	SDL_DestroyWindow(WINDOW);
	SDL_Quit();
}

bool render_marraztu(Mapa *mapa)
{
	bool dena_ondo = true;
	SDL_Rect laukia = { 0 };
	Bekt2D iso_pos = { 0 };
	
	laukia.w = laukia.h = ARGAZKI_TAMAINA;

	if (SDL_RenderClear(RENDERER) < 0)
	{
		fprintf(stderr, "Errorea: %s\n", SDL_GetError());
		dena_ondo = false;
		goto atera;
	}
	

	for (int i = 0; i < mapa->tamaina_x; ++i)
	{
		for (int j = 0; j < mapa->tamaina_y; ++j)
		{
			kalkulatu_iso(&iso_pos, (ARGAZKI_TAMAINA * 0.5f) * i + mapa_pos.x, (ARGAZKI_TAMAINA * 0.5f) * j - mapa_pos.y);

			laukia.x = iso_pos.x;
			laukia.y = iso_pos.y;

			Baldosa* baldosa = mapa_lortu_pos(mapa, i, j);

			if (marraztu_baldosa(baldosa, &laukia) == false)
			{
				fprintf(stderr, "Errorea: Ezin izan da tropa marraztu.\n");
				dena_ondo = false;
				goto atera;
			}

			if (marraztu_tropa(baldosa, &laukia) == false)
			{
				fprintf(stderr, "Errorea: Ezin izan da tropa marraztu.\n");
				dena_ondo = false;
				goto atera;
			}
			
		}
	}

	SDL_RenderPresent(RENDERER);

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

	/*
	 * Kargatu Terrenoaren Texturak
	 */

	/* Larrea */
	if ((texturak->larrea.aurrea = textura_sortu(render, "res\\img\\GRASS.png")) == NULL)
	{
		fprintf(stderr, "Errorea: Ezin izan da larrearen textura sortu.\n");
		goto errorea;
	}

	/* Mendia */
	if ((texturak->mendia.aurrea = textura_sortu(render, "res\\img\\MOUNTAIN.png")) == NULL)
	{
		fprintf(stderr, "Errorea: Ezin izan da mendiaren textura sortu.\n");
		goto errorea;
	}

	/* Ibaia */
	if ((texturak->ibaia.aurrea = textura_sortu(render, "res\\img\\WATER.png")) == NULL)
	{
		fprintf(stderr, "Errorea: Ezin izan da ibaiaren textura sortu.\n");
		goto errorea;
	}

	/* 
	 * Kargatu Tropen Texturak 
	 */

	/* Infanteria */
	if ((texturak->infanteria.aurrea = textura_sortu(render, "res\\img\\PERTSONA.png")) == NULL)
	{
		fprintf(stderr, "Errorea: Ezin izan da infanteriaren aurreko textura sortu.\n");
		goto errorea;
	}

	if ((texturak->infanteria.atzea = textura_sortu(render, "res\\img\\PERTSONA4.png")) == NULL)
	{
		fprintf(stderr, "Errorea: Ezin izan da infanteriaren aurreko textura sortu.\n");
		goto errorea;
	}

	if ((texturak->infanteria.ezker = textura_sortu(render, "res\\img\\PERTSONA2.png")) == NULL)
	{
		fprintf(stderr, "Errorea: Ezin izan da infanteriaren aurreko textura sortu.\n");
		goto errorea;
	}

	if ((texturak->infanteria.eskubi = textura_sortu(render, "res\\img\\PERTSONA3.png")) == NULL)
	{
		fprintf(stderr, "Errorea: Ezin izan da infanteriaren aurreko textura sortu.\n");
		goto errorea;
	}

	return texturak;

errorea:
	free(texturak);
	return NULL;
}

void argazkiak_garbitu(ElementuenTexturak** texturak)
{
	/* Terrenoak */
	SDL_DestroyTexture((*texturak)->larrea.aurrea);
	SDL_DestroyTexture((*texturak)->ibaia.aurrea);
	SDL_DestroyTexture((*texturak)->mendia.aurrea);
	
	/* Tropak */
	SDL_DestroyTexture((*texturak)->infanteria.aurrea);
	SDL_DestroyTexture((*texturak)->infanteria.atzea);
	SDL_DestroyTexture((*texturak)->infanteria.eskubi);
	SDL_DestroyTexture((*texturak)->infanteria.ezker);

	free(*texturak);
	*texturak = NULL;
}

SDL_Texture* textura_sortu(SDL_Renderer* render, const char* path)
{
	SDL_Texture* textura = NULL;
	SDL_Surface* srfc = NULL;

	if ((srfc = IMG_Load(path)) == NULL)
	{
		fprintf(stderr, "Errorea: %s\n", IMG_GetError());
		goto atera;
	}

	if ((textura = SDL_CreateTextureFromSurface(render, srfc)) == NULL)
	{
		fprintf(stderr, "Errorea: %s\n", IMG_GetError());
		goto atera;
	}

atera:
	SDL_FreeSurface(srfc);
	return textura;
}

bool marraztu_baldosa(Baldosa* baldosa, SDL_Rect* rect)
{
	bool dena_ondo = true;

	switch (baldosa->mota)
	{
	case Larrea:
	{
		if (SDL_RenderCopy(RENDERER, ELEM_TEXT->larrea.aurrea, NULL, rect) < 0)
		{
			fprintf(stderr, "Errorea: %s.\n", SDL_GetError());
			dena_ondo = false;
			goto atera;
		}
		break;
	}
	case Mendia:
	{
		if (SDL_RenderCopy(RENDERER, ELEM_TEXT->mendia.aurrea, NULL, rect) < 0)
		{
			fprintf(stderr, "Errorea: %s.\n", SDL_GetError());
			dena_ondo = false;
			goto atera;
		}
		break;
	}
	case Ibaia:
	{
		if (SDL_RenderCopy(RENDERER, ELEM_TEXT->ibaia.aurrea, NULL, rect) < 0)
		{
			fprintf(stderr, "Errorea: %s.\n", SDL_GetError());
			dena_ondo = false;
			goto atera;
		}
		break;
	}
	default:
		break;
	}

atera:
	return dena_ondo;
}

bool marraztu_tropa(Baldosa* baldosa, SDL_Rect* rect)
{
	TropaStat* tropa = baldosa->tropa;
	bool dena_ondo = true;

	if (tropa != NULL)
	{
		switch (tropa->mota)
		{
		case Infanteria:
		{
			switch (tropa->orientazioa)
			{
			case Aurrea:
				if (SDL_RenderCopy(RENDERER, ELEM_TEXT->infanteria.aurrea, NULL, rect) < 0)
				{
					fprintf(stderr, "Errorea: %s.\n", SDL_GetError());
					dena_ondo = false;
					goto atera;
				}
				break;
			case Atzea:
				if (SDL_RenderCopy(RENDERER, ELEM_TEXT->infanteria.atzea, NULL, rect) < 0)
				{
					fprintf(stderr, "Errorea: %s.\n", SDL_GetError());
					dena_ondo = false;
					goto atera;
				}
				break;
			case Eskubi:
				if (SDL_RenderCopy(RENDERER, ELEM_TEXT->infanteria.eskubi, NULL, rect) < 0)
				{
					fprintf(stderr, "Errorea: %s.\n", SDL_GetError());
					dena_ondo = false;
					goto atera;
				}
				break;
			case Ezker:
				if (SDL_RenderCopy(RENDERER, ELEM_TEXT->infanteria.ezker, NULL, rect) < 0)
				{
					fprintf(stderr, "Errorea: %s.\n", SDL_GetError());
					dena_ondo = false;
					goto atera;
				}
				break;
			default:
				break;
			}
			break;
		}
		default:
			break;
		}
	}

atera:
	return dena_ondo;
}

void kalkulatu_iso(Bekt2D* iso_pos, float x, float y)
{
	iso_pos->x = (int)(x - y);
	iso_pos->y = (int)((x + y) * 0.5);
}

 /*
  *	END: Funtzio pribatuen inplementazioa
  */