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

TropaStat* tropa_sortu(TropaMota mota, Bandoa id)
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
	if (*tropa != NULL)
	{
		free(*tropa);
		*tropa = NULL;
	}
}

void tropa_atakatu(TropaStat** erasotzailea, TropaStat** erasotua)
{
	if (erasotzailea != NULL && erasotua != NULL)
	{
		(*erasotzailea)->bizitza -= (int)(floor(((*erasotua)->atakea - (*erasotzailea)->defentsa) * 0.75));

		if ((*erasotzailea)->bizitza <= 0)
		{
			tropa_borratu(erasotzailea);
		}

		(*erasotua)->bizitza -= (int)(floor(((*erasotzailea)->atakea - (*erasotua)->defentsa)));
		if ((*erasotua)->bizitza <= 0)
		{
			tropa_borratu(erasotua);
		}

	}
}

void tropa_orientazioa(Bektorea* bidea, TropaStat* tropa)
{
	Bekt2D azken_aurreko_balorea = { 0 };
	Bekt2D azken_balorea = { 0 };

	bektorea_lortu_balioa_posizioan(bidea, bektorea_lortu_luzeera(bidea) - 2, (uint8_t*)(&azken_aurreko_balorea));
	bektorea_lortu_balioa_atzean(bidea, (uint8_t*)(&azken_balorea));

	int dif_x = azken_aurreko_balorea.x - azken_balorea.x;
	int dif_y = azken_aurreko_balorea.y - azken_balorea.y;

	if (dif_x < 0 && dif_y == 0)
	{
		tropa->orientazioa = Aurrea;
	}
	else if (dif_x > 0 && dif_y == 0)
	{
		tropa->orientazioa = Atzea;
	}
	else if (dif_x == 0 && dif_y < 0)
	{
		tropa->orientazioa = Ezker;
	}
	else if (dif_x == 0 && dif_y > 0)
	{
		tropa->orientazioa = Eskubi;
	}
}

/*
 *	START: Funtzio pribatuen inplementazioa
 */

void eraiki_infanteria(TropaStat* trp)
{
	trp->bizitza = 100;
	trp->atakea = 10;
	trp->defentsa = 1;
	trp->amunizioa = 10;
	trp->errekurtsoak = 20;
	trp->mug_max = 4;
	trp->mota = Infanteria;
}

void eraiki_infanteria_mek(TropaStat* trp)
{
	trp->bizitza = 100;
	trp->atakea = 20;
	trp->defentsa = 10;
	trp->amunizioa = 7;
	trp->errekurtsoak = 20;
	trp->mug_max = 3;
	trp->mota = InfanteriaMek;
}

void eraiki_errekonozimentua(TropaStat* trp)
{
	trp->bizitza = 100;
	trp->atakea = 15;
	trp->defentsa = 20;
	trp->amunizioa = 5;
	trp->errekurtsoak = 15;
	trp->mug_max = 10;
	trp->mota = Rekon;

}

void eraiki_tanke(TropaStat* trp)
{
	trp->bizitza = 100;
	trp->atakea = 30;
	trp->defentsa = 40;
	trp->amunizioa = 12;
	trp->errekurtsoak = 12;
	trp->mug_max = 8;
	trp->mota = Tanke;
}

/*
 *	END: Funtzio pribatuen inplementazioa
 */