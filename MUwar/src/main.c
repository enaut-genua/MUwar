#include "include.h"

#include "renderizadorea.h"
#include "tropa.h"
#include "baldosa.h"
#include "ebentuak.h"

int main(void)
{
	/* Memoria ondo borratu den ikusteko */
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif // _DEBUG

	TerrenoMotak mapa_1[] = {
	Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea,
	Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea,
	Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea,
	Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea,
	Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea,
	Larrea, Larrea, Larrea, Larrea, Ibaia, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea,
	Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea,
	Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea,
	Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea,
	Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea,
	Larrea, Larrea, Larrea, Larrea, Mendia, Mendia, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea,
	Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea,
	Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea,
	Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea,
	Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea,
	Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea,
	Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea,
	Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea,
	Larrea, Larrea, Larrea, Larrea, Ibaia, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea,
	Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea, Larrea,
	};

	bool jokoaMartxan = true;

	if (render_sortu("MUwar", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 700, false) == false)
	{
		exit(EXIT_FAILURE);
	}

	Mapa* map = mapa_sortu(mapa_1, 20, 20);

	ebentuak_martxan_jokoa(&jokoaMartxan);
	mapa_lortu_pos(map, 4, 9)->tropa = tropa_sortu(Infanteria, 2);
	mapa_lortu_pos(map, 5, 11)->aukeratuta = true;

	while (jokoaMartxan)
	{
		jokoaMartxan = render_marraztu(map);
		ebentuak_kudeatu();
	}

	tropa_borratu(&mapa_lortu_pos(map, 4, 9)->tropa);

	mapa_borratu(&map);
	render_garbitu();
	return 0;
}
