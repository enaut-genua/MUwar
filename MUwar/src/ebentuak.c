#include "ebentuak.h"
#include "renderizadorea.h"
#include "kalkuloak.h"

/*
 *	START: Aldagai global pribatuak
 */

static Xagua XAGUA = { 0 };
static bool* JOKOA_MARTXAN = NULL;

/*
 *	END: Aldagai global pribatuak
 */

void ebentuak_kudeatu(void)
{
	SDL_Event event = { 0 };

	while (SDL_PollEvent(&event))
	{
		uint32_t botoia = SDL_GetMouseState(&XAGUA.posizio_erreala.x, &XAGUA.posizio_erreala.y);

		switch (event.type)
		{
		case SDL_QUIT:
			*JOKOA_MARTXAN = false;
			break;
		case SDL_KEYDOWN:
		{
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				*JOKOA_MARTXAN = false;
				break;
			case SDLK_w:
				render_mugitu_mapa_gora();
				break;
			case SDLK_s:
				render_mugitu_mapa_behera();
				break;
			case SDLK_a:
				render_mugitu_mapa_ezker();
				break;
			case SDLK_d:
				render_mugitu_mapa_eskubi();
				break;
			}
			break;
		}
		case SDL_MOUSEWHEEL:
		{
			if (event.wheel.y > 0)
			{
				render_handitu_argazkiak();
			}
			else if (event.wheel.y < 0)
			{
				render_txikitu_argazkiak();
			}
			break;
		}
		case SDL_MOUSEBUTTONDOWN:
		{
			if ((botoia & SDL_BUTTON_LMASK) != 0)
			{
				XAGUA.ezker_botoia_klikatuta = true;
			}
			else if ((botoia & SDL_BUTTON_RMASK) != 0)
			{
				XAGUA.eskubi_botoia_klikatuta = true;
			}

			break;
		}
		case SDL_MOUSEBUTTONUP:
		{
			if ((botoia & SDL_BUTTON_LMASK) == 0)
			{
				XAGUA.ezker_botoia_klikatuta = false;
			}
			if ((botoia & SDL_BUTTON_RMASK) == 0)
			{
				XAGUA.eskubi_botoia_klikatuta = false;
			}

			break;
		}
		}
	}
}

void ebentuak_konfiguratu(bool* interruptorea)
{
	JOKOA_MARTXAN = interruptorea;
}

const Xagua* ebentuak_lortu_xaguaren_egoera(void)
{
	int argazki_tamaina = render_lortu_argazki_tamaina();
	Bekt2D mapa_hasiera = render_lortu_mapa_nondik_hasi_marrazten();
	Bekt2D pos_kart = { 0 };

	kalkulatu_kartesiarrak(&pos_kart, XAGUA.posizio_erreala.x, XAGUA.posizio_erreala.y);

	XAGUA.mapako_posizioa.x = (int)((pos_kart.x - argazki_tamaina * 0.5 - mapa_hasiera.x) / (argazki_tamaina * 0.5f));
	XAGUA.mapako_posizioa.y = (int)((pos_kart.y + mapa_hasiera.y) / (argazki_tamaina * 0.5f));

	return &XAGUA;
}