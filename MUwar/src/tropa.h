#ifndef TROPA_H
#define TROPA_H

#include "include.h"

#include "jokalaria.h"

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
	Jokalaria id;				/* Zeinen tropa den */
	int bizitza;				/* Zenbat bizitza daukaten */
	int atakea;					/* Zenbat atake daukaten */
	int amunizioa;				/* Zenbat amunizio daukaten */
	int errekurtsoak;			/* Bizirik jarraitzeko behar dituzten errekurtsoak. Adib, gasolina ala janaria */
	int mug_max;				/* Zenbat mugitu daitezken kondizio idealetan */
	TropaMota mota;				/* Tropa mota */
	Orientazioa orientazioa;	/* Tropak begiratzen duen orientazioa */
	bool terrenoa_puskatu;		/* Terrenoa puskatzeko gaitasuna */
	bool hiriak_hartu;			/* Hiriak hartzeko gaitasuna */
} TropaStat;

/* Sortu tropak memorian */
TropaStat* tropa_sortu(TropaMota mota, Jokalaria id);

/* Borratu tropa */
void tropa_borratu(TropaStat** tropa);

///* Tropa mugitu */
//bool tropa_mugitu(Baldosa * baldosa_1);

#endif // TROPAK_H