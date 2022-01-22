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

/* Tekla bat errepresentatzen dituen estruktura */
typedef struct
{
	bool sakatu;
	bool askatu;
	bool sakatuta;
} Tekla;

/* Teklatua errepresentatzen duen estruktura */
typedef struct
{
	bool enter;
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

#endif // !EBENTUAK_H

