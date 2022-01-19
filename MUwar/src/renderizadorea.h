#ifndef RENDERIZADOREA_H
#define RENDERIZADOREA_H

#include "include.h"

#include "mapa.h"

/* renderizadorea sortzen du */
bool render_sortu(char* titulo, int xpos, int ypos, int width, int height, bool fullscreen);

/* Memoria garbitzen du */
void render_garbitu(void);

/* Funtzio honek Behin eta berriz marraztuko du */
bool render_marraztu(Mapa* mapa);

/* Funtzio honek argazkien tamaina handitzen du */
void render_handitu_argazkiak(void);

/* Funtzio honek argazkien tamaina txikitzen du */
void render_txikitu_argazkiak(void);

/* Funtzio hauek maparen lehen baldosaren posizioa aldatzen dute */
void render_mugitu_mapa_gora(void);
void render_mugitu_mapa_behera(void);
void render_mugitu_mapa_eskubi(void);
void render_mugitu_mapa_ezker(void);

/* Getters/Setters */
const int render_lortu_argazki_tamaina(void);
const Bekt2D render_lortu_mapa_nondik_hasi_marrazten(void);

#endif // !RENDERIZADOREA_H