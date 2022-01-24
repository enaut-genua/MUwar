#include "jokoa.h"
#include "renderizadorea.h"
#include "ebentuak.h"
#include "tropa.h"
#include "mapa_modeloak.h"
#include "jokalaria.h"

/*
 *	START: Aldagai global pribatuak
 */

static bool JOKOA_MARTXAN = true;
static Mapa* MAPA = NULL;
static Bandoa NOREN_TXANDA = Gorria;

/*
 *	END: Aldagai global pribatuak
 */

 /*
  *	START: Funtzio pribatuak
  */

static void egin_jokaldia(void);
static void detektatu_inputa(float dt);
static void detektatu_xagua(void);
static void detektatu_teklatua(float dt);

static void tropa(Baldosa* klikatutako_baldosa, Bekt2D klikatutako_baldosa_pos);

/*
 *	END: Funtzio pribatuak
 */

bool jokoa_prestatu(void)
{
	bool dena_ondo = true;

	if (render_sortu(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 700, false) == false)
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
	float dt = 0;

	OHARRA("Jokoa hasi da.");

	while (JOKOA_MARTXAN && dena_ondo)
	{
		uint64_t hasiera = SDL_GetPerformanceCounter();
		dena_ondo = render_marraztu(MAPA);
		detektatu_inputa(dt);
		ebentuak_kudeatu();

		uint64_t bukaera = SDL_GetPerformanceCounter();

		dt = (bukaera - hasiera) / (float)SDL_GetPerformanceFrequency();

		render_erakutsi_fps(dt);
	}

	OHARRA("Jokoa bukatu da.");

	return dena_ondo;
}

bool jokoa_mugitu_tropa(Baldosa* hasiera, Baldosa* bukaera)
{
	bool dena_ondo = false;

	if (bukaera != NULL && bukaera->tropa == NULL && hasiera->tropa != NULL && bukaera->markatuta == true)
	{
		TropaStat* tmp = NULL;
		tmp = hasiera->tropa;
		hasiera->tropa = NULL;
		bukaera->tropa = tmp;
		dena_ondo = true;
	}

	return dena_ondo;
}

void detektatu_inputa(float dt)
{
	detektatu_xagua();
	detektatu_teklatua(dt);
}

void detektatu_xagua(void)
{
	static Baldosa* klikatutako_baldosa = NULL;
	static Bekt2D klikatutako_baldosa_pos = { 0 };

	const Xagua* xagua = ebentuak_lortu_xaguaren_egoera();

	Baldosa* aukeratutako_baldosa = mapa_lortu_pos(MAPA, xagua->mapako_posizioa.x, xagua->mapako_posizioa.y);
	Bekt2D aukeratutako_baldosa_pos = { 0 };

	if (xagua->ezker_botoia_klikatuta == true)
	{
		aukeratutako_baldosa_pos = xagua->mapako_posizioa;
		if (aukeratutako_baldosa != NULL && klikatutako_baldosa == NULL)
		{
			if (aukeratutako_baldosa->tropa != NULL)
			{
				if (aukeratutako_baldosa->tropa->id == NOREN_TXANDA)
				{
					klikatutako_baldosa = aukeratutako_baldosa;
					klikatutako_baldosa_pos = xagua->mapako_posizioa;
					mapa_rangoa_jarri(MAPA, aukeratutako_baldosa->tropa->mug_max, xagua->mapako_posizioa.x, xagua->mapako_posizioa.y);
				}
			}
			else
			{
				if (NOREN_TXANDA == Gorria && aukeratutako_baldosa->mota == Base_gorria)
				{
					aukeratutako_baldosa->tropa = tropa_sortu(rand() % 4, Gorria);
				}
				else if (NOREN_TXANDA == Urdina && aukeratutako_baldosa->mota == Base_urdina)
				{
					aukeratutako_baldosa->tropa = tropa_sortu(rand() % 4, Urdina);
				}
			}
		}
	}
	else if (xagua->ezker_botoia_klikatuta == false)
	{
		if (klikatutako_baldosa != NULL)
		{
			int tropa_rango = klikatutako_baldosa->tropa->mug_max;
			jokoa_mugitu_tropa(klikatutako_baldosa, aukeratutako_baldosa);
			mapa_rangoa_kendu(MAPA, tropa_rango, klikatutako_baldosa_pos.x, klikatutako_baldosa_pos.y);
			klikatutako_baldosa = NULL;
		}
	}
}

void detektatu_teklatua(float dt)
{
	const Teklatua* teklatu_berria = ebentuak_lortu_teklatua_berria();
	const Teklatua* teklatu_zaharra = ebentuak_lortu_teklatua_zaharra();

	if (teklatu_berria->enter == true && teklatu_zaharra->enter == false)
	{
		if (NOREN_TXANDA == Gorria)
		{
			OHARRA("Urdinaren txanda.");
			NOREN_TXANDA = Urdina;
		}
		else if (NOREN_TXANDA == Urdina)
		{
			OHARRA("Gorriaren txanda.");
			NOREN_TXANDA = Gorria;
		}
	}
	if (teklatu_berria->a == true)
	{
		render_mugitu_mapa_ezker(dt);
	}
	if (teklatu_berria->d == true)
	{
		render_mugitu_mapa_eskubi(dt);
	}
	if (teklatu_berria->w == true)
	{
		render_mugitu_mapa_gora(dt);
	}
	if (teklatu_berria->s == true)
	{
		render_mugitu_mapa_behera(dt);
	}
}

void tropa(Baldosa* baldosa, Bekt2D baldosa_pos)
{
	static Baldosa* klikatutako_baldosa = NULL;
	static Bekt2D klikatutako_baldosa_pos = { 0 };

	if (klikatutako_baldosa == NULL)
	{
		if (baldosa != NULL && baldosa->tropa->id == NOREN_TXANDA)
		{
			klikatutako_baldosa = baldosa;
			klikatutako_baldosa_pos = baldosa_pos;
			mapa_rangoa_jarri(MAPA, klikatutako_baldosa->tropa->mug_max, klikatutako_baldosa_pos.x, klikatutako_baldosa_pos.y);
		}
	}
	else
	{
		Baldosa* aukeratutako_baldosa = mapa_lortu_pos(MAPA, ebentuak_lortu_xaguaren_egoera()->mapako_posizioa.x, ebentuak_lortu_xaguaren_egoera()->mapako_posizioa.y);
		if (aukeratutako_baldosa != klikatutako_baldosa)
		{
			int rangoa = klikatutako_baldosa->tropa->mug_max;
			jokoa_mugitu_tropa(klikatutako_baldosa, aukeratutako_baldosa);
			mapa_rangoa_kendu(MAPA, rangoa, klikatutako_baldosa_pos.x, klikatutako_baldosa_pos.y);
			klikatutako_baldosa = NULL;
		}
	}
}
