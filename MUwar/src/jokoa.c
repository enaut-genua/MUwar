#include "jokoa.h"
#include "renderizadorea.h"
#include "ebentuak.h"
#include "tropa.h"
#include "mapa_modeloak.h"
#include "bektorea.h"
#include "musika.h"

/*
 *	START: Aldagai global pribatuak
 */

static bool JOKOA_MARTXAN = true;
static Mapa* MAPA = NULL;
static Bandoa NOREN_TXANDA = Gorria;
static Bektorea* BIDEA = NULL;
static Bandoa IRABAZLEA = Inor;

/*
 *	END: Aldagai global pribatuak
 */

 /*
  *	START: Funtzio pribatuak
  */

static bool mugitu_tropa(Baldosa* hasiera, Baldosa* bukaera);
static void detektatu_inputa(float dt);
static void detektatu_xagua(void);
static void detektatu_teklatua(float dt);
static void bidea_registratu(const Xagua* xagua);
static void txandaz_aldatu(void);

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

	if ((MAPA = mapa_sortu(array_mapa[rand() % 3], 20, 20)) == NULL)
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

	if (render_aldatu_fondoa() == false)
	{
		ERROREA("Ezin izan da fondoa aldatu");
		dena_ondo = false;
	}

	JOKOA_MARTXAN = true;
	NOREN_TXANDA = Gorria;
	IRABAZLEA = Inor;

	musika_hasi_jokoa();

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

	musika_gelditu();

	OHARRA("Jokoa bukatu da.");

	return dena_ondo;
}

bool mugitu_tropa(Baldosa* hasiera, Baldosa* bukaera)
{
	bool dena_ondo = false;

	if (bukaera != NULL && bukaera->tropa == NULL && hasiera->tropa != NULL && bukaera->markatuta == true)
	{
		TropaStat* tmp = hasiera->tropa;
		hasiera->tropa = NULL;
		bukaera->tropa = tmp;

		bukaera->tropa->mugitu_da = true;

		if (baldosa_aldatu_mota(bukaera) == true)
		{
			// Aldaketaren arabera egin gauzak
		}

		tropa_orientazioa(BIDEA, bukaera->tropa);

		dena_ondo = true;
	}

	return dena_ondo;
}

Bandoa jokoa_lortu_txanda(void)
{
	return NOREN_TXANDA;
}

Bandoa jokoa_lortu_irabazlea(void)
{
	return IRABAZLEA;
}

bool jokoa_reset(void)
{
	bool dena_ondo = true;

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

	if ((MAPA = mapa_sortu(array_mapa[rand() % 3], 20, 20)) == NULL)
	{
		ERROREA("Ezin izan da mapa sortu.");
		dena_ondo = false;
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

	if (xagua->ezker_botoia_klikatuta == true)
	{
		if (aukeratutako_baldosa != NULL && klikatutako_baldosa == NULL)
		{
			if (aukeratutako_baldosa->tropa != NULL)
			{
				if (aukeratutako_baldosa->tropa->id == NOREN_TXANDA && aukeratutako_baldosa->tropa->mugitu_da == false)
				{
					if (musika_aukeratu_efekto() == false)
					{
						ERROREA("Ezin izan da aukeratu efekto entzun.");
					}
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
			if (aukeratutako_baldosa != NULL)
			{
				int tropa_rango = klikatutako_baldosa->tropa->mug_max;
				if (aukeratutako_baldosa->tropa != NULL)
				{
					// Atakatu
					if (aukeratutako_baldosa->tropa->id != NOREN_TXANDA)
					{
						Bekt2D baldosa_pos = { 0 };
						tropa_atakatu(&klikatutako_baldosa->tropa, &aukeratutako_baldosa->tropa);
						bektorea_lortu_balioa_posizioan(BIDEA, bektorea_lortu_luzeera(BIDEA) - 2, (uint8_t*)(&baldosa_pos));
						aukeratutako_baldosa = mapa_lortu_pos(MAPA, baldosa_pos.x, baldosa_pos.y);
					}
				}

				mugitu_tropa(klikatutako_baldosa, aukeratutako_baldosa);
				mapa_rangoa_kendu(MAPA, tropa_rango, klikatutako_baldosa_pos.x, klikatutako_baldosa_pos.y);
				klikatutako_baldosa = NULL;
			}

			bektorea_borratu(&BIDEA);
		}
	}

	if (xagua->ezker_botoia_klikatuta == true && klikatutako_baldosa != NULL)
	{
		bidea_registratu(xagua);
	}
}

void detektatu_teklatua(float dt)
{
	const Teklatua* teklatu_berria = ebentuak_lortu_teklatua_berria();
	const Teklatua* teklatu_zaharra = ebentuak_lortu_teklatua_zaharra();

	if (teklatu_berria->enter == true && teklatu_zaharra->enter == false)
	{
		txandaz_aldatu();
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

void bidea_registratu(const Xagua* xagua)
{
	bool registratu_daiteke = true;

	if (BIDEA == NULL)
	{
		BIDEA = bektorea_sortu(sizeof(Bekt2D), 0);
	}

	Bekt2D xagu_pos = xagua->mapako_posizioa;

	if ((xagu_pos.x < MAPA->tamaina_x && xagu_pos.x >= 0) && (xagu_pos.y < MAPA->tamaina_y && xagu_pos.y >= 0))
	{
		for (size_t i = 0; i < BIDEA->luzeera; i++)
		{
			Bekt2D gordetako_balioa = { 0 };
			bektorea_lortu_balioa_posizioan(BIDEA, i, (uint8_t*)(&gordetako_balioa));

			if ((xagu_pos.x == gordetako_balioa.x) && (xagu_pos.y == gordetako_balioa.y))
			{
				registratu_daiteke = false;
			}
		}
	}
	else
	{
		registratu_daiteke = false;
	}

	if (registratu_daiteke)
	{
		bektorea_sartu_atzean(BIDEA, (uint8_t*)(&xagu_pos));
	}
}

void txandaz_aldatu(void)
{
	int tamaina = MAPA->tamaina_x * MAPA->tamaina_y;
	for (int i = 0; i < tamaina; i++)
	{
		Baldosa* baldosa = &MAPA->mapa[i];
		TropaStat* tropa = baldosa->tropa;
		if (tropa != NULL)
		{
			if (tropa->id == NOREN_TXANDA)
			{
				tropa->mugitu_da = false;
			}
			if (baldosa->mota == Base_gorria && tropa->id == Urdina)
			{
				// Irabazi
				IRABAZLEA = Urdina;
				JOKOA_MARTXAN = false;
			}
			else if (baldosa->mota == Base_urdina && tropa->id == Gorria)
			{
				//  Irabazi
				IRABAZLEA = Gorria;
				JOKOA_MARTXAN = false;
			}
		}
	}

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
