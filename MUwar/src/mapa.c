#include <stdlib.h>

#include "mapa.h"

static void prestatu_mapa(Mapa *mapa, int dimx, int dimy);

void Mapa_BorratuMapa(Mapa* mapa)
{
	free(mapa->mapa);
	mapa->mapa = NULL;
}

void prestatu_mapa(Mapa *mapa, int dimx, int dimy)
{
	mapa->mapa = (Baldosa*)malloc(dimx * dimy * sizeof(Baldosa));
}

