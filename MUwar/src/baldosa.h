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

typedef enum
{
	Iparra,
	Hegoa,
	Ekialdea,
	Mendebaldea
} BaldosaNoranzkoa;

typedef struct
{
	BaldosaNoranzkoa noranzkoa;			/* Baldosaren noranzkoa, erabilagarria adibidez karreterak ondo lotzeko */
	TerrenoMotak mota;
	TropaStat* tropa;					/* Baldosa honetan dagoen tropa bati apuntatzen dio */
} Baldosa;

#endif // !BALDOSA_H
