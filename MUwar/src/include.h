#ifndef INCLUDE_H
#define INCLUDE_H

/* Memoria ondo borratu den ikusteko */
#ifdef _DEBUG
		#define _CRTDBG_MAP_ALLOC
		#include <crtdbg.h>
#endif // _DEBUG


/* C STD */
#define _CRT_SECURE_NO_WARNINGS
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* SDL2 */
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

/* Erroreak, abisuak eta oharrak printeatzeko makroak */
#define ERROREA(X)		(fprintf(stderr, "Errorea: %s\n", X))
#define OHARRA(X)		(fprintf(stdout, "Oharra: %s\n", X))
#define ABISUA(X)		(fprintf(stderr, "Abisua: %s\n", X));

/* Erabili ez diren bariableak definitzeko */
#define ERABILI_GABE(X)	((void)(X))

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

#endif // !INCLUDE_H
