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
	TropaStat* tropa;					/* Baldosa honetan dagoen tropa bati apuntatzen dio */
	Orientazioa noranzkoa;				/* Baldosaren noranzkoa, erabilagarria adibidez karreterak ondo lotzeko */
	TerrenoMotak mota;
	bool aukeratuta;					/* Baldosa aukeratuta dagoen ala ez */
} Baldosa;


#endif // !BALDOSA_H