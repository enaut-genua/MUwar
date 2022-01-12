#include "tropa.h"

#include <stdlib.h>

/* Funtzio laguntzaileak */
static void EraikiInfanteria(TropaStat* trp);
static void EraikiInfanteriaMek(TropaStat* trp);
static void EraikiErrekonozimentua(TropaStat* trp);
static void EraikiTanke(TropaStat* trp);

TropaStat* Tropa_SortuTropa(TropaMota mota, int id)
{
	TropaStat* ret = (TropaStat*)malloc(sizeof(TropaStat));
	
	if (ret != NULL)
	{
		ret->id = id;
		switch (mota)
		{
		case Infanteria:
			EraikiInfanteria(ret);
			break;
		case InfanteriaMek:
			EraikiInfanteriaMek(ret);
			break;
		case Errekonozimentu:
			EraikiErrekonozimentua(ret);
			break;
		case Tanke:
			EraikiTanke(ret);
			break;
		default:
			Tropa_BorratuTropa(&ret);
		}
	}

	return ret;
}

void Tropa_BorratuTropa(TropaStat** tropa)
{
	free(*tropa);
	*tropa = NULL;
}

void EraikiInfanteria(TropaStat* trp)
{
	trp->bizitza = 100;
	trp->atakea = 10;
	trp->amunizioa = 10;
	trp->errekurtsoak = 20;
	trp->mug_max = 4;
	trp->mota = Infanteria;
	trp->terrenoa_puskatu = false;
	trp->hiriak_hartu = true;
}

void EraikiInfanteriaMek(TropaStat* trp)
{
	trp->bizitza = 100;
	trp->atakea = 20;
	trp->amunizioa = 7;
	trp->errekurtsoak = 20;
	trp->mug_max = 3;
	trp->mota = InfanteriaMek;
	trp->terrenoa_puskatu = true;
	trp->hiriak_hartu = true;
}

void EraikiErrekonozimentua(TropaStat* trp)
{
	trp->bizitza = 150;
	trp->atakea = 15;
	trp->amunizioa = 5;
	trp->errekurtsoak = 15;
	trp->mug_max = 10;
	trp->mota = Errekonozimentu;
	trp->terrenoa_puskatu = false;
	trp->hiriak_hartu = false;
}

void EraikiTanke(TropaStat* trp)
{
	trp->bizitza = 250;
	trp->atakea = 30;
	trp->amunizioa = 12;
	trp->errekurtsoak = 12;
	trp->mug_max = 8;
	trp->mota = Tanke;
	trp->terrenoa_puskatu = true;
	trp->hiriak_hartu = false;
}
