#include"jokoa.h"
#include"mapa.h"
bool editMap = false;
bool editPeople = false;
int aurrekotale = 0, azkenLehentale = 0;
int TAMAÑOIMAGEN = 100;
int rango = 2;
int DetektatutakoTropa;
int tmpposx, tmpposy;
void init(char* titulo, int xpos, int ypos, int width, int height, bool fullscreen) {
	int flags = 0;
	if (fullscreen)flags = SDL_WINDOW_FULLSCREEN_DESKTOP;
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		window = SDL_CreateWindow(titulo, xpos, ypos, width, height, flags | SDL_WINDOW_RESIZABLE | SDL_WINDOW_FOREIGN);
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE | SDL_RENDERER_PRESENTVSYNC);
		SDL_SetRenderDrawColor(renderer, 0xaa, 0xaa, 0x3b, 0x00);
		isRunning = true;
	}
}

void handleEvents() {
	MousePos();

	SDL_Event event;
	
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_MOUSEWHEEL)
		{
			if (event.wheel.y > 0 && TAMAÑOIMAGEN < 500)TAMAÑOIMAGEN += 5;
			else if (event.wheel.y < 0 && TAMAÑOIMAGEN>70)TAMAÑOIMAGEN -= 5;
		}
		switch (event.button.type)
		{
		case SDL_MOUSEBUTTONDOWN:
			if (PERTSONAK[infoPos.y][infoPos.x] > 0  && editMap == false) {
			
				editMap = true;
				DetektatutakoTropa = PERTSONAK[infoPos.y][infoPos.x];
				tmpposx = infoPos.x;
				tmpposy = infoPos.y;
				printf("\nTROPA AUKERATU DA\n");
				RangoaIpini(rango);
			}
			else if (editMap) {
				if (RANGO_JOKALARIARENA[infoPos.y][infoPos.x] == 1) {
					PERTSONAK[tmpposy][tmpposx] = 0;
					persona.x = infoPos.x;
					persona.y = infoPos.y;
					PERTSONAK[persona.y][persona.x] = DetektatutakoTropa;
					printf("\nTROPA MUGITU DA DA\n");
				}
				RangoaEzabatu();
				editMap = false;
			}
			break;
		}
		switch (event.key.type) {
		case SDL_KEYDOWN:

			switch (event.key.keysym.sym) {

			case SDLK_ESCAPE:
				isRunning = false; 
				break;
			case SDLK_p:
				persona.y = TALE_Y-1;
				editPeople = true;  break;
			case SDLK_o:
				editPeople = false;  break;
			case SDLK_w:mapPos.x += (int)(TAMAÑOIMAGEN * 0.5); mapPos.y -= (int)(TAMAÑOIMAGEN * 0.5); break;
			case SDLK_s:mapPos.x -= (int)(TAMAÑOIMAGEN * 0.5); mapPos.y += (int)(TAMAÑOIMAGEN * 0.5); break;
			case SDLK_d:mapPos.x -= (int)(TAMAÑOIMAGEN * 0.5); mapPos.y -= (int)(TAMAÑOIMAGEN * 0.5); break;
			case SDLK_a:mapPos.x += (int)(TAMAÑOIMAGEN * 0.5); mapPos.y += (int)(TAMAÑOIMAGEN * 0.5); break;
			case SDLK_RIGHT:Desplazatu(tmpposx, tmpposy,1, 0, 2); break;
			case SDLK_LEFT:Desplazatu(-1, 0, 3); break;
			case SDLK_DOWN:Desplazatu(0, 1, 1); break;
			case SDLK_UP:Desplazatu(0, -1, 0); break;
			case SDLK_e:

				break;
			}
		}
	}
	
}
void RangoaEzabatu() {
	for (int y = 0; y <= TALE_Y - 1; y++)
	{
		for (int x = 0; x <= TALE_X - 1; x++)
		{
			RANGO_JOKALARIARENA[y][x] = 0;
		}
	}
}
void RangoaIpini(int rango) {
	if (editPeople == true) {
		RangoaEzabatu();
		printf(" RANGOA MARRAZTU DA\n");
		for (int y = 0; y < (rango * 2) + 1; y++)
		{
			for (int x = 0; x < (rango * 2) + 1; x++)
			{
				if (TERRENO[infoPos.y + y - rango][infoPos.x + x - rango] <= 1 && infoPos.y + y - rango >= 0 && infoPos.x + x - rango >= 0 && infoPos.y + y - rango < TALE_Y && infoPos.x + x - rango < TALE_X)
					RANGO_JOKALARIARENA[infoPos.y + y - rango][infoPos.x + x - rango] = 1;
			}
		}
	}
}
void Desplazatu(int x, int y, int orientazioa) {
	if (editPeople == true) {
		persona.x += x;
		persona.y += y;
		if (TERRENO[persona.y][persona.x] > 1 || persona.x<0 || persona.y < 0 || persona.x >TALE_X - 1 || persona.y >TALE_Y - 1)
		{
			persona.x -= x;
			persona.y -= y;
		}
		if (TERRENO[persona.y][persona.x] <= 1 && (persona.y >= 0 && persona.y <= TALE_Y - 1 && persona.x >= 0 && persona.x <= TALE_Y - 1))
		{
			
			PERTSONAK[persona.y][persona.x] = DetektatutakoTropa;
			soldado.orientazioa = orientazioa;
			PERTSONAK[persona.y - y][persona.x - x] = 0;
		}
	}
}
void MousePos(void) {
	int buttons;
	SDL_PumpEvents();  // make sure we have the latest mouse state.
	buttons = SDL_GetMouseState(&mousePos.x, &mousePos.y);
}
SDL_Texture* loadImage(char* file, SDL_Renderer* render) {
	SDL_Surface* tmpSurface = IMG_Load(file);
	SDL_Texture* Tex = SDL_CreateTextureFromSurface(render, tmpSurface);
	SDL_FreeSurface(tmpSurface);
	return Tex;
}
void laukia(int x0, int y0, int w, int h, SDL_Rect* laukia)
{
	laukia->h = h;
	laukia->w = w;
	laukia->x = x0;
	laukia->y = y0;
}
void Mapa() {
	SDL_Rect laukiakk;
	for (int yy = 0; yy < TALE_Y; yy++) {
		for (int xx = 0; xx < TALE_X; xx++) {
			iso((TAMAÑOIMAGEN * 0.5) * xx + mapPos.x, (TAMAÑOIMAGEN * 0.5) * yy - mapPos.y);

			laukia(isometric.x, isometric.y, TAMAÑOIMAGEN, TAMAÑOIMAGEN, &laukiakk);

			switch (TERRENO[yy][xx]) {
			case 1:SDL_RenderCopy(renderer, terreno.irudiak[belarzaria], NULL, &laukiakk); break;
			case 2:SDL_RenderCopy(renderer, terreno.irudiak[ura], NULL, &laukiakk); break;
			case 3:SDL_RenderCopy(renderer, terreno.irudiak[mendia], NULL, &laukiakk); break;
			}
			switch (RANGO_JOKALARIARENA[yy][xx]) {
			case 1:SDL_RenderCopy(renderer, cubo.irudiak[2], NULL, &laukiakk); break;
			}
			switch (PERTSONAK[yy][xx]) {
			case 1:SDL_RenderCopy(renderer, soldado.irudiak[soldado.orientazioa], NULL, &laukiakk); break;
			case 2:SDL_RenderCopy(renderer, orco.irudiak[orco.orientazioa], NULL, &laukiakk); break;
			}
			switch (INFO_BALDOSAK[yy][xx]) {
			case 1:SDL_RenderCopy(renderer, cubo.irudiak[0], NULL, &laukiakk); break;
			}
		}
	}
	laukia(0, 0, 100, 100, &laukiakk);
	if ((infoPos.x >= 0 && infoPos.x <= TALE_X - 1) && (infoPos.y >= 0 && infoPos.y <= TALE_Y - 1)) {
		switch (TERRENO[infoPos.y][infoPos.x]) {
		case 1:SDL_RenderCopy(renderer, terreno.irudiak[0], NULL, &laukiakk); break;
		case 2:SDL_RenderCopy(renderer, terreno.irudiak[1], NULL, &laukiakk); break;
		case 3:SDL_RenderCopy(renderer, terreno.irudiak[2], NULL, &laukiakk); break;
		}
	}
	switch (PERTSONAK[infoPos.y][infoPos.x]) {
	case 1:SDL_RenderCopy(renderer, soldado.irudiak[soldado.orientazioa], NULL, &laukiakk); break;
	case 2:SDL_RenderCopy(renderer, orco.irudiak[orco.orientazioa], NULL, &laukiakk); break;
	}
}
void erakutsiTale(int xmouse, int ymouse) {
	cartesian(xmouse, ymouse);
	infoPos.x = ((cart.x - 50 - mapPos.x) / (TAMAÑOIMAGEN * 0.5));
	infoPos.y = ((cart.y + mapPos.y) / (TAMAÑOIMAGEN * 0.5));
	if ((infoPos.x >= 0 && infoPos.x <= TALE_X - 1) && (infoPos.y >= 0 && infoPos.y <= TALE_Y - 1)) {
		for (int yy = 0; yy <= TALE_Y - 1; yy++) {
			for (int xx = 0; xx <= TALE_X - 1; xx++)INFO_BALDOSAK[yy][xx] = 0;
		}
		INFO_BALDOSAK[infoPos.y][infoPos.x] = 1;
	}
	else {
		for (int yy = 0; yy <= TALE_Y - 1; yy++) {
			for (int xx = 0; xx <= TALE_X - 1; xx++)INFO_BALDOSAK[yy][xx] = 0;
		}
	}
}
void render() {
	SDL_RenderClear(renderer);
	erakutsiTale(mousePos.x, mousePos.y);
	Mapa();
	SDL_RenderPresent(renderer);

}
void iso(int x0, int y0) {
	isometric.x = x0 - y0;
	isometric.y = (x0 + y0) * 0.5;
}
void cartesian(int isoX, int isoY) {
	cart.x = ((2 * isoY + isoX) / 2);
	cart.y = ((2 * isoY - isoX) / 2);
}
void clean() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	
		SDL_Quit();
}
bool running() {
	return isRunning;
}
void update() {}