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

 /*
  *	START: Funtzio pribatuak
  */

static void ikusi_jokaldia(void);

/*
 *	END: Funtzio pribatuak
 */

bool jokoa_prestatu(void)
{
	bool dena_ondo = true;

	if (render_sortu("MUwar", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 700, false) == false)
	{
		ERROREA("Ezin izan da renderizadorea sortu.");
		dena_ondo = false;
		goto atera;
	}

	if ((MAPA = mapa_sortu(mapa_1, 20, 20)) == NULL)
	{
		ERROREA("Ezin izan da mapa sortu.");
		dena_ondo = false;
		goto atera;
	}

	ebentuak_konfiguratu(&JOKOA_MARTXAN);

	OHARRA("Jokua zuzen prestatu da.");

atera:
	return dena_ondo;
}

void jokoa_garbitu(void)
{
	int maparen_tamaina = MAPA != NULL ? MAPA->tamaina_x * MAPA->tamaina_y : 0;

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

	OHARRA("Jokoa garbitu da.");
}

bool jokoa_hasi(void)
{
	bool dena_ondo = true;

	mapa_lortu_pos(MAPA, 4, 9)->tropa = tropa_sortu(Infanteria, 2);
	mapa_lortu_pos(MAPA, 5, 11)->markatuta = true;

	OHARRA("Jokoa hasi da.");

	while (JOKOA_MARTXAN && dena_ondo)
	{
		dena_ondo = render_marraztu(MAPA);
		ERABILI_GABE(ikusi_jokaldia());
		ebentuak_kudeatu();
	}

	OHARRA("Jokoa bukatu da.");

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

void ikusi_jokaldia(void)
{
	static Baldosa* klikatutako_baldosa = NULL;
	static Bekt2D klikatutako_baldosa_pos = { 0 };

	const Xagua* xagua = ebentuak_lortu_xaguaren_egoera();
	Baldosa* aukeratutako_baldosa = mapa_lortu_pos(MAPA, xagua->mapako_posizioa.x, xagua->mapako_posizioa.y);

	if (xagua->ezker_botoia_klikatuta && aukeratutako_baldosa != NULL && aukeratutako_baldosa->tropa != NULL)
	{
		klikatutako_baldosa = aukeratutako_baldosa;
		klikatutako_baldosa_pos = xagua->mapako_posizioa;
		mapa_rangoa_jarri(MAPA, aukeratutako_baldosa->tropa->mug_max, xagua->mapako_posizioa.x, xagua->mapako_posizioa.y);
	}
	if (xagua->ezker_botoia_klikatuta == false && klikatutako_baldosa != NULL)
	{
		mapa_rangoa_kendu(MAPA, klikatutako_baldosa->tropa->mug_max, klikatutako_baldosa_pos.x, klikatutako_baldosa_pos.y);
		klikatutako_baldosa = NULL;
	}
}
