#include <stdlib.h>

#include "mapa.h"


Mapa* mapa_sortu(TerrenoMotak mapa_array[], int tamaina)
{
	/* Sortu Mapa estruktura eta barruko Baldosa* arraya */
	Mapa* mapa = (Mapa*)calloc(1, sizeof(Mapa));
	mapa->mapa = (Baldosa*)calloc(tamaina, sizeof(Baldosa) * tamaina);

	for (int i = 0; i < tamaina; i++)
	{
		mapa->mapa[i].mota = mapa_array[i];
	}

	return mapa;
}

void mapa_borratu(Mapa** mapa)
{
	free((*mapa)->mapa);
	free(*mapa);
	*mapa = NULL;
}