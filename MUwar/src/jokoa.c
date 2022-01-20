#include"jokoa.h"
#include"mapa.h"
bool tropaAukeratuta = false;
bool Tropa_Mugitzeko_Aukera = false;
bool mugituX = false, mugituY = false;
bool XiritsiDa;
bool Basetik_sortu_tropa;
int TAMAÑOIMAGEN = 100;
int rango = 5;
int Detektatutako_Tropa;
int Dif_destOrg_X_abs, Dif_destOrg_Y_abs;
int Dif_destOrg_X, Dif_destOrg_Y;
int orientazioaX, orientazioaY;
int infoPosx_tmp=NULL, infoPosy_tmp=NULL;
SDL_Rect laukiakk;
bool zapalduta = false,OSTIA=false, tmp = false;
int aa=0,tmp_x,tmp_y;

void Dinamic_Move(int Tale_OrgX, int Tale_OrgY,int dinamicX, int dinamicY,int difdestorgx,int difdestorgy) {
	int orgx, orgy;
	int difx, dify;
	if (mugituX ==true)
	{
		iso((TAMAÑOIMAGEN * 0.5) * (Tale_OrgX)+mapPos.x, (TAMAÑOIMAGEN * 0.5) * (Tale_OrgY)-mapPos.y);
		orgx = isometric.x;
		orgy = isometric.y;
		difx = (TAMAÑOIMAGEN * 0.5) * (difdestorgx * orientazioaX);
		dify = (TAMAÑOIMAGEN * 0.5) * (difdestorgy * orientazioaY);

		iso((TAMAÑOIMAGEN * 0.5) * (Tale_OrgX)+mapPos.x + dinamicX, (TAMAÑOIMAGEN * 0.5) * (Tale_OrgY)-mapPos.y);
		laukia(isometric.x, isometric.y, TAMAÑOIMAGEN, TAMAÑOIMAGEN, &laukiakk);
		SDL_RenderCopy(renderer, cubo.irudiak[1], NULL, &laukiakk);
		printf("\ndifX=%d\n", difx);
		if ((isometric.x - orgx) * orientazioaX >= difx) {
			mugituX = false; 
			mugituY = true;	
		}
	}

	if (mugituY == true&& mugituX == false)
	{
		iso((TAMAÑOIMAGEN * 0.5) * (Tale_OrgX+ difdestorgx)+mapPos.x, (TAMAÑOIMAGEN * 0.5) * (Tale_OrgY)-mapPos.y);
		orgx = isometric.x;
		orgy = isometric.y;
		difx = (TAMAÑOIMAGEN * 0.5) * (difdestorgx * orientazioaX);
		dify = ((TAMAÑOIMAGEN * 0.5) * (difdestorgy * orientazioaY)/2);

		iso((TAMAÑOIMAGEN * 0.5) * (Tale_OrgX + difdestorgx)+mapPos.x , (TAMAÑOIMAGEN * 0.5) * (Tale_OrgY)-mapPos.y + dinamicY);
		laukia(isometric.x, isometric.y, TAMAÑOIMAGEN, TAMAÑOIMAGEN, &laukiakk);
		SDL_RenderCopy(renderer, cubo.irudiak[1], NULL, &laukiakk);
		printf("\nisometric.y =%d\n", isometric.y);
		if ((isometric.y - orgy) * orientazioaY >= dify)mugituY = false;
	}
		
}
void Zenbat_eta_nora_desplazatu_en_Baldosas(int *orientazioa,int org,int dest,int *dif,int* difAbs) {
	*dif = dest - org;
	if (dest - org > 0)*orientazioa = 1;
	else if (dest - org < 0)*orientazioa = -1;
	else if (dest - org == 0)*orientazioa = 0;
	*difAbs = *dif * *orientazioa;
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
		case SDL_MOUSEBUTTONUP: 
			
			for (int yy = 0; yy < TALE_Y; yy++) { //pa borrar trayectoria de mierda
				for (int xx = 0; xx < TALE_X; xx++) {
					TRAYECTORIA[yy][xx] = 0;
				}
			}
			aa = 0;
			OSTIA = false;
			if (tropaAukeratuta) {
				if (TERRENO[infoPos.y][infoPos.x] <= 1 && RANGO_JOKALARIARENA[infoPos.y][infoPos.x] == 1)
					Tropa_Dest_Aukeratu(infoPos.x, infoPos.y, tropa_org.x, tropa_org.y, 1, Detektatutako_Tropa);
				Rangoa(rango, EZABATU, &tropa_org.x, &tropa_org.y);
				tropaAukeratuta = false;
				mugituX = true;
				Zenbat_eta_nora_desplazatu_en_Baldosas(&orientazioaX, tropa_org.x, infoPos.x, &Dif_destOrg_X, &Dif_destOrg_X_abs);
				Zenbat_eta_nora_desplazatu_en_Baldosas(&orientazioaY, tropa_org.y, infoPos.y, &Dif_destOrg_Y, &Dif_destOrg_Y_abs);
				if (TERRENO[infoPos.y][infoPos.x] > 1)mugituX = false;
			}
			break;
		case SDL_MOUSEBUTTONDOWN:

			if (Tropa_Mugitzeko_Aukera) {
				if (!tropaAukeratuta) {
					Detektatutako_Tropa = Tropa_Org_Aukeratu(&tropa_org.x, &tropa_org.y, &infoPos.x, &infoPos.y);
					if (Detektatutako_Tropa > EZER)
					{
						Tropa_desplazamendua.x = 0;
						Tropa_desplazamendua.y = 0;
						printf("\nTROPA AUKERATU DA\n");
						tropaAukeratuta = true;
						Rangoa(rango, EZABATU,&tropa_org.x,&tropa_org.y);
						Rangoa(rango,MARRAZTU,&tropa_org.x,&tropa_org.y);
						mugituY = false;
						mugituX = false;
					}
				}
					
			}
			if (TERRENO[infoPos.y][infoPos.x] == basea && !tropaAukeratuta)
			{
				printf("AUKERATU TROPA BAT:\n 1=soldado\n 2=tanke\n");
				Basetik_sortu_tropa = true;
				tropa_org.x = infoPos.x;
				tropa_org.y = infoPos.y;
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
				printf("\nMUGITU DAITEKE TROPA BAT\n");
				Tropa_Mugitzeko_Aukera = true;  break;
			case SDLK_o:
				Tropa_Mugitzeko_Aukera = false; printf("\nEZIN DA MUGITU TROPA\n");  break;
			case SDLK_w:mapPos.x += (int)(TAMAÑOIMAGEN * 0.5); mapPos.y -= (int)(TAMAÑOIMAGEN * 0.5); break;
			case SDLK_s:mapPos.x -= (int)(TAMAÑOIMAGEN * 0.5); mapPos.y += (int)(TAMAÑOIMAGEN * 0.5); break;
			case SDLK_d:mapPos.x -= (int)(TAMAÑOIMAGEN * 0.5); mapPos.y -= (int)(TAMAÑOIMAGEN * 0.5); break;
			case SDLK_a:mapPos.x += (int)(TAMAÑOIMAGEN * 0.5); mapPos.y += (int)(TAMAÑOIMAGEN * 0.5); break;
			case SDLK_1: if (Basetik_sortu_tropa == true) PERTSONAK[tropa_org.y][tropa_org.x] = 1; Basetik_sortu_tropa = false; break;
			case SDLK_2: if (Basetik_sortu_tropa == true) PERTSONAK[tropa_org.y][tropa_org.x] = 2; Basetik_sortu_tropa = false; break;
			case SDLK_q: mugituX = false; mugituY = false; break;
			case SDLK_x: mugituX = true; break;
			case SDLK_y: mugituY = true; break;
				break;
			}
		}
	}
}
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
int Tropa_Org_Aukeratu(int* Xorg, int* Yorg,int* XCuboInfo, int* YCuboInfo) { 
	//funtzio honek tropa baten ubikazioa esatean ze tropa aukeratu den esaten du eta bere posizioa gordetzen du
	
	*Xorg = *XCuboInfo; 
	*Yorg = *YCuboInfo;
	return (PERTSONAK[*YCuboInfo][*XCuboInfo]);
}
void Tropa_Dest_Aukeratu(int  TropaDestX,int TropaDestY, int tropaOrgX, int TropaOrgY, int TerrenoDondePuedeAndar,int IpiniNahiDenTropa) {
	//funtzio honek Tropa_Org_Aukeratu funtzioak detektatu duen tropa ipintzen du ubikazio batean 
	
	PERTSONAK[TropaOrgY][tropaOrgX] = 0;
		PERTSONAK[TropaDestY][TropaDestX] = IpiniNahiDenTropa;
}
void Rangoa(int rango,int borratu_edo_marraztu, int* XCuboInfo, int* YCuboInfo) {
	for (int y = 0; y < (rango * 2) + 1; y++)
	{
		for (int x = 0; x < (rango * 2) + 1; x++)
		{
			if (TERRENO[*YCuboInfo + y - rango][*XCuboInfo + x - rango] <= 1 && *YCuboInfo + y - rango >= 0 && *XCuboInfo + x - rango >= 0 && *YCuboInfo + y - rango < TALE_Y && *XCuboInfo + x - rango < TALE_X)
				RANGO_JOKALARIARENA[*YCuboInfo + y - rango][*XCuboInfo + x - rango] = borratu_edo_marraztu;
		}
	}
}
void MousePos(void) {
	int buttons;
	
	SDL_PumpEvents();  // make sure we have the latest mouse state.
	buttons = SDL_GetMouseState(&mousePos.x, &mousePos.y);
	//SDL_Log("Mouse cursor is at %d, %d", mousePos.x, mousePos.y);
	if ((buttons & SDL_BUTTON_LMASK) != 0) {
		zapalduta = true;
		
		if (OSTIA==false) {
			infoPosy_tmp = infoPos.y;
			infoPosx_tmp = infoPos.x;
			OSTIA = true;
			
		}
		

		if ( (infoPosy_tmp != infoPos.y || infoPosx_tmp != infoPos.x) && (0 <= aa &&aa<rango ) && (TRAYECTORIA[infoPos.y][infoPos.x]!=1)  ) {
			
			infoPosy_tmp = infoPos.y;
			infoPosx_tmp = infoPos.x;
			TRAYECTORIA[infoPos.y][infoPos.x] = 1;
			TRAYECTORIA_EN_ORDEN[aa][0] = infoPos.y;
			TRAYECTORIA_EN_ORDEN[aa][1] = infoPos.x;
			aa++;
			tmp = false;
			printf("\naa= %d", aa);
		}

		
		if ((infoPosy_tmp != infoPos.y || infoPosx_tmp != infoPos.x) && 0 < aa && aa <= rango && TRAYECTORIA[infoPos.y][infoPos.x] == 1) {
			
			for (int i = 0; i < TALE_Y; i++)
			{
				if (tmp==false&&TRAYECTORIA_EN_ORDEN[i][0] == infoPos.y && TRAYECTORIA_EN_ORDEN[i][1] == infoPos.x) {
					
					tmp = true;
				
					if (tmp == true) aa = i;	
				}
				if (tmp == true) {
					TRAYECTORIA[TRAYECTORIA_EN_ORDEN[i][0]][TRAYECTORIA_EN_ORDEN[i][1]] = 0;
					TRAYECTORIA_EN_ORDEN[i][1] = 0;
					TRAYECTORIA_EN_ORDEN[i][0] = 0;
				}
			}
			printf("\naa= %d", aa);
		}
		
		
	}
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
	
	for (int yy = 0; yy < TALE_Y; yy++) {
		for (int xx = 0; xx < TALE_X; xx++) {
			iso((TAMAÑOIMAGEN * 0.5) * xx + mapPos.x, (TAMAÑOIMAGEN * 0.5) * yy - mapPos.y);

			laukia(isometric.x, isometric.y, TAMAÑOIMAGEN, TAMAÑOIMAGEN, &laukiakk);

			switch (TERRENO[yy][xx]) {
			case 1:SDL_RenderCopy(renderer, terreno.irudiak[belarzaria], NULL, &laukiakk); break;
			case 2:SDL_RenderCopy(renderer, terreno.irudiak[ura], NULL, &laukiakk); break;
			case 3:SDL_RenderCopy(renderer, terreno.irudiak[mendia], NULL, &laukiakk); break;
			case 4:SDL_RenderCopy(renderer, terreno.irudiak[3], NULL, &laukiakk); break;
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
			switch (TRAYECTORIA[yy][xx]) {
			case 1:SDL_RenderCopy(renderer, cubo.irudiak[3], NULL, &laukiakk); break;
			
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
	Dinamic_Move(tropa_org.x, tropa_org.y, Tropa_desplazamendua.x, Tropa_desplazamendua.y, Dif_destOrg_X, Dif_destOrg_Y);
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
void update() {
	if (mugituX == true)Tropa_desplazamendua.x += orientazioaX*3;
	if (mugituY == true)Tropa_desplazamendua.y += orientazioaY*3;
}

