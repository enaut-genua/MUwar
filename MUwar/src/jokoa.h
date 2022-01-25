#ifndef JOKOA_H
#define JOKOA_H

#include "baldosa.h"
#include "mapa.h"
#include "jokalaria.h"


/* Jokoaren elementuak prestatu. Bertan mapa eta renderizadorea sortzeaz gain, ebentuak jasotzeko prestatzen da programa. */
bool jokoa_prestatu(void);

/* Jokoaren elementuak garbitu */
void jokoa_garbitu(void);

/* Jokoa hasi */
bool jokoa_hasi(void);

/* Lortu noren txanda */
Bandoa jokoa_lortu_txanda(void);

#endif // !JOKOA_H
