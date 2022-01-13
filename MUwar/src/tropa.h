#ifndef TROPA_H
#define TROPA_H

#include "include.h"

/* Jokuan erabiliko diren tropa motak. */
typedef enum
{
	Infanteria,
	InfanteriaMek,
	Errekonozimentu,
	Tanke
} TropaMota;

/* Tropen estatistikak */
typedef struct
{
	int id;					/* Zeinen tropa den */
	int bizitza;			/* Zenbat bizitza daukaten */
	int atakea;				/* Zenbat atake daukaten */
	int amunizioa;			/* Zenbat amunizio daukaten */
	int errekurtsoak;		/* Bizirik jarraitzeko behar dituzten errekurtsoak. Adib, gasolina ala janaria */
	int mug_max;			/* Zenbat mugitu daitezken kondizio idealetan */
	TropaMota mota;			/* Tropa mota */
	bool terrenoa_puskatu;	/* Terrenoa puskatzeko gaitasuna */
	bool hiriak_hartu;		/* Hiriak hartzeko gaitasuna */
} TropaStat;

/* Sortu tropak memorian */
TropaStat* tropa_sortu(TropaMota mota, int id);

/* Borratu tropa */
void tropa_borratu(TropaStat** tropa);

#endif // TROPAK_H