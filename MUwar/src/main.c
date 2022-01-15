#include "include.h"

#include "renderizadorea.h"
#include "tropa.h"
#include "baldosa.h"
#include "ebentuak.h"

void ebentoakGestionatu(void);

bool jokoaMartxan = false;

int main(void)
{
	/* Memoria ondo borratu den ikusteko */
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif // _DEBUG

	TerrenoMotak mapa_1[] = {
	Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea,
	Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea,
	Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea,
	Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea,
	Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea,
	Larrea, Larrea, Larrea, Larrea, Ibaia, Larrea, Larrea, Larrea, Larrea, Larrea,
	Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea,
	Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea,
	Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea,
	Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea,
	Larrea, Larrea, Larrea, Larrea, Mendia, Mendia, Larrea, Larrea, Larrea, Larrea,
	Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea,
	Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea,
	};

	jokoaMartxan = render_sortu("MUwar", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 700, false);

	Mapa* map = mapa_sortu(mapa_1, 10, 13);

	mapa_lortu_pos(map, 4, 9)->tropa = tropa_sortu(Infanteria, 2);

	while (ebentuak_martxan_jokoa())
	{
		render_marraztu(map);
		ebentuak_kudeatu();
	}

	tropa_borratu(&mapa_lortu_pos(map, 4, 9)->tropa);

	mapa_borratu(&map);
	render_garbitu();
	return 0;
}

/*-----------------------------------------------------------------------------------------------
Funtzio honek eventuak gestionatzen ditu beraz, ebentoak uneoro errebisatzen joango dira jokoa martxan dabilen bitartean
-----------------------------------------------------------------------------------------------*/
void ebentoakGestionatu(void)
{
	SDL_Event event = { 0 };

	/* Lortu xaguaren posizioa */


	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			jokoaMartxan = false;
			break;
		case SDL_KEYDOWN:
		{
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				jokoaMartxan = false; 
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