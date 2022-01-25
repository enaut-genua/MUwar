#include "baldosa.h"

bool baldosa_aldatu_mota(Baldosa* baldosa)
{
	bool aldaketa = false;
	if (baldosa != NULL)
	{
		if (baldosa->tropa != NULL)
		{
			switch (baldosa->tropa->mota)
			{
			case Infanteria:
			case InfanteriaMek:
				if (baldosa->mota == Herria)
				{
					baldosa->mota = HerriHautsia;
					aldaketa = true;
				}
				else if (baldosa->mota == Basoa)
				{
					baldosa->mota = BasoMoztua;
					aldaketa = true;
				}
				break;
			case Rekon:
			case Tanke:
				if (baldosa->mota == Mendia)
				{
					baldosa->mota = MendiHautsia;
					aldaketa = true;
				}
				else if (baldosa->mota == Herria)
				{
					baldosa->mota = HerriHautsia;
					aldaketa = true;
				}
				else if (baldosa->mota == Basoa)
				{
					baldosa->mota = BasoMoztua;
					aldaketa = true;
				}
				break;
			}
		}
	}

	return aldaketa;
}