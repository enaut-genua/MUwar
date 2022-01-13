#include "include.h"

#include "renderizadorea.h"
#include "tropa.h"
#include "baldosa.h"

void ebentoakGestionatu(void);

bool jokoaMartxan = false;

int main(void)
{
	/* Memoria ondo borratu den ikusteko */
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif // _DEBUG

	jokoaMartxan = render_sortu("MUwar", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 700, false);

	while (jokoaMartxan)
	{
		ebentoakGestionatu();
		render_marraztu();
	}

	render_garbitu();
	return 0;
}

/*-----------------------------------------------------------------------------------------------
Funtzio honek eventuak gestionatzen ditu beraz, ebentoak uneoro errebisatzen joango dira jokoa martxan dabilen bitartean
-----------------------------------------------------------------------------------------------*/
void ebentoakGestionatu(void)
{
	SDL_Event event = { 0 };

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
			}
			break;
		}
		default:
			break;
		}
	}
}