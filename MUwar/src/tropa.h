#ifndef TROPA_H
#define TROPA_H

#include "include.h"

#include "jokalaria.h"
#include "bektorea.h"

/* Jokuan erabiliko diren tropa motak. */
typedef enum
{
	Infanteria,
	InfanteriaMek,
	Rekon,
	Tanke
} TropaMota;

/* Tropen estatistikak */
typedef struct
{
	bool mugitu_da;
	Bandoa id;					/* Zeinen tropa den */
	int bizitza;				/* Zenbat bizitza daukaten */
	int atakea;					/* Zenbat atake daukaten */
	int defentsa;				/* Zenbat defentsa duen */
	int amunizioa;				/* Zenbat amunizio daukaten */
	int errekurtsoak;			/* Bizirik jarraitzeko behar dituzten errekurtsoak. Adib, gasolina ala janaria */
	int mug_max;				/* Zenbat mugitu daitezken kondizio idealetan */
	TropaMota mota;				/* Tropa mota */
	Orientazioa orientazioa;	/* Tropak begiratzen duen orientazioa */
	//bool terrenoa_puskatu;		/* Terrenoa puskatzeko gaitasuna */
	//bool hiriak_hartu;			/* Hiriak hartzeko gaitasuna */
} TropaStat;

/* Sortu tropak memorian */
TropaStat* tropa_sortu(TropaMota mota, Bandoa id);

/* Borratu tropa */
void tropa_borratu(TropaStat** tropa);

/* Bi tropen arteko konfliktoa */
void tropa_atakatu(TropaStat** erasotzailea, TropaStat** erasotua);

/* Tropa orientazioa kalkulatu */
void tropa_orientazioa(Bektorea* bekt, TropaStat* tropa);

#endif // TROPAK_H