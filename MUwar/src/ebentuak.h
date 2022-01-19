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

/* Erabiltzaileak egindako ebentuak kudeatzen ditu */
void ebentuak_kudeatu(void);

/* Erabiltzaileak jokoa gelditu duen ala ez esaten du */
void ebentuak_konfiguratu(bool* interruptorea);

/* Xaguaren egoera lortu */
const Xagua* ebentuak_lortu_xaguaren_egoera(void);

#endif // !EBENTUAK_H

