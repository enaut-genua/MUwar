#ifndef MAPA_H
#define MAPA_H

#include "baldosa.h"

BaldosaMota mapa_1[] = {
	Larrea, Larrea, Larrea, Larrea, Larrea,
	Larrea, Mendia, Mendia, Ibaia, Larrea,
	Larrea, Larrea, Ibaia, Ibaia, Mendia,
};

typedef struct
{
	Baldosa* mapa;		/* 1D-n errepresentatutako matrizea */
} Mapa;

void Mapa_BorratuMapa(Mapa* mapa);

#endif // !MAPA_H
