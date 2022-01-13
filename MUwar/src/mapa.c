#include <stdlib.h>

#include "mapa.h"


Mapa* mapa_sortu(BaldosaMota mapa_array[], int tamaina)
{
	Mapa* mapa = (Mapa*)malloc(sizeof(Mapa));
	mapa->mapa = (Baldosa*)malloc(sizeof(Baldosa) * tamaina);

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