#ifndef BEKTOREA_H
#define BEKTOREA_H

#include "include.h"

typedef struct
{
	size_t luzeera;
	size_t kapazidadea;
	size_t datu_tamaina;
	uint8_t** datuak;
} Bektorea;

Bektorea* bektorea_sortu(size_t datu_tamaina, size_t kapazidadea);
void bektorea_borratu(Bektorea** bekt);

size_t bektorea_lortu_kapazidadea(const Bektorea* bekt);
size_t bektorea_lortu_luzeera(const Bektorea* bekt);
size_t bektorea_lortu_datu_tamaina(const Bektorea* bekt);

bool bektorea_hutsik_dago(const Bektorea* bekt);

bool bektorea_handitu(Bektorea* bekt);
bool bektorea_estutu(Bektorea* bekt);

bool bektorea_sartu_posizioan(Bektorea* bekt, const size_t posizioa, const uint8_t* sartuko_dena);
bool bektorea_sartu_atzean(Bektorea* bekt, const uint8_t* sartuko_dena);
bool bektorea_sartu_aurrean(Bektorea* bekt, const uint8_t* sartuko_dena);

bool bektorea_borratu_posizioan(Bektorea* bekt, const size_t posizioa);
bool bektorea_borratu_aurrean(Bektorea* bekt);
bool bektorea_borratu_atzean(Bektorea* bekt);

uint8_t* bektorea_lortu_balioa_posizioan(Bektorea* bekt, const size_t posizioa,  uint8_t* erreferentzia);
uint8_t* bektorea_lortu_balioa_atzean(Bektorea* bekt, uint8_t* erreferentzia);

#endif // !BEKTOREA_H
