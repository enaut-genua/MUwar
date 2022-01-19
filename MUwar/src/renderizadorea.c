#include "renderizadorea.h"
#include "ebentuak.h"

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
	/* Punteroa */
	Textura punteroa;

	/* Aukeratutakoa markatzeko */
	Textura aukeratutakoa;

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

static ElementuenTexturak* argazkiak_kargatu(void);												/* Argazkiak memoriara kargatzen ditu */
static void argazkiak_garbitu(ElementuenTexturak** texturak);									/* Argazkiak memoriatik garbitzen ditu */
static SDL_Texture* textura_sortu(const char* path, uint8_t alpha);								/* Pathean dagoen argazkiaren textura sortzen du */
static bool marraztu_baldosa(Baldosa* baldosa, SDL_Rect* rect);									/* Pasatzen zaion baldosa marrazten du */
static bool marraztu_tropa(Baldosa* baldosa, SDL_Rect* rect);									/* Baldosan dagoen tropa marrazten du */
static bool marraztu_orientazioa(TropaStat* tropa, SDL_Rect* rect);								/* marraztu_tropa(2) funtziotik deitzen da, orientazioaren arabera tropa marrazten du */
static bool marraztu_punteroa(Mapa* mapa, Baldosa* baldosa);									/* Marraztu punteroa */
static bool marraztu_informazioa(Mapa* mapa);
static bool marraztu_aukeratuta(Baldosa* baldosa, SDL_Rect* rect);
static void kalkulatu_isometriko(Bekt2D* iso_pos, float x, float y);							/* Koordenada isometrikoak kalkulatzen ditu */
static void kalkulatu_kartesiarrak(Bekt2D* kartes_pos, int x, int y);							/* Koordenada kartesiarrak kalkulatzen ditu */

/*
 *	END: Funtzio pribatuak
 */


 /*
  *	START: Aldagai global pribatuak
  */

static SDL_Window* WINDOW = NULL;
static SDL_Renderer* RENDERER = NULL;
static ElementuenTexturak* ELEM_TEXT = NULL;
static Bekt2D MAPA_HASIERA = { 100, 300 };
static int ARGAZKI_TAMAINA = 100;

/*
 *	END: Aldagai global pribatuak
 */

bool render_sortu(char* titulo, int xpos, int ypos, int width, int height, bool fullscreen)
{
	bool dena_ondo = true;
	int banderak = fullscreen ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0;

	/* SDL libreria guztiak hasieratzen ditu, hala ezean errore bat emango du */
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		fprintf(stderr, "Errorea: %s\n", SDL_GetError());
		dena_ondo = false;
		goto atera;
	}

	/* Lehio bat sortzen du, hala ezean errore bat emango du */
	if ((WINDOW = SDL_CreateWindow(titulo, xpos, ypos, width, height, banderak | SDL_WINDOW_RESIZABLE | SDL_WINDOW_FOREIGN)) == NULL)
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
	if (SDL_SetRenderDrawColor(RENDERER, 0xAA, 0xAA, 0x3B, SDL_ALPHA_OPAQUE) < 0)
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

	if ((ELEM_TEXT = argazkiak_kargatu()) == NULL)
	{
		fprintf(stderr, "Errorea: Ezin izan dira texturak sortu.");
		dena_ondo = false;
	};

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

bool render_marraztu(Mapa* mapa)
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
			kalkulatu_isometriko(&iso_pos, (ARGAZKI_TAMAINA * 0.5f) * i + MAPA_HASIERA.x, (ARGAZKI_TAMAINA * 0.5f) * j - MAPA_HASIERA.y);

			laukia.x = iso_pos.x;
			laukia.y = iso_pos.y;

			Baldosa* baldosa = mapa_lortu_pos(mapa, i, j);

			if (marraztu_baldosa(baldosa, &laukia) == false)
			{
				fprintf(stderr, "Errorea: Ezin izan da baldosa marraztu.\n");
				dena_ondo = false;
				goto atera;
			}

			if (marraztu_tropa(baldosa, &laukia) == false)
			{
				fprintf(stderr, "Errorea: Ezin izan da tropa marraztu.\n");
				dena_ondo = false;
				goto atera;
			}

			if (marraztu_punteroa(mapa, baldosa) == false)
			{
				fprintf(stderr, "Errorea: Ezin izan da punteroa marraztu.\n");
				dena_ondo = false;
				goto atera;
			}

			if (marraztu_aukeratuta(baldosa, &laukia) == false)
			{
				fprintf(stderr, "Errorea: Ezin izan da aukeratutakoa marraztu.\n");
				dena_ondo = false;
				goto atera;
			}
		}
	}

	if (marraztu_informazioa(mapa) == false)
	{
		fprintf(stderr, "Errorea: Ezin izan da punteroa marraztu.\n");
		dena_ondo = false;
		goto atera;
	}

	SDL_RenderPresent(RENDERER);

atera:
	return dena_ondo;
}

void render_handitu_argazkiak(void)
{
	if (ARGAZKI_TAMAINA < 500)
	{
		ARGAZKI_TAMAINA += 5;
	}
}

void render_txikitu_argazkiak(void)
{
	if (ARGAZKI_TAMAINA > 70)
	{
		ARGAZKI_TAMAINA -= 5;
	}
}

void render_mugitu_mapa_gora(void)
{
	MAPA_HASIERA.x += (int)(ARGAZKI_TAMAINA * 0.5f);
	MAPA_HASIERA.y -= (int)(ARGAZKI_TAMAINA * 0.5f);
}

void render_mugitu_mapa_behera(void)
{
	MAPA_HASIERA.x -= (int)(ARGAZKI_TAMAINA * 0.5f);
	MAPA_HASIERA.y += (int)(ARGAZKI_TAMAINA * 0.5f);
}

void render_mugitu_mapa_eskubi(void)
{
	MAPA_HASIERA.x -= (int)(ARGAZKI_TAMAINA * 0.5f);
	MAPA_HASIERA.y -= (int)(ARGAZKI_TAMAINA * 0.5f);
}

void render_mugitu_mapa_ezker(void)
{
	MAPA_HASIERA.x += (int)(ARGAZKI_TAMAINA * 0.5f);
	MAPA_HASIERA.y += (int)(ARGAZKI_TAMAINA * 0.5f);
}

/*
 *	START: Funtzio pribatuen inplementazioa
 */

ElementuenTexturak* argazkiak_kargatu(void)
{
	ElementuenTexturak* texturak = NULL;

	/* Sortu ElementuTexturak structa */
	if ((texturak = (ElementuenTexturak*)calloc(1, sizeof(ElementuenTexturak))) == NULL)
	{
		fprintf(stderr, "Errorea: Ezin izan da ElementuanTexturak estruktura sortu.\n");
		goto errorea;
	}

	/*
	 * Kargatu Aukeratutakoaren Textura
	 */

	if ((texturak->aukeratutakoa.aurrea = textura_sortu("res\\img\\TILEROSE.png", 50)) == NULL)
	{
		fprintf(stderr, "Errorea: Ezin izan da aukeratutakoaren textura sortu.\n");
		goto errorea;
	}

	/*
	 * Kargatu Punteroaren Textura
	 */

	if ((texturak->punteroa.aurrea = textura_sortu("res\\img\\ISOTILE.png", SDL_ALPHA_OPAQUE)) == NULL)
	{
		fprintf(stderr, "Errorea: Ezin izan da punteroaren textura sortu.\n");
		goto errorea;
	}

	/*
	 * Kargatu Terrenoaren Texturak
	 */

	 /* Larrea */
	if ((texturak->larrea.aurrea = textura_sortu("res\\img\\GRASS.png", SDL_ALPHA_OPAQUE)) == NULL)
	{
		fprintf(stderr, "Errorea: Ezin izan da larrearen textura sortu.\n");
		goto errorea;
	}

	/* Mendia */
	if ((texturak->mendia.aurrea = textura_sortu("res\\img\\MOUNTAIN.png", SDL_ALPHA_OPAQUE)) == NULL)
	{
		fprintf(stderr, "Errorea: Ezin izan da mendiaren textura sortu.\n");
		goto errorea;
	}

	/* Ibaia */
	if ((texturak->ibaia.aurrea = textura_sortu("res\\img\\WATER.png", SDL_ALPHA_OPAQUE)) == NULL)
	{
		fprintf(stderr, "Errorea: Ezin izan da ibaiaren textura sortu.\n");
		goto errorea;
	}

	/*
	 * Kargatu Tropen Texturak
	 */

	 /* Infanteria */
	if ((texturak->infanteria.aurrea = textura_sortu("res\\img\\PERTSONA.png", SDL_ALPHA_OPAQUE)) == NULL)
	{
		fprintf(stderr, "Errorea: Ezin izan da infanteriaren aurreko textura sortu.\n");
		goto errorea;
	}

	if ((texturak->infanteria.atzea = textura_sortu("res\\img\\PERTSONA4.png", SDL_ALPHA_OPAQUE)) == NULL)
	{
		fprintf(stderr, "Errorea: Ezin izan da infanteriaren aurreko textura sortu.\n");
		goto errorea;
	}

	if ((texturak->infanteria.ezker = textura_sortu("res\\img\\PERTSONA2.png", SDL_ALPHA_OPAQUE)) == NULL)
	{
		fprintf(stderr, "Errorea: Ezin izan da infanteriaren aurreko textura sortu.\n");
		goto errorea;
	}

	if ((texturak->infanteria.eskubi = textura_sortu("res\\img\\PERTSONA3.png", SDL_ALPHA_OPAQUE)) == NULL)
	{
		fprintf(stderr, "Errorea: Ezin izan da infanteriaren aurreko textura sortu.\n");
		goto errorea;
	}

	return texturak;

errorea:
	argazkiak_garbitu(&texturak);
	free(texturak);
	return NULL;
}

void argazkiak_garbitu(ElementuenTexturak** texturak)
{
	if (*texturak != NULL)
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
}

SDL_Texture* textura_sortu(const char* path, uint8_t alpha)
{
	SDL_Texture* textura = NULL;
	SDL_Surface* srfc = NULL;

	if ((srfc = IMG_Load(path)) == NULL)
	{
		fprintf(stderr, "Errorea: %s\n", IMG_GetError());
		goto atera;
	}

	if ((textura = SDL_CreateTextureFromSurface(RENDERER, srfc)) == NULL)
	{
		fprintf(stderr, "Errorea: %s\n", SDL_GetError());
		goto atera;
	}

	if (SDL_SetTextureAlphaMod(textura, alpha) < 0)
	{
		fprintf(stderr, "Errorea: %s\n", SDL_GetError());
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
		}
		break;
	}
	case Mendia:
	{
		if (SDL_RenderCopy(RENDERER, ELEM_TEXT->mendia.aurrea, NULL, rect) < 0)
		{
			fprintf(stderr, "Errorea: %s.\n", SDL_GetError());
			dena_ondo = false;
		}
		break;
	}
	case Ibaia:
	{
		if (SDL_RenderCopy(RENDERER, ELEM_TEXT->ibaia.aurrea, NULL, rect) < 0)
		{
			fprintf(stderr, "Errorea: %s.\n", SDL_GetError());
			dena_ondo = false;
		}
		break;
	}
	default:
		break;
	}

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
			dena_ondo = marraztu_orientazioa(tropa, rect);
			break;
		}
		default:
			break;
		}
	}

	return dena_ondo;
}

bool marraztu_orientazioa(TropaStat* tropa, SDL_Rect* rect)
{
	bool dena_ondo = true;

	switch (tropa->orientazioa)
	{
	case Aurrea:
		if (SDL_RenderCopy(RENDERER, ELEM_TEXT->infanteria.aurrea, NULL, rect) < 0)
		{
			fprintf(stderr, "Errorea: %s.\n", SDL_GetError());
			dena_ondo = false;
		}
		break;
	case Atzea:
		if (SDL_RenderCopy(RENDERER, ELEM_TEXT->infanteria.atzea, NULL, rect) < 0)
		{
			fprintf(stderr, "Errorea: %s.\n", SDL_GetError());
			dena_ondo = false;
		}
		break;
	case Eskubi:
		if (SDL_RenderCopy(RENDERER, ELEM_TEXT->infanteria.eskubi, NULL, rect) < 0)
		{
			fprintf(stderr, "Errorea: %s.\n", SDL_GetError());
			dena_ondo = false;
		}
		break;
	case Ezker:
		if (SDL_RenderCopy(RENDERER, ELEM_TEXT->infanteria.ezker, NULL, rect) < 0)
		{
			fprintf(stderr, "Errorea: %s.\n", SDL_GetError());
			dena_ondo = false;
		}
		break;
	default:
		break;
	}

	return dena_ondo;
}

bool marraztu_punteroa(Mapa* mapa, Baldosa* baldosa)
{
	bool dena_ondo = true;
	SDL_Rect laukia = { 0, 0, ARGAZKI_TAMAINA, ARGAZKI_TAMAINA };
	Bekt2D xagu_pos = ebentuak_lortu_xagu_pos();
	Bekt2D pos_kart = { 0 };
	Bekt2D aukeratutako_baldosa_pos = { 0 };

	kalkulatu_kartesiarrak(&pos_kart, xagu_pos.x, xagu_pos.y);

	aukeratutako_baldosa_pos.x = (int)((pos_kart.x - ARGAZKI_TAMAINA * 0.5 - MAPA_HASIERA.x) / (ARGAZKI_TAMAINA * 0.5f));
	aukeratutako_baldosa_pos.y = (int)((pos_kart.y + MAPA_HASIERA.y) / (ARGAZKI_TAMAINA * 0.5f));

	if ((mapa_lortu_pos(mapa, aukeratutako_baldosa_pos.x, aukeratutako_baldosa_pos.y) == baldosa)
		&& (aukeratutako_baldosa_pos.x < mapa->tamaina_x && aukeratutako_baldosa_pos.y < mapa->tamaina_y) 
		&& (aukeratutako_baldosa_pos.x >= 0 && aukeratutako_baldosa_pos.y >= 0))
	{
		Bekt2D iso_pos = { 0 };

		kalkulatu_isometriko(&iso_pos, (ARGAZKI_TAMAINA * 0.5f) * aukeratutako_baldosa_pos.x + MAPA_HASIERA.x, (ARGAZKI_TAMAINA * 0.5f) * aukeratutako_baldosa_pos.y - MAPA_HASIERA.y);

		laukia.x = iso_pos.x;
		laukia.y = iso_pos.y;

		if (SDL_RenderCopy(RENDERER, ELEM_TEXT->punteroa.aurrea, NULL, &laukia) < 0)
		{
			fprintf(stderr, "Errorea: %s.\n", SDL_GetError());
			dena_ondo = false;
		}
	}
	
	return dena_ondo;
}

bool marraztu_informazioa(Mapa* mapa)
{
	bool dena_ondo = true;
	SDL_Rect laukia = { 0, 0, 100, 100 };
	Bekt2D xagu_pos = ebentuak_lortu_xagu_pos();
	Bekt2D pos_kart = { 0 };
	Bekt2D aukeratutako_baldosa_pos = { 0 };
	Baldosa* aukeratutako_baldosa = NULL;

	kalkulatu_kartesiarrak(&pos_kart, xagu_pos.x, xagu_pos.y);

	aukeratutako_baldosa_pos.x = (int)((pos_kart.x - 50 - MAPA_HASIERA.x) / (ARGAZKI_TAMAINA * 0.5f));
	aukeratutako_baldosa_pos.y = (int)((pos_kart.y + MAPA_HASIERA.y) / (ARGAZKI_TAMAINA * 0.5f));

	if ((aukeratutako_baldosa_pos.x < mapa->tamaina_x && aukeratutako_baldosa_pos.y < mapa->tamaina_y) && (aukeratutako_baldosa_pos.x >= 0 && aukeratutako_baldosa_pos.y >= 0))
	{
		aukeratutako_baldosa = mapa_lortu_pos(mapa, aukeratutako_baldosa_pos.x, aukeratutako_baldosa_pos.y);
		if (marraztu_baldosa(aukeratutako_baldosa, &laukia) == false)
		{
			fprintf(stderr, "Errorea: Ezin izan da info baldosa marraztu.\n");
			dena_ondo = false;
			goto atera;
		}

		if (marraztu_tropa(aukeratutako_baldosa, &laukia) == false)
		{
			fprintf(stderr, "Errorea: Ezin izan da info tropa marraztu.\n");
			dena_ondo = false;
			goto atera;
		}
	}

atera:
	return dena_ondo;
}

bool marraztu_aukeratuta(Baldosa* baldosa, SDL_Rect* rect)
{
	bool dena_ondo = true;

	if (baldosa->aukeratuta == true)
	{
		if (SDL_RenderCopy(RENDERER, ELEM_TEXT->aukeratutakoa.aurrea, NULL, rect) < 0)
		{
			fprintf(stderr, "Errorea: %s.\n", SDL_GetError());
			dena_ondo = false;
		}
	}

	return dena_ondo;
}

void kalkulatu_isometriko(Bekt2D* iso_pos, float x, float y)
{
	iso_pos->x = (int)(x - y);
	iso_pos->y = (int)((x + y) * 0.5);
}

void kalkulatu_kartesiarrak(Bekt2D* kartes_pos, int x, int y)
{
	kartes_pos->x = (int)((2 * y + x) / 2);
	kartes_pos->y = (int)((2 * y - x) / 2);
}

/*
 *	END: Funtzio pribatuen inplementazioa
 */