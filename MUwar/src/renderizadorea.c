#define _CRT_SECURE_NO_WARNINGS

#include "renderizadorea.h"
#include "ebentuak.h"
#include "kalkuloak.h"
#include "jokoa.h"

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
	Textura rangoa;

	/* Terrenoak */
	Textura basamortua;
	Textura base_gorria;
	Textura base_urdina;
	Textura baso_moztua;
	Textura basoa;
	Textura fabrika;
	Textura herri_hautsia;
	Textura herria;
	Textura ibaia;
	Textura karretera;
	Textura larrea;
	Textura mendi_hautsia;
	Textura mendia;

	/* Tropak */
	Textura infanteria_urdina;
	Textura infanteria_gorria;
	Textura infanteria_mek_urdina;
	Textura infanteria_mek_gorria;
	Textura rekon_urdina;
	Textura rekon_gorria;
	Textura tanke_urdina;
	Textura tanke_gorria;

} ElementuenTexturak;

/*
 *	END: Estruktura pribatuak
 */

 /*
  *	START: Funtzio pribatuak
  */

static ElementuenTexturak* argazkiak_kargatu(void);												/* Argazkiak memoriara kargatzen ditu */
static void argazkiak_garbitu(ElementuenTexturak** texturak);									/* Argazkiak memoriatik garbitzen ditu */
static bool letra_tipoa_kargatu(void);
static void letra_tipoa_garbitu(void);
static SDL_Texture* textura_sortu(const char* path, uint8_t alpha);								/* Pathean dagoen argazkiaren textura sortzen du */
static bool marraztu_baldosa(Baldosa* baldosa, SDL_Rect* rect);									/* Pasatzen zaion baldosa marrazten du */
static bool marraztu_tropa(Baldosa* baldosa, SDL_Rect* rect);									/* Baldosan dagoen tropa marrazten du */
static bool marraztu_orientazioa(TropaStat* tropa, Textura* textura, SDL_Rect* rect);			/* marraztu_tropa(2) funtziotik deitzen da, orientazioaren arabera tropa marrazten du */
static bool marraztu_punteroa(Mapa* mapa, Baldosa* baldosa);									/* Marraztu punteroa */
static bool marraztu_informazioa(Mapa* mapa);
static bool marraztu_stat_textua(Mapa* mapa);
static bool marraztu_textua(SDL_Rect* rect, char* str);
static bool marraztu_markatua(Baldosa* baldosa, SDL_Rect* rect);
static bool marraztu_tropa_aukeratzeko_menua(void);

/*
 *	END: Funtzio pribatuak
 */


 /*
  *	START: Aldagai global pribatuak
  */

static SDL_Window* WINDOW = NULL;
static SDL_Renderer* RENDERER = NULL;
static TTF_Font* FONT = NULL;

static ElementuenTexturak* ELEM_TEXT = NULL;
static Bekt2D MAPA_NONDIK_HASI_MARRAZTEN = { 100, 300 };
static int ARGAZKI_TAMAINA = 100;

/*
 *	END: Aldagai global pribatuak
 */

 /*
  *	START: Konstanteak
  */

const char* LEIHOAREN_IZENA = "MUwar";

/*
 *	END: Konstanteak
 */


bool render_sortu(int xpos, int ypos, int width, int height, bool fullscreen)
{
	bool dena_ondo = true;
	int banderak = fullscreen ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0;

	/* SDL libreria guztiak hasieratzen ditu, hala ezean errore bat emango du */
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		ERROREA(SDL_GetError());
		dena_ondo = false;
		goto atera;
	}

	/* Lehio bat sortzen du, hala ezean errore bat emango du */
	if ((WINDOW = SDL_CreateWindow(LEIHOAREN_IZENA, xpos, ypos, width, height, banderak | SDL_WINDOW_RESIZABLE | SDL_WINDOW_FOREIGN)) == NULL)
	{
		ERROREA(SDL_GetError());
		dena_ondo = false;
		goto atera;
	}

	/* Renderizadore bat sortzen du, hala ezean errore bat emango du */
	if ((RENDERER = SDL_CreateRenderer(WINDOW, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE | SDL_RENDERER_PRESENTVSYNC)) == NULL)
	{
		ERROREA(SDL_GetError());
		dena_ondo = false;
		goto atera;
	}

	/* Ze kolorearekin margotzea nahi det esaten da, hala ezean errore bat emango du */
	if (SDL_SetRenderDrawColor(RENDERER, 0xAA, 0xAA, 0x3B, SDL_ALPHA_OPAQUE) < 0)
	{
		ERROREA(SDL_GetError());
		dena_ondo = false;
		goto atera;
	}

	/* IMG inzializatu */
	if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
	{
		ERROREA(IMG_GetError());
		dena_ondo = false;
		goto atera;
	}

	if ((ELEM_TEXT = argazkiak_kargatu()) == NULL)
	{
		ERROREA("Ez dira texturak sortu.");
		dena_ondo = false;
		goto atera;
	};

	/* TTF inizializatu */
	if (TTF_Init() < 0)
	{
		ERROREA(TTF_GetError());
		dena_ondo = false;
		goto atera;
	}

	letra_tipoa_kargatu();

	OHARRA("Lehioa, renderizadorea eta texturak zuzen sortu dira.");

atera:
	return dena_ondo;
}

void render_garbitu(void)
{
	letra_tipoa_garbitu();
	argazkiak_garbitu(&ELEM_TEXT);
	SDL_DestroyRenderer(RENDERER);
	SDL_DestroyWindow(WINDOW);
	SDL_Quit();

	OHARRA("Lehioa, renderizadorea eta texturak garbitu dira.");
}

bool render_marraztu(Mapa* mapa)
{
	bool dena_ondo = true;
	SDL_Rect laukia = { 0 };
	Bekt2D iso_pos = { 0 };

	laukia.w = laukia.h = ARGAZKI_TAMAINA;

	if (SDL_RenderClear(RENDERER) < 0)
	{
		ERROREA(SDL_GetError());
		dena_ondo = false;
		goto atera;
	}

	for (int i = 0; i < mapa->tamaina_x; ++i)
	{
		for (int j = 0; j < mapa->tamaina_y; ++j)
		{
			kalkulatu_isometriko(&iso_pos, (ARGAZKI_TAMAINA * 0.5f) * i + MAPA_NONDIK_HASI_MARRAZTEN.x, (ARGAZKI_TAMAINA * 0.5f) * j - MAPA_NONDIK_HASI_MARRAZTEN.y);

			laukia.x = iso_pos.x;
			laukia.y = iso_pos.y;

			Baldosa* baldosa = mapa_lortu_pos(mapa, i, j);

			if (marraztu_baldosa(baldosa, &laukia) == false)
			{
				ERROREA("Ezin izan da baldosa marraztu");
				dena_ondo = false;
				goto atera;
			}

			if (marraztu_tropa(baldosa, &laukia) == false)
			{
				ERROREA("Ezin izan da tropa marraztu.");
				dena_ondo = false;
				goto atera;
			}

			if (marraztu_punteroa(mapa, baldosa) == false)
			{
				ERROREA("Ezin izan da punteroa marraztu.");
				dena_ondo = false;
				goto atera;
			}

			if (marraztu_markatua(baldosa, &laukia) == false)
			{
				ERROREA("Ezin izan da aukeratutakoa marraztu.");
				dena_ondo = false;
				goto atera;
			}
		}
	}

	if (marraztu_informazioa(mapa) == false)
	{
		ERROREA("Ezin izan da punteroa marraztu.");
		dena_ondo = false;
		goto atera;
	}

	if (marraztu_stat_textua(mapa) == false)
	{
		ERROREA("Ezin izan dira estadistikak marraztu.");
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

void render_mugitu_mapa_gora(float dt)
{
	MAPA_NONDIK_HASI_MARRAZTEN.x += (int)(floor(ARGAZKI_TAMAINA * dt * 10));
	MAPA_NONDIK_HASI_MARRAZTEN.y -= (int)(floor(ARGAZKI_TAMAINA * dt * 10));
}

void render_mugitu_mapa_behera(float dt)
{
	MAPA_NONDIK_HASI_MARRAZTEN.x -= (int)(floor(ARGAZKI_TAMAINA * dt * 10));
	MAPA_NONDIK_HASI_MARRAZTEN.y += (int)(floor(ARGAZKI_TAMAINA * dt * 10));
}

void render_mugitu_mapa_eskubi(float dt)
{
	MAPA_NONDIK_HASI_MARRAZTEN.x -= (int)(floor(ARGAZKI_TAMAINA * dt * 10));
	MAPA_NONDIK_HASI_MARRAZTEN.y -= (int)(floor(ARGAZKI_TAMAINA * dt * 10));
}

void render_mugitu_mapa_ezker(float dt)
{
	MAPA_NONDIK_HASI_MARRAZTEN.x += (int)(floor(ARGAZKI_TAMAINA * dt * 10));
	MAPA_NONDIK_HASI_MARRAZTEN.y += (int)(floor(ARGAZKI_TAMAINA * dt * 10));
}

void render_erakutsi_fps(float dt)
{
	static float tenporizadorea = 0;
	static int fotogramak = 0;

	char str[20] = { 0 };

	tenporizadorea += dt;
	++fotogramak;

	if (tenporizadorea >= 1.0f)
	{
		sprintf(str, "%s - FPS: %d", LEIHOAREN_IZENA, fotogramak);
		SDL_SetWindowTitle(WINDOW, str);
		--tenporizadorea;
		fotogramak = 0;
	}

}

int render_lortu_argazki_tamaina(void)
{
	return ARGAZKI_TAMAINA;
}

Bekt2D render_lortu_mapa_nondik_hasi_marrazten(void)
{
	return MAPA_NONDIK_HASI_MARRAZTEN;
}

Bekt2D render_lortu_leiho_tamaina(void)
{
	Bekt2D lehio_tamaina = { 0 };
	SDL_GetWindowSize(WINDOW, &lehio_tamaina.x, &lehio_tamaina.y);
	return lehio_tamaina;
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
		ERROREA("Ezin izan da ElementuanTexturak estruktura sortu.");
		goto errorea;
	}

	/*
	 * Kargatu Aukeratutakoaren Textura
	 */

	if ((texturak->rangoa.aurrea = textura_sortu("res/img/jokua/bloke_laranja.png", 80)) == NULL)
	{
		ERROREA("Ezin izan da aukeratutakoaren textura sortu.");
		goto errorea;
	}

	/*
	 * Kargatu Punteroaren Textura
	 */

	if ((texturak->punteroa.aurrea = textura_sortu("res/img/jokua/punteroa.png", SDL_ALPHA_OPAQUE)) == NULL)
	{
		ERROREA("Ezin izan da punteroraren textura sortu.");
		goto errorea;
	}

	/*
	 * Kargatu Terrenoaren Texturak
	 */

	 /* Basamortua */
	if ((texturak->basamortua.aurrea = textura_sortu("res/img/jokua/basamortua.png", SDL_ALPHA_OPAQUE)) == NULL)
	{
		ERROREA("Ezin izan da basamortuaren textura sortu.");
		goto errorea;
	}

	/* Base gorria */
	if ((texturak->base_gorria.aurrea = textura_sortu("res/img/jokua/base_gorria.png", SDL_ALPHA_OPAQUE)) == NULL)
	{
		ERROREA("Ezin izan base gorriaren textura sortu.");
		goto errorea;
	}

	/* Base urdina */
	if ((texturak->base_urdina.aurrea = textura_sortu("res/img/jokua/base_urdina.png", SDL_ALPHA_OPAQUE)) == NULL)
	{
		fprintf(stderr, "Errorea: Ezin izan da base urdinaren textura sortu.\n");
		goto errorea;
	}

	/* Baso moztua */
	if ((texturak->baso_moztua.aurrea = textura_sortu("res/img/jokua/baso_moztua.png", SDL_ALPHA_OPAQUE)) == NULL)
	{
		fprintf(stderr, "Errorea: Ezin izan da baso moztuaren textura sortu.\n");
		goto errorea;
	}

	/* Basoa */
	if ((texturak->basoa.aurrea = textura_sortu("res/img/jokua/basoa.png", SDL_ALPHA_OPAQUE)) == NULL)
	{
		ERROREA("Ezin izan da basoaren textura sortu.");
		goto errorea;
	}

	/* Herri hautsia */
	if ((texturak->herri_hautsia.aurrea = textura_sortu("res/img/jokua/herri_hautsia.png", SDL_ALPHA_OPAQUE)) == NULL)
	{
		ERROREA("Ezin izan da herri hautsiaren textura sortu.");
		goto errorea;
	}

	/* Herria */
	if ((texturak->herria.aurrea = textura_sortu("res/img/jokua/herria.png", SDL_ALPHA_OPAQUE)) == NULL)
	{
		ERROREA("Ezin izan da herriaren textura sortu.");
		goto errorea;
	}

	/* Ibaia */
	if ((texturak->ibaia.aurrea = textura_sortu("res/img/jokua/ura.png", SDL_ALPHA_OPAQUE)) == NULL)
	{
		ERROREA("Ezin izan da ibaiaren textura sortu.");
		goto errorea;
	}

	/* Karretera */
	if ((texturak->karretera.aurrea = textura_sortu("res/img/jokua/karretera.png", SDL_ALPHA_OPAQUE)) == NULL)
	{
		ERROREA("Ezin izan da karreteraren textura sortu.");
		goto errorea;
	}

	/* Larrea */
	if ((texturak->larrea.aurrea = textura_sortu("res/img/jokua/larrea.png", SDL_ALPHA_OPAQUE)) == NULL)
	{
		ERROREA("Ezin izan da larrearen textura sortu.");
		goto errorea;
	}

	/* Mendi hautsia */
	if ((texturak->mendi_hautsia.aurrea = textura_sortu("res/img/jokua/mendi_hautsia.png", SDL_ALPHA_OPAQUE)) == NULL)
	{
		ERROREA("Ezin izan da mendiaren textura sortu.");
		goto errorea;
	}

	/* Mendia */
	if ((texturak->mendia.aurrea = textura_sortu("res/img/jokua/mendia.png", SDL_ALPHA_OPAQUE)) == NULL)
	{
		ERROREA("Ezin izan da mendiaren textura sortu.");
		goto errorea;
	}

	/*
	 * Kargatu Tropen Texturak
	 */

	 /* Infanteria */
	if ((texturak->infanteria_urdina.aurrea = textura_sortu("res/img/jokua/infanteria_urdina_aurrea.png", SDL_ALPHA_OPAQUE)) == NULL)
	{
		ERROREA("Ezin izan da infanteria urdinaren aurreko textura sortu.");
		goto errorea;
	}
	if ((texturak->infanteria_urdina.atzea = textura_sortu("res/img/jokua/infanteria_urdina_atzea.png", SDL_ALPHA_OPAQUE)) == NULL)
	{
		ERROREA("Ezin izan da infanteria urdinaren atzeko textura sortu.");
		goto errorea;
	}
	if ((texturak->infanteria_urdina.ezker = textura_sortu("res/img/jokua/infanteria_urdina_ezkerra.png", SDL_ALPHA_OPAQUE)) == NULL)
	{
		ERROREA("Ezin izan da infanteria urdinaren ezkerreko textura sortu.");
		goto errorea;
	}
	if ((texturak->infanteria_urdina.eskubi = textura_sortu("res/img/jokua/infanteria_urdina_eskubi.png", SDL_ALPHA_OPAQUE)) == NULL)
	{
		ERROREA("Ezin izan da infanteria urdinaren eskubiko textura sortu.");
		goto errorea;
	}

	if ((texturak->infanteria_gorria.aurrea = textura_sortu("res/img/jokua/infanteria_gorria_aurrea.png", SDL_ALPHA_OPAQUE)) == NULL)
	{
		ERROREA("Ezin izan da infanteria gorriaren aurreko textura sortu.");
		goto errorea;
	}
	if ((texturak->infanteria_gorria.atzea = textura_sortu("res/img/jokua/infanteria_gorria_atzea.png", SDL_ALPHA_OPAQUE)) == NULL)
	{
		ERROREA("Ezin izan da infanteria gorriaren atzeko textura sortu.");
		goto errorea;
	}
	if ((texturak->infanteria_gorria.ezker = textura_sortu("res/img/jokua/infanteria_gorria_ezkerra.png", SDL_ALPHA_OPAQUE)) == NULL)
	{
		ERROREA("Ezin izan da infanteria gorriaren ezkerreko textura sortu.");
		goto errorea;
	}
	if ((texturak->infanteria_gorria.eskubi = textura_sortu("res/img/jokua/infanteria_gorria_eskubi.png", SDL_ALPHA_OPAQUE)) == NULL)
	{
		ERROREA("Ezin izan da infanteria gorriaren eskubiko textura sortu.");
		goto errorea;
	}

	/* Infanteria Mek */
	if ((texturak->infanteria_mek_urdina.aurrea = textura_sortu("res/img/jokua/infanteria_mek_urdina_aurrea.png", SDL_ALPHA_OPAQUE)) == NULL)
	{
		ERROREA("Ezin izan da infanteria_mek urdinaren aurreko textura sortu.");
		goto errorea;
	}
	if ((texturak->infanteria_mek_urdina.atzea = textura_sortu("res/img/jokua/infanteria_mek_urdina_atzea.png", SDL_ALPHA_OPAQUE)) == NULL)
	{
		ERROREA("Ezin izan da infanteria_mek urdinaren atzeko textura sortu.");
		goto errorea;
	}
	if ((texturak->infanteria_mek_urdina.ezker = textura_sortu("res/img/jokua/infanteria_mek_urdina_ezkerra.png", SDL_ALPHA_OPAQUE)) == NULL)
	{
		ERROREA("Ezin izan da infanteria_mek urdinaren ezkerreko textura sortu.");
		goto errorea;
	}
	if ((texturak->infanteria_mek_urdina.eskubi = textura_sortu("res/img/jokua/infanteria_mek_urdina_eskubi.png", SDL_ALPHA_OPAQUE)) == NULL)
	{
		ERROREA("Ezin izan da infanteria_mek urdinaren eskubiko textura sortu.");
		goto errorea;
	}

	if ((texturak->infanteria_mek_gorria.aurrea = textura_sortu("res/img/jokua/infanteria_mek_gorria_aurrea.png", SDL_ALPHA_OPAQUE)) == NULL)
	{
		ERROREA("Ezin izan da infanteria_mek gorriaren aurreko textura sortu.");
		goto errorea;
	}
	if ((texturak->infanteria_mek_gorria.atzea = textura_sortu("res/img/jokua/infanteria_mek_gorria_atzea.png", SDL_ALPHA_OPAQUE)) == NULL)
	{
		ERROREA("Ezin izan da infanteria_mek gorriaren atzeko textura sortu.");
		goto errorea;
	}
	if ((texturak->infanteria_mek_gorria.ezker = textura_sortu("res/img/jokua/infanteria_mek_gorria_ezkerra.png", SDL_ALPHA_OPAQUE)) == NULL)
	{
		ERROREA("Ezin izan da infanteria_mek gorriaren ezkerreko textura sortu.");
		goto errorea;
	}
	if ((texturak->infanteria_mek_gorria.eskubi = textura_sortu("res/img/jokua/infanteria_mek_gorria_eskubi.png", SDL_ALPHA_OPAQUE)) == NULL)
	{
		ERROREA("Ezin izan da infanteria_mek gorriaren eskubiko textura sortu.");
		goto errorea;
	}

	/* Rekon */
	if ((texturak->rekon_urdina.aurrea = textura_sortu("res/img/jokua/rekon_urdina_aurrea.png", SDL_ALPHA_OPAQUE)) == NULL)
	{
		ERROREA("Ezin izan da rekon urdinaren aurreko textura sortu.");
		goto errorea;
	}
	if ((texturak->rekon_urdina.atzea = textura_sortu("res/img/jokua/rekon_urdina_atzea.png", SDL_ALPHA_OPAQUE)) == NULL)
	{
		ERROREA("Ezin izan da rekon urdinaren atzeko textura sortu.");
		goto errorea;
	}
	if ((texturak->rekon_urdina.ezker = textura_sortu("res/img/jokua/rekon_urdina_ezkerra.png", SDL_ALPHA_OPAQUE)) == NULL)
	{
		ERROREA("Ezin izan da rekon urdinaren ezkerreko textura sortu.");
		goto errorea;
	}
	if ((texturak->rekon_urdina.eskubi = textura_sortu("res/img/jokua/rekon_urdina_eskubi.png", SDL_ALPHA_OPAQUE)) == NULL)
	{
		ERROREA("Ezin izan da rekon urdinaren eskubiko textura sortu.");
		goto errorea;
	}

	if ((texturak->rekon_gorria.aurrea = textura_sortu("res/img/jokua/rekon_gorria_aurrea.png", SDL_ALPHA_OPAQUE)) == NULL)
	{
		ERROREA("Ezin izan da rekon gorriaren aurreko textura sortu.");
		goto errorea;
	}
	if ((texturak->rekon_gorria.atzea = textura_sortu("res/img/jokua/rekon_gorria_atzea.png", SDL_ALPHA_OPAQUE)) == NULL)
	{
		ERROREA("Ezin izan da rekon gorriaren atzeko textura sortu.");
		goto errorea;
	}
	if ((texturak->rekon_gorria.ezker = textura_sortu("res/img/jokua/rekon_gorria_ezkerra.png", SDL_ALPHA_OPAQUE)) == NULL)
	{
		ERROREA("Ezin izan da rekon gorriaren ezkerreko textura sortu.");
		goto errorea;
	}
	if ((texturak->rekon_gorria.eskubi = textura_sortu("res/img/jokua/rekon_gorria_eskubi.png", SDL_ALPHA_OPAQUE)) == NULL)
	{
		ERROREA("Ezin izan da rekon gorriaren eskubiko textura sortu.");
		goto errorea;
	}

	/* Tanke */
	if ((texturak->tanke_urdina.aurrea = textura_sortu("res/img/jokua/tanke_urdina_aurrea.png", SDL_ALPHA_OPAQUE)) == NULL)
	{
		ERROREA("Ezin izan da tanke urdinaren aurreko textura sortu.");
		goto errorea;
	}
	if ((texturak->tanke_urdina.atzea = textura_sortu("res/img/jokua/tanke_urdina_atzea.png", SDL_ALPHA_OPAQUE)) == NULL)
	{
		ERROREA("Ezin izan da tanke urdinaren atzeko textura sortu.");
		goto errorea;
	}
	if ((texturak->tanke_urdina.ezker = textura_sortu("res/img/jokua/tanke_urdina_ezkerra.png", SDL_ALPHA_OPAQUE)) == NULL)
	{
		ERROREA("Ezin izan da tanke urdinaren ezkerreko textura sortu.");
		goto errorea;
	}
	if ((texturak->tanke_urdina.eskubi = textura_sortu("res/img/jokua/tanke_urdina_eskubi.png", SDL_ALPHA_OPAQUE)) == NULL)
	{
		ERROREA("Ezin izan da tanke urdinaren eskubiko textura sortu.");
		goto errorea;
	}

	if ((texturak->tanke_gorria.aurrea = textura_sortu("res/img/jokua/tanke_gorria_aurrea.png", SDL_ALPHA_OPAQUE)) == NULL)
	{
		ERROREA("Ezin izan da tanke gorriaren aurreko textura sortu.");
		goto errorea;
	}
	if ((texturak->tanke_gorria.atzea = textura_sortu("res/img/jokua/tanke_gorria_atzea.png", SDL_ALPHA_OPAQUE)) == NULL)
	{
		ERROREA("Ezin izan da tanke gorriaren atzeko textura sortu.");
		goto errorea;
	}
	if ((texturak->tanke_gorria.ezker = textura_sortu("res/img/jokua/tanke_gorria_ezkerra.png", SDL_ALPHA_OPAQUE)) == NULL)
	{
		ERROREA("Ezin izan da tanke gorriaren ezkerreko textura sortu.");
		goto errorea;
	}
	if ((texturak->tanke_gorria.eskubi = textura_sortu("res/img/jokua/tanke_gorria_eskubi.png", SDL_ALPHA_OPAQUE)) == NULL)
	{
		ERROREA("Ezin izan da tanke gorriaren eskubiko textura sortu.");
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
		SDL_DestroyTexture((*texturak)->basamortua.aurrea);
		SDL_DestroyTexture((*texturak)->base_gorria.aurrea);
		SDL_DestroyTexture((*texturak)->base_urdina.aurrea);
		SDL_DestroyTexture((*texturak)->basoa.aurrea);
		SDL_DestroyTexture((*texturak)->herri_hautsia.aurrea);
		SDL_DestroyTexture((*texturak)->herria.aurrea);
		SDL_DestroyTexture((*texturak)->ibaia.aurrea);
		SDL_DestroyTexture((*texturak)->karretera.aurrea);
		SDL_DestroyTexture((*texturak)->larrea.aurrea);
		SDL_DestroyTexture((*texturak)->mendi_hautsia.aurrea);
		SDL_DestroyTexture((*texturak)->mendia.aurrea);

		/* Tropak */
		SDL_DestroyTexture((*texturak)->infanteria_urdina.aurrea);
		SDL_DestroyTexture((*texturak)->infanteria_urdina.atzea);
		SDL_DestroyTexture((*texturak)->infanteria_urdina.eskubi);
		SDL_DestroyTexture((*texturak)->infanteria_urdina.ezker);

		SDL_DestroyTexture((*texturak)->infanteria_gorria.aurrea);
		SDL_DestroyTexture((*texturak)->infanteria_gorria.atzea);
		SDL_DestroyTexture((*texturak)->infanteria_gorria.eskubi);
		SDL_DestroyTexture((*texturak)->infanteria_gorria.ezker);

		SDL_DestroyTexture((*texturak)->infanteria_mek_urdina.aurrea);
		SDL_DestroyTexture((*texturak)->infanteria_mek_urdina.atzea);
		SDL_DestroyTexture((*texturak)->infanteria_mek_urdina.eskubi);
		SDL_DestroyTexture((*texturak)->infanteria_mek_urdina.ezker);

		SDL_DestroyTexture((*texturak)->infanteria_mek_gorria.aurrea);
		SDL_DestroyTexture((*texturak)->infanteria_mek_gorria.atzea);
		SDL_DestroyTexture((*texturak)->infanteria_mek_gorria.eskubi);
		SDL_DestroyTexture((*texturak)->infanteria_mek_gorria.ezker);

		SDL_DestroyTexture((*texturak)->rekon_urdina.aurrea);
		SDL_DestroyTexture((*texturak)->rekon_urdina.atzea);
		SDL_DestroyTexture((*texturak)->rekon_urdina.eskubi);
		SDL_DestroyTexture((*texturak)->rekon_urdina.ezker);

		SDL_DestroyTexture((*texturak)->rekon_gorria.aurrea);
		SDL_DestroyTexture((*texturak)->rekon_gorria.atzea);
		SDL_DestroyTexture((*texturak)->rekon_gorria.eskubi);
		SDL_DestroyTexture((*texturak)->rekon_gorria.ezker);

		SDL_DestroyTexture((*texturak)->tanke_urdina.aurrea);
		SDL_DestroyTexture((*texturak)->tanke_urdina.atzea);
		SDL_DestroyTexture((*texturak)->tanke_urdina.eskubi);
		SDL_DestroyTexture((*texturak)->tanke_urdina.ezker);

		SDL_DestroyTexture((*texturak)->tanke_gorria.aurrea);
		SDL_DestroyTexture((*texturak)->tanke_gorria.atzea);
		SDL_DestroyTexture((*texturak)->tanke_gorria.eskubi);
		SDL_DestroyTexture((*texturak)->tanke_gorria.ezker);

		free(*texturak);
		*texturak = NULL;
	}
	OHARRA("Texturak garbitu dira.");
}

bool letra_tipoa_kargatu(void)
{
	bool dena_ondo = true;
	FONT = TTF_OpenFontIndex("res/Fonts/arial.ttf", 20, 0);
	if (!FONT)
	{
		ERROREA(TTF_GetError());
		dena_ondo = false;
	}
	return dena_ondo;
}

void letra_tipoa_garbitu(void)
{
	TTF_CloseFont(FONT);
	TTF_Quit();
}

SDL_Texture* textura_sortu(const char* path, uint8_t alpha)
{
	SDL_Texture* textura = NULL;
	SDL_Surface* srfc = NULL;

	if ((srfc = IMG_Load(path)) == NULL)
	{
		ERROREA(IMG_GetError());
		goto atera;
	}

	if ((textura = SDL_CreateTextureFromSurface(RENDERER, srfc)) == NULL)
	{
		ERROREA(SDL_GetError());
		goto atera;
	}

	if (SDL_SetTextureAlphaMod(textura, alpha) < 0)
	{
		ERROREA(SDL_GetError());
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
	case Basamortua:
	{
		if (SDL_RenderCopy(RENDERER, ELEM_TEXT->basamortua.aurrea, NULL, rect) < 0)
		{
			ERROREA(SDL_GetError());
			dena_ondo = false;
		}
		break;
	}
	case Base_gorria:
	{
		if (SDL_RenderCopy(RENDERER, ELEM_TEXT->base_gorria.aurrea, NULL, rect) < 0)
		{
			ERROREA(SDL_GetError());
			dena_ondo = false;
		}
		break;
	}
	case Base_urdina:
	{
		if (SDL_RenderCopy(RENDERER, ELEM_TEXT->base_urdina.aurrea, NULL, rect) < 0)
		{
			ERROREA(SDL_GetError());
			dena_ondo = false;
		}
		break;
	}
	case Basoa:
	{
		if (SDL_RenderCopy(RENDERER, ELEM_TEXT->basoa.aurrea, NULL, rect) < 0)
		{
			ERROREA(SDL_GetError());
			dena_ondo = false;
		}
		break;
	}
	case BasoMoztua:
	{
		if (SDL_RenderCopy(RENDERER, ELEM_TEXT->baso_moztua.aurrea, NULL, rect) < 0)
		{
			ERROREA(SDL_GetError());
			dena_ondo = false;
		}
		break;
	}
	case Herria:
	{
		if (SDL_RenderCopy(RENDERER, ELEM_TEXT->herria.aurrea, NULL, rect) < 0)
		{
			ERROREA(SDL_GetError());
			dena_ondo = false;
		}
		break;
	}
	case HerriHautsia:
	{
		if (SDL_RenderCopy(RENDERER, ELEM_TEXT->herri_hautsia.aurrea, NULL, rect) < 0)
		{
			ERROREA(SDL_GetError());
			dena_ondo = false;
		}
		break;
	}
	case Ibaia:
	{
		if (SDL_RenderCopy(RENDERER, ELEM_TEXT->ibaia.aurrea, NULL, rect) < 0)
		{
			ERROREA(SDL_GetError());
			dena_ondo = false;
		}
		break;
	}
	case Karretera:
	{
		if (SDL_RenderCopy(RENDERER, ELEM_TEXT->karretera.aurrea, NULL, rect) < 0)
		{
			ERROREA(SDL_GetError());
			dena_ondo = false;
		}
		break;
	}
	case Larrea:
	{
		if (SDL_RenderCopy(RENDERER, ELEM_TEXT->larrea.aurrea, NULL, rect) < 0)
		{
			ERROREA(SDL_GetError());
			dena_ondo = false;
		}
		break;
	}
	case Mendia:
	{
		if (SDL_RenderCopy(RENDERER, ELEM_TEXT->mendia.aurrea, NULL, rect) < 0)
		{
			ERROREA(SDL_GetError());
			dena_ondo = false;
		}
		break;
	}
	case MendiHautsia:
	{
		if (SDL_RenderCopy(RENDERER, ELEM_TEXT->mendi_hautsia.aurrea, NULL, rect) < 0)
		{
			ERROREA(SDL_GetError());
			dena_ondo = false;
		}
		break;
	}
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
			Textura* textura = NULL;
			switch (tropa->id)
			{
			case Urdina:
				textura = &(ELEM_TEXT->infanteria_urdina);
				break;
			case Gorria:
				textura = &(ELEM_TEXT->infanteria_gorria);
				break;
			}
			dena_ondo = marraztu_orientazioa(tropa, textura, rect);
			break;
		}
		case InfanteriaMek:
		{
			Textura* textura = NULL;
			switch (tropa->id)
			{
			case Urdina:
				textura = &(ELEM_TEXT->infanteria_mek_urdina);
				break;
			case Gorria:
				textura = &(ELEM_TEXT->infanteria_mek_gorria);
				break;
			}
			dena_ondo = marraztu_orientazioa(tropa, textura, rect);
			break;
		}
		case Rekon:
		{
			Textura* textura = NULL;
			switch (tropa->id)
			{
			case Urdina:
				textura = &(ELEM_TEXT->rekon_urdina);
				break;
			case Gorria:
				textura = &(ELEM_TEXT->rekon_gorria);
				break;
			}
			dena_ondo = marraztu_orientazioa(tropa, textura, rect);
			break;
		}
		case Tanke:
		{
			Textura* textura = NULL;
			switch (tropa->id)
			{
			case Urdina:
				textura = &(ELEM_TEXT->tanke_urdina);
				break;
			case Gorria:
				textura = &(ELEM_TEXT->tanke_gorria);
				break;
			}
			dena_ondo = marraztu_orientazioa(tropa, textura, rect);
			break;
		}
		}
	}

	return dena_ondo;
}

bool marraztu_orientazioa(TropaStat* tropa, Textura* textura, SDL_Rect* rect)
{
	bool dena_ondo = true;

	switch (tropa->orientazioa)
	{
	case Aurrea:
		if (SDL_RenderCopy(RENDERER, textura->aurrea, NULL, rect) < 0)
		{
			ERROREA(SDL_GetError());
			dena_ondo = false;
		}
		break;
	case Atzea:
		if (SDL_RenderCopy(RENDERER, textura->atzea, NULL, rect) < 0)
		{
			ERROREA(SDL_GetError());
			dena_ondo = false;
		}
		break;
	case Eskubi:
		if (SDL_RenderCopy(RENDERER, textura->eskubi, NULL, rect) < 0)
		{
			ERROREA(SDL_GetError());
			dena_ondo = false;
		}
		break;
	case Ezker:
		if (SDL_RenderCopy(RENDERER, textura->ezker, NULL, rect) < 0)
		{
			ERROREA(SDL_GetError());
			dena_ondo = false;
		}
		break;
	}

	return dena_ondo;
}

bool marraztu_punteroa(Mapa* mapa, Baldosa* baldosa)
{
	bool dena_ondo = true;
	SDL_Rect laukia = { 0, 0, ARGAZKI_TAMAINA, ARGAZKI_TAMAINA };
	Bekt2D aukeratutako_baldosa_pos = ebentuak_lortu_xaguaren_egoera()->mapako_posizioa;

	if ((mapa_lortu_pos(mapa, aukeratutako_baldosa_pos.x, aukeratutako_baldosa_pos.y) == baldosa))
	{
		Bekt2D iso_pos = { 0 };

		kalkulatu_isometriko(&iso_pos, (ARGAZKI_TAMAINA * 0.5f) * aukeratutako_baldosa_pos.x + MAPA_NONDIK_HASI_MARRAZTEN.x, (ARGAZKI_TAMAINA * 0.5f) * aukeratutako_baldosa_pos.y - MAPA_NONDIK_HASI_MARRAZTEN.y);

		laukia.x = iso_pos.x;
		laukia.y = iso_pos.y;

		if (SDL_RenderCopy(RENDERER, ELEM_TEXT->punteroa.aurrea, NULL, &laukia) < 0)
		{
			ERROREA(SDL_GetError());
			dena_ondo = false;
		}
	}

	return dena_ondo;
}

bool marraztu_informazioa(Mapa* mapa)
{
	SDL_Rect laukia = { 0, 0, 100, 100 };
	bool dena_ondo = true;
	Bekt2D aukeratutako_baldosa_pos = ebentuak_lortu_xaguaren_egoera()->mapako_posizioa;
	Baldosa* aukeratutako_baldosa = mapa_lortu_pos(mapa, aukeratutako_baldosa_pos.x, aukeratutako_baldosa_pos.y);

	if (aukeratutako_baldosa != NULL)
	{
		if (marraztu_baldosa(aukeratutako_baldosa, &laukia) == false)
		{
			ERROREA("Ezin izan da info baldosa marraztu.");
			dena_ondo = false;
			goto atera;
		}

		if (marraztu_tropa(aukeratutako_baldosa, &laukia) == false)
		{
			ERROREA("Ezin izan da info tropa marraztu.");
			dena_ondo = false;
			goto atera;
		}
	}

atera:
	return dena_ondo;
}

bool marraztu_stat_textua(Mapa* mapa)
{
	char buffer[50] = { 0 };
	bool dena_ondo = true;
	SDL_Rect rect = { 0 };
	Bekt2D lehio_tamaina = render_lortu_leiho_tamaina();

	Baldosa* baldosa = mapa_lortu_pos(mapa, ebentuak_lortu_xaguaren_egoera()->mapako_posizioa.x, ebentuak_lortu_xaguaren_egoera()->mapako_posizioa.y);

	/* Txanda */
	rect.x = (int)(floor(lehio_tamaina.x * 0.43));
	rect.y = (int)(floor(lehio_tamaina.y * 0.03));
	snprintf(buffer, 50, "Jokalaria: %s", jokoa_lortu_txanda() == Gorria ? "Gorria" : "Urdina");
	if (marraztu_textua(&rect, buffer) == false)
	{
		ERROREA("Textua ez da marraztu.");
		dena_ondo = false;
		goto atera;
	}

	/* Bizitza */
	if (baldosa && baldosa->tropa)
	{
		rect.x = (int)(floor(lehio_tamaina.x * 0.004));
		rect.y = (int)(floor(lehio_tamaina.y * 0.15));
		snprintf(buffer, 50, "Bizitza: %d", baldosa->tropa->bizitza);
	}

	if (marraztu_textua(&rect, buffer) == false)
	{
		ERROREA("Textua ez da marraztu.");
		dena_ondo = false;
		goto atera;
	}

	/* Rangoa */
	if (baldosa && baldosa->tropa)
	{
		rect.x = (int)(floor(lehio_tamaina.x * 0.004));
		rect.y = (int)(floor(lehio_tamaina.y * 0.20));
		snprintf(buffer, 50, "Rangoa: %d", baldosa->tropa->mug_max);
	}

	if (marraztu_textua(&rect, buffer) == false)
	{
		ERROREA("Textua ez da marraztu.");
		dena_ondo = false;
		goto atera;
	}

	/* Munizioa */
	if (baldosa && baldosa->tropa)
	{
		rect.x = (int)(floor(lehio_tamaina.x * 0.004));
		rect.y = (int)(floor(lehio_tamaina.y * 0.25));
		snprintf(buffer, 50, "Munizioa: %d", baldosa->tropa->amunizioa);
	}

	if (marraztu_textua(&rect, buffer) == false)
	{
		ERROREA("Textua ez da marraztu.");
		dena_ondo = false;
		goto atera;
	}

	/* Atakea */
	if (baldosa && baldosa->tropa)
	{
		rect.x = (int)(floor(lehio_tamaina.x * 0.004));
		rect.y = (int)(floor(lehio_tamaina.y * 0.30));
		snprintf(buffer, 50, "Atakea: %d", baldosa->tropa->atakea);
	}

	if (marraztu_textua(&rect, buffer) == false)
	{
		ERROREA("Textua ez da marraztu.");
		dena_ondo = false;
		goto atera;
	}

atera:
	return dena_ondo;
}

bool marraztu_textua(SDL_Rect* rect, char* str)
{
	bool dena_ondo = true;

	SDL_Color textColor = { 0 };

	SDL_Surface* surface_string = TTF_RenderText_Blended(FONT, str, textColor);
	SDL_Texture* textura_string = SDL_CreateTextureFromSurface(RENDERER, surface_string);

	rect->w = surface_string->w;
	rect->h = surface_string->h;

	if (SDL_RenderCopy(RENDERER, textura_string, NULL, rect) < 0)
	{
		ERROREA(SDL_GetError());
		dena_ondo = false;
	}

	SDL_FreeSurface(surface_string);
	SDL_DestroyTexture(textura_string);

	return dena_ondo;
}

bool marraztu_markatua(Baldosa* baldosa, SDL_Rect* rect)
{
	bool dena_ondo = true;

	if (baldosa->markatuta == true)
	{
		if (SDL_RenderCopy(RENDERER, ELEM_TEXT->rangoa.aurrea, NULL, rect) < 0)
		{
			ERROREA(SDL_GetError());
			dena_ondo = false;
		}
	}

	return dena_ondo;
}

bool marraztu_tropa_aukeratzeko_menua(void)
{
	bool dena_ondo = true;
	Bekt2D leiho_tamaina = ebentuak_lortu_lehio_tamaina_berria();

	Baldosa baldosa_infanteria_urdina = { 0 };
	Baldosa baldosa_infanteria_mek_urdina = { 0 };
	Baldosa baldosa_rekon_urdina = { 0 };
	Baldosa baldosa_tanke_urdina = { 0 };

	Baldosa baldosa_infanteria_gorria = { 0 };
	Baldosa baldosa_infanteria_mek_gorria = { 0 };
	Baldosa baldosa_rekon_gorria = { 0 };
	Baldosa baldosa_tanke_gorria = { 0 };

	TropaStat infanteria_urdina = { .id = Urdina, .orientazioa = Aurrea };
	TropaStat infanteria_mek_urdina = { .id = Urdina, .orientazioa = Aurrea };
	TropaStat rekon_urdina = { .id = Urdina, .orientazioa = Aurrea };
	TropaStat tanke_urdina = { .id = Urdina, .orientazioa = Aurrea };
	TropaStat infanteria_gorria = { .id = Gorria, .orientazioa = Aurrea };
	TropaStat infanteria_mek_gorria = { .id = Gorria, .orientazioa = Aurrea };
	TropaStat rekon_gorria = { .id = Gorria, .orientazioa = Aurrea };
	TropaStat tanke_gorria = { .id = Gorria, .orientazioa = Aurrea };

	baldosa_infanteria_urdina.tropa = &infanteria_urdina;
	baldosa_infanteria_mek_urdina.tropa = &infanteria_mek_urdina;
	baldosa_rekon_urdina.tropa = &rekon_urdina;
	baldosa_tanke_urdina.tropa = &tanke_urdina;

	baldosa_infanteria_gorria.tropa = &infanteria_gorria;
	baldosa_infanteria_mek_gorria.tropa = &infanteria_mek_gorria;
	baldosa_rekon_gorria.tropa = &rekon_gorria;
	baldosa_tanke_gorria.tropa = &tanke_gorria;

	SDL_Rect laukia_1 = { .y = (int)(floor(leiho_tamaina.y) * 0.20), .w = 100, .h = 100 };
	SDL_Rect laukia_2 = { .y = (int)(floor(leiho_tamaina.y) * 0.25), .w = 100, .h = 100 };
	SDL_Rect laukia_3 = { .y = (int)(floor(leiho_tamaina.y) * 0.30), .w = 100, .h = 100 };
	SDL_Rect laukia_4 = { .y = (int)(floor(leiho_tamaina.y) * 0.35), .w = 100, .h = 100 };



	return dena_ondo;
}

/*
 *	END: Funtzio pribatuen inplementazioa
 */
