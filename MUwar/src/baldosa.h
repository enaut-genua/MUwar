#ifndef BALDOSA_H
#define BALDOSA_H

#include "tropa.h"

typedef enum
{
	Larrea,
	Ibaia,
	Karretera,
	Basoa,
	BasoMoztua,
	Mendia,
	MendiHautsia,	
	Hiria,
	Fabrika,
	Basea
} TerrenoMotak;

typedef struct
{
	Orientazioa noranzkoa;			/* Baldosaren noranzkoa, erabilagarria adibidez karreterak ondo lotzeko */
	TerrenoMotak mota;
	TropaStat* tropa;					/* Baldosa honetan dagoen tropa bati apuntatzen dio */
} Baldosa;

#endif // !BALDOSA_H
