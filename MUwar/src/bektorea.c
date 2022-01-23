#include "bektorea.h"

Bektorea* bektorea_sortu(size_t datu_tamaina, size_t kapazidadea)
{
	Bektorea* bekt = NULL;

	if (kapazidadea == 0)
	{
		kapazidadea = 8;
	}

	if ((bekt = (Bektorea*)calloc(1, sizeof(Bektorea))) == NULL)
	{
		ERROREA("Ezin izan da bektorea sortu.");
		goto errorea;
	}

	if ((bekt->datuak = (uint8_t**)calloc(kapazidadea, datu_tamaina)) == NULL)
	{
		ERROREA("Ezin izan dira bektorearen datuak sortu.");
		goto errorea;
	}

	bekt->datu_tamaina = datu_tamaina;
	bekt->kapazidadea = kapazidadea;
	bekt->luzeera = 0;

	return bekt;

errorea:
	bektorea_borratu(&bekt);
	return NULL;
}

void bektorea_borratu(Bektorea** bekt)
{
	for (size_t i = 0; i < bektorea_lortu_luzeera(*bekt); i++)
	{
		free((*bekt)->datuak[i]);
	}
	free((*bekt)->datuak);
	free(*bekt);
	*bekt = NULL;
}

size_t bektorea_lortu_kapazidadea(const Bektorea* bekt)
{
	return bekt->kapazidadea;
}

size_t bektorea_lortu_luzeera(const Bektorea* bekt)
{
	return bekt->luzeera;
}

size_t bektorea_lortu_datu_tamaina(const Bektorea* bekt)
{
	return bekt->datu_tamaina;
}

bool bektorea_hutsik_dago(const Bektorea* bekt)
{
	bool hutsik_dago = true;

	if (bekt != NULL && bekt->luzeera != 0)
	{
		hutsik_dago = false;
	}

	return hutsik_dago;
}

bool bektorea_handitu(Bektorea* bekt)
{
	bool dena_ondo = false;

	if (bekt != NULL)
	{
		if (bekt->kapazidadea == bekt->luzeera)
		{
			bekt->kapazidadea += bektorea_lortu_kapazidadea(bekt) / 2;
			uint8_t** tmp = (uint8_t**)realloc(bekt->datuak, sizeof(uint8_t*) * bekt->kapazidadea);
			if (tmp != NULL)
			{
				bekt->datuak = tmp;
				dena_ondo = true;
			}
		}
	}

	if (dena_ondo == false)
	{
		ERROREA("Ezin izan da bektorea handitu.");
	}

	return dena_ondo;
}

bool bektorea_estutu(Bektorea* bekt)
{
	bool dena_ondo = false;

	if (bekt != NULL)
	{
		if (bektorea_hutsik_dago(bekt) == false)
		{
			bekt->kapazidadea = bektorea_lortu_luzeera(bekt) + 1;
			uint8_t** tmp = (uint8_t**)realloc(bekt->datuak, sizeof(uint8_t*) * bektorea_lortu_kapazidadea(bekt));
			if (tmp != NULL)
			{
				bekt->datuak = tmp;
				dena_ondo = true;
			}
		}
	}

	if (dena_ondo == false)
	{
		ERROREA("Ezin izan da bektorea txikitu.");
	}

	return false;
}

bool bektorea_sartu_posizioan(Bektorea* bekt, size_t posizioa, const uint8_t* sartuko_dena)
{
	bool dena_ondo = false;

	if (bekt != NULL && sartuko_dena != NULL)
	{
		if (posizioa <= bektorea_lortu_luzeera(bekt) && bektorea_handitu(bekt) == true)
		{
			uint8_t* tmp = (uint8_t*)calloc(1, bektorea_lortu_datu_tamaina(bekt));

			if (tmp != NULL)
			{
				bekt->datuak[bektorea_lortu_luzeera(bekt)] = tmp;

				for (size_t i = bektorea_lortu_luzeera(bekt); i > posizioa; --i)
				{
					memcpy(bekt->datuak[i], bekt->datuak[i - 1], bektorea_lortu_datu_tamaina(bekt));
				}

				memcpy(bekt->datuak[posizioa], sartuko_dena, bektorea_lortu_datu_tamaina(bekt));

				bekt->luzeera++;

				dena_ondo = true;
			}
		}
	}

	if (dena_ondo == false)
	{
		ERROREA("Ezin izan dira datuak eskatutako posizioan sartu.");
	}

	return dena_ondo;
}

bool bektorea_sartu_atzean(Bektorea* bekt, const uint8_t* sartuko_dena)
{
	bool dena_ondo = false;

	if (bekt != NULL && sartuko_dena != NULL)
	{
		dena_ondo = bektorea_sartu_posizioan(bekt, bektorea_lortu_luzeera(bekt), sartuko_dena);
	}

	if (dena_ondo == false)
	{
		ERROREA("Ezin izan dira datuak atzean sartu.");
	}

	return dena_ondo;
}

bool bektorea_sartu_aurrean(Bektorea* bekt, const uint8_t* sartuko_dena)
{
	bool dena_ondo = false;

	if (bekt != NULL && sartuko_dena != NULL)
	{
		dena_ondo = bektorea_sartu_posizioan(bekt, 0, sartuko_dena);
	}

	if (dena_ondo == false)
	{
		ERROREA("Ezin izan dira datuak aurrean sartu.");
	}

	return dena_ondo;
}

bool bektorea_borratu_posizioan(Bektorea* bekt, const size_t posizioa)
{
	bool dena_ondo = false;

	if (bekt != NULL)
	{
		if (bektorea_hutsik_dago(bekt) == false && posizioa < bektorea_lortu_datu_tamaina(bekt))
		{
			for (size_t i = posizioa; i < bektorea_lortu_luzeera(bekt) - 1; i++)
			{
				memcpy(bekt->datuak[i], bekt->datuak[i + 1], bektorea_lortu_datu_tamaina(bekt));
			}

			free(bekt->datuak[bektorea_lortu_luzeera(bekt)] - 1);
			bekt->luzeera--;

			dena_ondo = true;
		}
	}

	if (dena_ondo == false)
	{
		ERROREA("Ezin izan dira datuak posizioan borratu.");
	}

	return dena_ondo;
}

bool bektorea_borratu_aurrean(Bektorea* bekt)
{
	bool dena_ondo = false;

	if (bekt != NULL)
	{
		if (bektorea_hutsik_dago(bekt) == false)
		{
			dena_ondo = bektorea_borratu_posizioan(bekt, 0);
		}
	}

	if (dena_ondo == false)
	{
		ERROREA("Ezin izan dira aurreko datuak borratu.");
	}

	return dena_ondo;
}

bool bektorea_borratu_atzean(Bektorea* bekt)
{
	bool dena_ondo = false;

	if (bekt != NULL)
	{
		if (bektorea_hutsik_dago(bekt) == false)
		{
			dena_ondo = bektorea_borratu_posizioan(bekt, bektorea_lortu_luzeera(bekt) - 1);
		}
	}

	return false;
}