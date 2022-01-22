#include "tropa.h"


/*
 *	START: Funtzio pribatuen deklarazioa
 */

static void eraiki_infanteria(TropaStat* trp);
static void eraiki_infanteria_mek(TropaStat* trp);
static void eraiki_errekonozimentua(TropaStat* trp);
static void eraiki_tanke(TropaStat* trp);

/*
 *	END: Funtzio pribatuen deklarazioa
 */

TropaStat* tropa_sortu(TropaMota mota, Jokalaria id)
{
	/* Sortu TropaStat estruktura bat */
	TropaStat* ret = (TropaStat*)calloc(1, sizeof(TropaStat));
	
	if (ret != NULL)
	{
		ret->id = id;
		ret->orientazioa = Aurrea;
		switch (mota)
		{
		case Infanteria:
			eraiki_infanteria(ret);
			break;
		case InfanteriaMek:
			eraiki_infanteria_mek(ret);
			break;
		case Rekon:
			eraiki_errekonozimentua(ret);
			break;
		case Tanke:
			eraiki_tanke(ret);
			break;
		default:
			ABISUA("Errekonozitzen ez den tropa bat sortzen saiatu da.");
			tropa_borratu(&ret);
		}
	}

	return ret;
}

void tropa_borratu(TropaStat** tropa)
{
	free(*tropa);
	*tropa = NULL;
}

/*
 *	START: Funtzio pribatuen inplementazioa
 */

void eraiki_infanteria(TropaStat* trp)
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

void eraiki_infanteria_mek(TropaStat* trp)
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

void eraiki_errekonozimentua(TropaStat* trp)
{
	trp->bizitza = 150;
	trp->atakea = 15;
	trp->amunizioa = 5;
	trp->errekurtsoak = 15;
	trp->mug_max = 10;
	trp->mota = Rekon;
	trp->terrenoa_puskatu = false;
	trp->hiriak_hartu = false;
}

void eraiki_tanke(TropaStat* trp)
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

/*
 *	END: Funtzio pribatuen inplementazioa
 */