#ifndef MAPA_H
#define MAPA_H

#include "baldosa.h"

BaldosaMota mapa_1[] = {
	Larrea, Larrea, Larrea, Larrea, Larrea,
	Larrea, Mendia, Mendia, Ibaia, Larrea,
	Larrea, Larrea, Ibaia, Ibaia, Mendia,
	Mendia, Larrea, Mendia, Mendia, Mendia
};

typedef struct
{
	Baldosa* mapa;		/* 1D-n errepresentatutako matrizea */
} Mapa;

Mapa* Mapa_SortuMapa(BaldosaMota mapa[]);
void Mapa_BorratuMapa(Mapa* mapa);

#endif // !MAPA_H
