#ifndef BALDOSA_H
#define BALDOSA_H

#include "tropa.h"

typedef enum
{
	Basamortua,
	Base_gorria,
	Base_urdina,
	Basoa,
	BasoMoztua,
	Fabrika,
	Herria,
	HerriHautsia,
	Ibaia,
	Karretera,
	Larrea,
	Mendia,
	MendiHautsia,
} TerrenoMotak;

typedef struct
{
	TropaStat* tropa;					/* Baldosa honetan dagoen tropa bati apuntatzen dio */
	Orientazioa noranzkoa;				/* Baldosaren noranzkoa, erabilagarria adibidez karreterak ondo lotzeko */
	TerrenoMotak mota;
	bool markatuta;					/* Baldosa aukeratuta dagoen ala ez */
} Baldosa;

/* Aldatu baldosaren mota, troparen arabera */
bool baldosa_aldatu_mota(Baldosa* baldosa);

#endif // !BALDOSA_H
