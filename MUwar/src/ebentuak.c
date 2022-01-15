#include "ebentuak.h"
#include "renderizadorea.h"

/*
 *	START: Aldagai global pribatuak
 */

static Bekt2D XAGU_POS = { 0 };
static bool JOKOA_MARTXAN = true;

/*
 *	END: Aldagai global pribatuak
 */

void ebentuak_kudeatu(void)
{
	SDL_Event event = { 0 };

	while (SDL_PollEvent(&event))
	{
		SDL_GetMouseState(&XAGU_POS.x, &XAGU_POS.y);
	
		switch (event.type)
		{
		case SDL_QUIT:
			JOKOA_MARTXAN = false;
			break;
		case SDL_KEYDOWN:
		{
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				JOKOA_MARTXAN = false;
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
		case SDL_KEYUP:
		{
			switch (event.key.keysym.sym)
			{
			default:
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
		default:
			break;
		}
	}
}

bool ebentuak_martxan_jokoa(void)
{
	return JOKOA_MARTXAN;
}

Bekt2D ebentuak_lortu_xagu_pos(void)
{
	Bekt2D xagupos = { XAGU_POS.x, XAGU_POS.y };
	return xagupos;
}
