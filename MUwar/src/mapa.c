#include <stdlib.h>

#include "mapa.h"


Mapa* mapa_sortu(TerrenoMotak mapa_array[], int tamaina_x, int tamaina_y)
{
	Mapa* mapa = NULL;
	
	/* Kalkulatu tamaina totala */
	int tamaina = tamaina_x * tamaina_y;

	/* Sortu mapa eta begiratu errorerik gertatu den */
	if ((mapa = (Mapa*)calloc(1, sizeof(Mapa))) == NULL)
	{
		fprintf(stderr, "Errorea mapa sortzean!\n");
		goto atera;
	}

	/* Sortu mapa barruko Baldosa* bektorea eta begiratu ea errorerik gertatu den */
	if ((mapa->mapa = (Baldosa*)calloc(tamaina, sizeof(Baldosa))) == NULL)
	{
		fprintf(stderr, "Errorea 'baldosa*' bektorea sortzean\n");
		mapa_borratu(&mapa);
		goto atera;
	}

	mapa->tamaina_x = tamaina_x;
	mapa->tamaina_y = tamaina_y;

	for (int i = 0; i < tamaina; i++)
	{
		mapa->mapa[i].mota = mapa_array[i];
	}

atera:
	return mapa;
}

void mapa_borratu(Mapa** mapa)
{
	free((*mapa)->mapa);
	free(*mapa);
	*mapa = NULL;
}

Baldosa* mapa_lortu_pos(Mapa* mapa, int x, int y)
{
	int pos = x + mapa->tamaina_x * y;
	return &(mapa->mapa[pos]);
}
