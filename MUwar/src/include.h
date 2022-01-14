#ifndef MAIN_H
#define MAIN_H

/* Memoria ondo borratu den ikusteko */
#ifdef _DEBUG
		#define _CRTDBG_MAP_ALLOC
		#include <crtdbg.h>
#endif // _DEBUG


/* C STD */
#define _CRT_SECURE_NO_WARNINGS
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>


/* SDL2 */
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


/* Estruktura erabilgarriak */

typedef struct
{
	int x;
	int y;
} Bekt2D;

/* Enumerazio erabilgarriak */

typedef enum
{
	Aurrea,
	Atzea,
	Ezker,
	Eskubi
} Orientazioa;

#endif // !MAIN_H
