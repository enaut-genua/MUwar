#ifndef JOKOA_H
#define JOKOA_H

#include "baldosa.h"
#include "mapa.h"

/* Jokoaren elementuak prestatu */
bool jokoa_prestatu(void);

/* Jokoaren elementuak garbitu */
void jokoa_garbitu(void);

/* Jokoa hasi */
bool jokoa_hasi(void);

/* Mugitu Tropa */
bool jokoa_mugitu_tropa(Baldosa* hasiera, Baldosa* bukaera);

#endif // !JOKOA_H
