#ifndef RENDERIZADOREA_H
#define RENDERIZADOREA_H

#include "include.h"

#include "mapa.h"

/* renderizadorea sortzen du. Liburutegiak hasieratzen dira,mapa sortzen da , renderizadorea sortzen da eta texturak sortzen dira  */
bool render_sortu(int xpos, int ypos, int width, int height, bool fullscreen);

/* Memoria garbitzen du */
void render_garbitu(void);

/* Funtzio honek Behin eta berriz marraztuko du */
bool render_marraztu(Mapa* mapa);

/* Funtzio honek argazkien tamaina handitzen du */
void render_handitu_argazkiak(void);

/* Funtzio honek argazkien tamaina txikitzen du */
void render_txikitu_argazkiak(void);

/* Funtzio hauek maparen lehen baldosaren posizioa aldatzen dute */
void render_mugitu_mapa_gora(float dt);
void render_mugitu_mapa_behera(float dt);
void render_mugitu_mapa_eskubi(float dt);
void render_mugitu_mapa_ezker(float dt);

/* Funtzio honek FPSak erakutsiko ditu */
void render_erakutsi_fps(float dt);

/* Lortzeko */
int render_lortu_argazki_tamaina(void);
Bekt2D render_lortu_mapa_nondik_hasi_marrazten(void);
Bekt2D render_lortu_leiho_tamaina(void);

/* Pathean dagoen argazkiaren textura sortzen du */
SDL_Texture* render_textura_sortu(const char* path, uint8_t alpha);

/* Lortu renderer */
SDL_Renderer* render_lortu_render(void);

/* Lortu window */
SDL_Window* render_lortu_window(void);

/* Fondoa kolorez aldatu */
bool render_aldatu_fondoa(void);

#endif // !RENDERIZADOREA_H