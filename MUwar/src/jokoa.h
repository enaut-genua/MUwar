#ifndef JOKOA_H
#define JOKOA_H
/* C STD */
#define _CRT_SECURE_NO_WARNINGS
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include<SDL2/SDL_ttf.h>


/* SDL2 */
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include<string.h>

SDL_Window* window;
SDL_Renderer* renderer;
bool isRunning;

//______________________________________________TTF_____________________________________________________________________//

SDL_Texture* irudiak[20];
SDL_Renderer* getRenderer(void);
SDL_Renderer* getRenderer(void);
void textuaIdatzi(int x, int y, char* str);
void textuaGaitu(void);
void textuaDesgaitu(void);
void Textuak_idatzi();
//______________________________________________TTF_____________________________________________________________________//





#pragma region DEFINES
#define WINDOW_WIDTH     800
#define WINDOW_HEIGHT    800
#define TALE_X 30
#define TALE_Y 30
#define GORA 0
#define EZER 0
#define BEHERA 1
#define ESKUBI 2
#define EZKERRA 3
#define MARRAZTU 1
#define EZABATU 0
#pragma endregion


#pragma region ENUM
typedef enum { aurrera, atzera, eskubi, ezker }ORIENTAZIOAK;
typedef enum { belarzaria, ura, mendia,basea=4 }TERRENOAK;
#pragma endregion
ORIENTAZIOAK orientazioak;
TERRENOAK terrenoak;

#pragma region STRUCT
typedef struct XY
{
	int x, y;
} BI_D_KOORDENADAK;
BI_D_KOORDENADAK mapPos, mousePos, infoPos, isometric, cart, persona, tropa_org, tropa_dest, Tropa_desplazamendua;
typedef struct IRUDIAK {
	SDL_Texture* irudiak[4];
	int orientazioa;
	int terrenoMota;
	

} ORIENTAZIOA;
ORIENTAZIOA soldado, orco, terreno, cubo ;
//______________________________________________BEHEKO BARRA_____________________________________________________________________//
typedef struct {
	SDL_Texture* irudia;
	SDL_Rect laukia;
} BARRA;
BARRA Barra_Urdina,Barra_Gorria ;
//______________________________________________BEHEKO BARRA_____________________________________________________________________//
#pragma endregion

#pragma region FUNCTIONS
void init(char* titulo, int xpos, int ypos, int width, int height, bool fullscreen);
void handleEvents();
void update();
void render();
void clean();
void laukia(int x0, int y0, int w, int h, SDL_Rect* laukia);
void Mapa();
void MousePos();
void iso(int x0, int y0);
void cartesian(int isoY, int isoX);
void erakutsiTale(int xmouse, int ymouse);
void irudiakKargatu(SDL_Texture* gotorlekua[], char** link);
bool running();
void Dinamic_Move(int** trayectoria, int dinamicX, int dinamicY, int difdestorgx, int difdestorgy);
SDL_Texture* loadImage(char* file, SDL_Renderer* renderer);
void Rangoa(int rango, int borratu_edo_marraztu, int* XCuboInfo, int* YCuboInfo);
int Tropa_Org_Aukeratu(int* Xorg, int* Yorg, int* XCuboInfo, int* YCuboInfo);
void Zenbat_eta_nora_desplazatu_en_Baldosas(int* _orientazioa, int org, int dest, int* _dif, int* _difAbs);
void Tropa_Dest_Aukeratu(int  TropaDestX, int TropaDestY, int tropaOrgX, int TropaOrgY, int TerrenoDondePuedeAndar, int IpiniNahiDenTropa);
void Desplazamendua();
void Tropa_Aukeratzeko_barra_sortu();
int Barrako_tropa_aukeratu();
#pragma endregion
#endif // !JOKOA_H