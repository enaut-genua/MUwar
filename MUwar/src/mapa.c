#include "include.h"

#include "ebentuak.h"
#include "mapa.h"
#include "jokoa.h"

Mapa* mapa_sortu(TerrenoMotak mapa_array[], int tamaina_x, int tamaina_y)
{
	Mapa* mapa = NULL;

	/* Kalkulatu tamaina totala */
	int tamaina = tamaina_x * tamaina_y;

	/* Sortu mapa eta begiratu errorerik gertatu den */
	if ((mapa = (Mapa*)calloc(1, sizeof(Mapa))) == NULL)
	{
		ERROREA("Mapa ez da sortu.");
		goto atera;
	}

	/* Sortu mapa barruko Baldosa* bektorea eta begiratu ea errorerik gertatu den */
	if ((mapa->mapa = (Baldosa*)calloc(tamaina, sizeof(Baldosa))) == NULL)
	{
		ERROREA("Baldosa* bektorea ez da sortu.");
		mapa_borratu(&mapa);
		goto atera;
	}

	mapa->tamaina_x = tamaina_x;
	mapa->tamaina_y = tamaina_y;

	for (int i = 0; i < tamaina; i++)
	{
		mapa->mapa[i].mota = mapa_array[i];
	}

	OHARRA("Mapa sortu da");

atera:
	return mapa;
}

void mapa_borratu(Mapa** mapa)
{
	if (*mapa != NULL)
	{
		free((*mapa)->mapa);
		free(*mapa);
		*mapa = NULL;
	}
}

Baldosa* mapa_aukeratu_baldosa(Mapa* mapa)
{
	Bekt2D pos = ebentuak_lortu_xaguaren_egoera()->mapako_posizioa;
	return mapa_lortu_pos(mapa, pos.x, pos.y);
}

Baldosa* mapa_lortu_pos(Mapa* mapa, int x, int y)
{
	Baldosa* baldosa = NULL;
	int pos = x + mapa->tamaina_x * y;

	if ((x >= 0 && x < mapa->tamaina_x) && (y >= 0 && y < mapa->tamaina_y))
	{
		baldosa = &(mapa->mapa[pos]);
	}

	return baldosa;
}

void mapa_rangoa_jarri(Mapa* mapa, int rangoa, int x_pos, int y_pos)
{
	for (int i = x_pos - rangoa; i <= x_pos + rangoa; i++)
	{
		for (int j = y_pos - rangoa; j <= y_pos + rangoa; j++)
		{
			Baldosa* baldosa = mapa_lortu_pos(mapa, i, j);
			if (baldosa != NULL)
			{
				if (baldosa->mota != Ibaia)
				{
					baldosa->markatuta = true;
					if (baldosa->tropa != NULL)
					{
						if (baldosa->tropa->id == jokoa_lortu_txanda())
						{
							baldosa->markatuta = false;
						}
					}
				}
			}
		}
	}
}

void mapa_rangoa_kendu(Mapa* mapa, int rangoa, int x_pos, int y_pos)
{
	for (int i = x_pos - rangoa; i <= x_pos + rangoa; i++)
	{
		for (int j = y_pos - rangoa; j <= y_pos + rangoa; j++)
		{
			Baldosa* baldosa = mapa_lortu_pos(mapa, i, j);
			if (baldosa != NULL)
			{
				baldosa->markatuta = false;
			}
		}
	}
}
