#include "jokoa.h"

#include "renderizadorea.h"
#include "ebentuak.h"
#include "tropa.h"
#include "mapa_modeloak.h"

/*
 *	START: Aldagai global pribatuak
 */

static bool JOKOA_MARTXAN = true;
static Mapa* MAPA = NULL;

/*
 *	END: Aldagai global pribatuak
 */

bool jokoa_prestatu(void)
{
	bool dena_ondo = true;

	if (render_sortu("MUwar", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 700, false) == false)
	{
		fprintf(stderr, "Errorea: Ezin izan da renderizadorea sortu.\n");
		dena_ondo = false;
		goto atera;
	}

	if ((MAPA = mapa_sortu(mapa_1, 20, 20)) == NULL)
	{
		fprintf(stderr, "Errorea: Ezin izan da mapa sortu.\n");
		dena_ondo = false;
		goto atera;
	}

	ebentuak_konfiguratu(&JOKOA_MARTXAN);

atera:
	return dena_ondo;
}

void jokoa_garbitu(void)
{
	int maparen_tamaina = MAPA->tamaina_x * MAPA->tamaina_y;

	for (int i = 0; i < maparen_tamaina; i++)
	{
		TropaStat* tropa = MAPA->mapa[i].tropa;
		if (tropa != NULL)
		{
			tropa_borratu(&tropa);
		}
	}

	mapa_borratu(&MAPA);
	render_garbitu();
}

bool jokoa_hasi(void)
{
	bool dena_ondo = true;

	mapa_lortu_pos(MAPA, 4, 9)->tropa = tropa_sortu(Infanteria, 2);
	mapa_lortu_pos(MAPA, 5, 11)->aukeratuta = true;

	while (JOKOA_MARTXAN && dena_ondo)
	{
		dena_ondo = render_marraztu(MAPA);
		ebentuak_kudeatu();
	}

	return dena_ondo;
}

bool jokoa_mugitu_tropa(Baldosa* hasiera, Baldosa* bukaera)
{
	bool dena_ondo = false;

	if (bukaera->tropa == NULL && hasiera->tropa != NULL)
	{
		TropaStat* tmp = NULL;
		tmp = hasiera->tropa;
		hasiera->tropa = NULL;
		bukaera->tropa = tmp;
		dena_ondo = true;
	}

	return dena_ondo;
}
