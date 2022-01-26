#ifndef EBENTUAK_H
#define EBENTUAK_H

#include "include.h"

/* Xagua errepresentatzen duen estruktura */
typedef struct
{
	bool ezker_botoia_klikatuta;
	bool eskubi_botoia_klikatuta;
	Bekt2D posizio_erreala;
	Bekt2D mapako_posizioa;
} Xagua;

/* Teklatua errepresentatzen duen estruktura */
typedef struct
{
	bool enter;
	bool a;
	bool s;
	bool d;
	bool w;
} Teklatua;

/* Erabiltzaileak egindako ebentuak kudeatzen ditu */
void ebentuak_kudeatu(void);

/* Erabiltzaileak jokoa gelditu duen ala ez esaten du */
void ebentuak_konfiguratu(bool* interruptorea);

/* Xaguaren egoera lortu */
const Xagua* ebentuak_lortu_xaguaren_egoera(void);

/* Teklen egoera zaharra lortu */
const Teklatua* ebentuak_lortu_teklatua_zaharra(void);

/* Teklen egoera berria lortu */
const Teklatua* ebentuak_lortu_teklatua_berria(void);

/* Lehioaren tamaina berria lortu */
Bekt2D ebentuak_lortu_lehio_tamaina_berria(void);

/* Lehioaren tamaina zaharra lortu */
Bekt2D ebentuak_lortu_lehio_tamaina_zaharra(void);

#endif // !EBENTUAK_H

