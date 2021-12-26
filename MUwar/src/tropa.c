#include "tropa.h"

#include <stdlib.h>

/* Funtzio laguntzaileak */
static void EraikiInfanteria(TropaStat* trp);
static void EraikiInfanteriaMek(TropaStat* trp);
static void EraikiErrekonozimentua(TropaStat* trp);
static void EraikiTankeArina(TropaStat* trp);
static void EraikiTankeHand(TropaStat* trp);

TropaStat* Tropa_SortuTropa(TropaMota mota)
{
	TropaStat* ret = NULL;

	switch (mota)
	{
	case Infanteria:
		ret = (TropaStat*)malloc(sizeof(TropaStat));
		EraikiInfanteria(ret);
		break;
	case InfanteriaMek:
		ret = (TropaStat*)malloc(sizeof(TropaStat));
		EraikiInfanteriaMek(ret);
		break;
	case Errekonozimentu:
		ret = (TropaStat*)malloc(sizeof(TropaStat));
		EraikiErrekonozimentua(ret);
		break;
	case TankeArina:
		ret = (TropaStat*)malloc(sizeof(TropaStat));
		EraikiTankeArina(ret);
		break;
	case TankeHand:
		ret = (TropaStat*)malloc(sizeof(TropaStat));
		EraikiTankeHand(ret);
		break;
	default:
		ret = NULL;
	}

	return ret;
}

void Tropa_BorratuTropa(TropaStat* tropa)
{
	free(tropa);
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

void EraikiTankeArina(TropaStat* trp)
{
	trp->bizitza = 250;
	trp->atakea = 30;
	trp->amunizioa = 12;
	trp->errekurtsoak = 12;
	trp->mug_max = 8;
	trp->mota = TankeArina;
	trp->terrenoa_puskatu = true;
	trp->hiriak_hartu = false;
}

void EraikiTankeHand(TropaStat* trp)
{
	trp->bizitza = 350;
	trp->atakea = 50;
	trp->amunizioa = 10;
	trp->errekurtsoak = 10;
	trp->mug_max = 6;
	trp->mota = TankeHand;
	trp->terrenoa_puskatu = true;
	trp->hiriak_hartu = false;
}