#ifndef MAPA_H
#define MAPA_H

#include "baldosa.h"

TerrenoMotak mapa_1[] = {
	Larrea, Larrea, Larrea, Larrea, Larrea,
	Larrea, Mendia, Mendia, Ibaia, Larrea,
	Larrea, Larrea, Ibaia, Ibaia, Mendia,
	Mendia, Larrea, Mendia, Mendia, Mendia
};

typedef struct
{
	Baldosa* mapa;		/* 1D-n errepresentatutako matrizea */
} Mapa;

Mapa* mapa_sortu(TerrenoMotak mapa[], int tamaina);
void mapa_borratu(Mapa** mapa);

#endif // !MAPA_H
