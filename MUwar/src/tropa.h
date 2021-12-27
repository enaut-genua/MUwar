#ifndef TROPA_H
#define TROPA_H

#include <stdbool.h>

/* Jokuan erabiliko diren tropa motak. */
typedef enum
{
	Infanteria,
	InfanteriaMek,
	Errekonozimentu,
	TankeArina,
	TankeHand,
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
TropaStat* Tropa_SortuTropa(TropaMota mota, int id);

/* Borratu tropa */
void Tropa_BorratuTropa(TropaStat** tropa);

#endif // TROPAK_H