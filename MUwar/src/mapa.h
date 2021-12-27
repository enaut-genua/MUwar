#ifndef MAPA_H
#define MAPA_H

#include "baldosa.h"

typedef struct
{
	Baldosa* mapa;		/* 1D-n errepresentatutako matrizea */
} Mapa;


void Mapa_BorratuMapa(Mapa* mapa);

#endif // !MAPA_H
