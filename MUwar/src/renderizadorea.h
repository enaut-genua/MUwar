#ifndef RENDERIZADOREA_H
#define RENDERIZADOREA_H

#include "main.h"

/* Renderizadorea sortzen du */
bool render_init(char* titulo, int xpos, int ypos, int width, int height, bool fullscreen);

/* Memoria garbitzen du */
void render_garbitu(void);

/* Funtzio honek Behin eta berriz marraztuko du */
bool render_marraztu(void);


#endif // !RENDERIZADOREA_H
