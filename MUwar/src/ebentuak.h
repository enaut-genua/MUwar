#ifndef EBENTUAK_H
#define EBENTUAK_H

#include "include.h"

/* Erabiltzaileak egindako ebentuak kudeatzen ditu */
void ebentuak_kudeatu(void);

/* Erabiltzaileak jokoa gelditu duen ala ez esaten du */
bool ebentuak_martxan_jokoa(void);

/* Xaguaren posizioa lortu */
Bekt2D ebentuak_lortu_xagu_pos(void);

#endif // !EBENTUAK_H

