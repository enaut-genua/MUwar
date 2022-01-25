#include"jokoa.h"
#include"mapa.h"
bool Tropa_Mugitzeko_Aukera = false;
bool mugituX = false, mugituY = false, mugituGeneral = false;
bool XiritsiDa;
bool Basetik_sortu_tropa;
int TAMA�OIMAGEN = 100;
int rango = 2;
int Detektatutako_Tropa;
int Dif_destOrg_X_abs, Dif_destOrg_Y_abs;
int Dif_destOrg_X, Dif_destOrg_Y;
int orientazioaX, orientazioaY;

int hasierako_pos_x= NULL, hasierako_pos_y = NULL;
SDL_Rect laukiakk;

int ZenbatMugitu=0, tmp_x,tmp_y;
int � = -1;
bool Desplazamendua_erabaki = false;
int k = 0;
bool Tropa_Sortu = false;
int cc = 2;


//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
bool tropaAukeratuta = false;
bool zapalduta = false;
bool Lehenengo_pos_aukeratuta = false;
int desplazamendu_kopurua=0;
int infoPosx_tmp = NULL, infoPosy_tmp = NULL;// diferencial de posizioa egitejko aurreko pposizioa gordetxen du temporalmente
void TrayectoriaMarraztu() {
	if (SDL_BUTTON_LMASK != 0 && tropaAukeratuta) {
		if ((TERRENO[infoPos.y][infoPos.x] == 1 || TERRENO[infoPos.y][infoPos.x] == 4))//berrarra edo basamortua bada
		{
			zapalduta = true;
			if ((infoPosy_tmp != infoPos.y || infoPosx_tmp != infoPos.x) && (0 <= desplazamendu_kopurua && desplazamendu_kopurua <= TALE_Y) && (TRAYECTORIA[infoPos.y][infoPos.x] != 1)) {

				infoPosy_tmp = infoPos.y;
				infoPosx_tmp = infoPos.x;
				TRAYECTORIA[infoPos.y][infoPos.x] = 1;
				TRAYECTORIA_EN_ORDEN[desplazamendu_kopurua][0] = infoPos.y;
				TRAYECTORIA_EN_ORDEN[desplazamendu_kopurua][1] = infoPos.x;

				desplazamendu_kopurua++;
				
				//printf("\naa= %d", aa);
			}
			if ((infoPosy_tmp != infoPos.y || infoPosx_tmp != infoPos.x) && 0 <= desplazamendu_kopurua && desplazamendu_kopurua <= TALE_Y + 1 && TRAYECTORIA[infoPos.y][infoPos.x] == 1) {
				bool tmp = false;
				for (int i = 0; i < TALE_Y; i++)
				{
					if (tmp == false && TRAYECTORIA_EN_ORDEN[i][0] == infoPos.y && TRAYECTORIA_EN_ORDEN[i][1] == infoPos.x) {

						tmp = true;

						if (tmp == true) desplazamendu_kopurua = i;
					}
					if (tmp == true) {
						TRAYECTORIA[TRAYECTORIA_EN_ORDEN[i][0]][TRAYECTORIA_EN_ORDEN[i][1]] = 0;
						TRAYECTORIA_EN_ORDEN[i][1] = 0;
						TRAYECTORIA_EN_ORDEN[i][0] = 0;
					}
				}

			}
			//printf("\n  %d  %d", TRAYECTORIA_EN_ORDEN[0][1], TRAYECTORIA_EN_ORDEN[0][0]);
			if (!Lehenengo_pos_aukeratuta)
			{
				hasierako_pos_x = infoPos.x;
				hasierako_pos_y = infoPos.y;
				Lehenengo_pos_aukeratuta = true;
			}
		}

		if ((hasierako_pos_y == infoPos.y && hasierako_pos_x == infoPos.x) || (TERRENO[infoPos.y][infoPos.x] < 1))
		{
			for (int yy = 0; yy < TALE_Y; yy++) { //pa borrar trayectoria de mierda
				for (int xx = 0; xx < TALE_X; xx++) {
					TRAYECTORIA[yy][xx] = 0;
				}
			}
			TRAYECTORIA_EN_ORDEN[0][1] = hasierako_pos_x;
			TRAYECTORIA_EN_ORDEN[0][0] = hasierako_pos_y;
			desplazamendu_kopurua = 1;
			if ((TERRENO[infoPos.y][infoPos.x] < 1))
			{
				tropaAukeratuta = false;
				printf("\n TROPA MUGITZEKO AUKERA GALDU DA MAPATIK ATERA DELAKO, AUKERATU BERRIRO\n");
			}
		}

		//printf("\naa= %d   %d", aa, rango);

	}

}
//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

TTF_Font* font = 0;
void textuaIdatzi(int x, int y, char* str)
{
	SDL_Surface* textSurface;
	SDL_Texture* mTexture;
	SDL_Color textColor = { 0, 0, 0 };
	SDL_Rect src, dst;
	SDL_Renderer* gRenderer;

	if (font == 0) return;
	gRenderer = getRenderer();
	textSurface = TTF_RenderText_Solid(font, str, textColor);
	mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
	src.x = 0; dst.x = x;
	src.y = 0; dst.y = y;
	src.w = dst.w = textSurface->w;
	src.h = dst.h = textSurface->h;
	SDL_RenderCopy(gRenderer, mTexture, &src, &dst);
	SDL_FreeSurface(textSurface);
	SDL_DestroyTexture(mTexture);
}
void textuaGaitu(void) {
	font = TTF_OpenFontIndex("arial.ttf", 20, 0);
	if (!font)
	{
		printf("TTF_OpenFontIndex: %s\n", TTF_GetError());
		// handle error
	}
}
void textuaDesgaitu(void)
{
	if (font != 0) TTF_CloseFont(font);
	font = 0;
}
SDL_Renderer* getRenderer(void) { return renderer; }

void Tropa_Aukeratzeko_barra_sortu() {
	if (Tropa_Sortu)
	{
		for (int i = 0; i < 2; i++)
		{
			laukia(300+(i*100), 800 - 100, 100, 100, &laukiakk);
			SDL_RenderCopy(renderer, Barra_Urdina.irudia, NULL, &laukiakk);
			Barra_Urdina.laukia.x = 300;
			Barra_Urdina.laukia.y = 800 - 100;
			Barra_Urdina.laukia.w = 100;
			Barra_Urdina.laukia.h = 100;
		}
	}
}
int Barrako_tropa_aukeratu() {
	int value = 0;
	if (300 <mousePos.x && mousePos.x < 400)
	{
		if (800 - 100 < mousePos.y  && mousePos.y < 800) {
			value = 1; printf("SOLDADO %d\n",value);
		}
	}

	 else if (400 < mousePos.x && mousePos.x < 500)
	{
		if (800 - 100 < mousePos.y && mousePos.y < 800) {
			value = 2; printf("TANKE %d\n",value);
		}
	}

	return value;
}
void Desplazamendua(){
int orgx, orgy;
int difx, dify;

if (mugituGeneral)
{
	
	if (!Desplazamendua_erabaki && � + 2 < ZenbatMugitu)
	{
		Tropa_desplazamendua.x = 0;
		Tropa_desplazamendua.y = 0;
		�++;
		Zenbat_eta_nora_desplazatu_en_Baldosas(&orientazioaX, TRAYECTORIA_EN_ORDEN[�][1], TRAYECTORIA_EN_ORDEN[� + 1][1], &Dif_destOrg_X, &Dif_destOrg_X_abs);
		Zenbat_eta_nora_desplazatu_en_Baldosas(&orientazioaY, TRAYECTORIA_EN_ORDEN[�][0], TRAYECTORIA_EN_ORDEN[� + 1][0], &Dif_destOrg_Y, &Dif_destOrg_Y_abs);
		Desplazamendua_erabaki = true;
		printf("\n%d    %d    %d    %d\n", TRAYECTORIA_EN_ORDEN[�][1], TRAYECTORIA_EN_ORDEN[� + 1][1], TRAYECTORIA_EN_ORDEN[�][0], TRAYECTORIA_EN_ORDEN[� + 1][0]);
	}
	if ( � + 2 > ZenbatMugitu) {
		mugituX = false; mugituY = false; � = -1; printf("\n BUKATU DA\n"); Desplazamendua_erabaki = false; mugituGeneral = false;
	}
	if (mugituX&& Desplazamendua_erabaki) {

		iso((TAMA�OIMAGEN * 0.5) * (TRAYECTORIA_EN_ORDEN[�][1]) + mapPos.x, (TAMA�OIMAGEN * 0.5) * (TRAYECTORIA_EN_ORDEN[�][0]) - mapPos.y);
		orgx = isometric.x;
		orgy = isometric.y;
		difx = (TAMA�OIMAGEN * 0.5) * (Dif_destOrg_X * orientazioaX);
		dify = (TAMA�OIMAGEN * 0.5) * (Dif_destOrg_Y * orientazioaY);

		iso((TAMA�OIMAGEN * 0.5) * (TRAYECTORIA_EN_ORDEN[�][1]) + mapPos.x + Tropa_desplazamendua.x, (TAMA�OIMAGEN * 0.5) * (TRAYECTORIA_EN_ORDEN[�][0]) - mapPos.y);
		laukia(isometric.x, isometric.y, TAMA�OIMAGEN, TAMA�OIMAGEN, &laukiakk);
		SDL_RenderCopy(renderer, cubo.irudiak[1], NULL, &laukiakk);
		if ((isometric.x - orgx) * orientazioaX >= difx) {
			mugituY = true;
			//Desplazamendua_erabaki = false;
			mugituX = false;
		}
	}
	if (mugituY == true && mugituX == false)
	{
		iso((TAMA�OIMAGEN * 0.5) * (TRAYECTORIA_EN_ORDEN[�][1] + Dif_destOrg_X) + mapPos.x, (TAMA�OIMAGEN * 0.5) * (TRAYECTORIA_EN_ORDEN[�][0]) - mapPos.y);
		orgx = isometric.x;
		orgy = isometric.y;
		difx = (TAMA�OIMAGEN * 0.5) * (Dif_destOrg_X * orientazioaX);
		dify = ((TAMA�OIMAGEN * 0.5) * (Dif_destOrg_Y * orientazioaY) / 2);

		iso((TAMA�OIMAGEN * 0.5) * (TRAYECTORIA_EN_ORDEN[�][1] + Dif_destOrg_X) + mapPos.x, (TAMA�OIMAGEN * 0.5) * (TRAYECTORIA_EN_ORDEN[�][0]) - mapPos.y + Tropa_desplazamendua.y);
		laukia(isometric.x, isometric.y, TAMA�OIMAGEN, TAMA�OIMAGEN, &laukiakk);
		SDL_RenderCopy(renderer, cubo.irudiak[1], NULL, &laukiakk);
		if ((isometric.y - orgy) * orientazioaY >= dify) {
			mugituY = false; mugituX = true; Desplazamendua_erabaki = false; printf("\n PRUEBA  %d\n", �);
		}


	}
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
			if (event.wheel.y > 0 && TAMA�OIMAGEN < 500)TAMA�OIMAGEN += 5;
			else if (event.wheel.y < 0 && TAMA�OIMAGEN>70)TAMA�OIMAGEN -= 5;
		}
		switch (event.button.type)
		{

			case SDL_MOUSEBUTTONDOWN:
			if (Basetik_sortu_tropa == true)
			{
				
				cc = Barrako_tropa_aukeratu();
				PERTSONAK[tropa_org.y][tropa_org.x] = cc;
				Basetik_sortu_tropa = false;
				
				Tropa_Sortu = false;
			}
			if (Tropa_Mugitzeko_Aukera) {
			//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||1|||11
				if (!tropaAukeratuta) {
					Detektatutako_Tropa = Tropa_Org_Aukeratu(&tropa_org.x, &tropa_org.y, &infoPos.x, &infoPos.y);			
					if (Detektatutako_Tropa > EZER)
					{
						Tropa_desplazamendua.x = 0;
						Tropa_desplazamendua.y = 0;
						printf("\nTROPA AUKERATU DA\n");
						tropaAukeratuta = true;
						Rangoa(rango, EZABATU, &tropa_org.x, &tropa_org.y);
						Rangoa(rango, MARRAZTU, &tropa_org.x, &tropa_org.y);
						mugituY = false;
						mugituX = false;
						mugituGeneral = false;
						� = -1;
					}
				}
				if (TERRENO[infoPos.y][infoPos.x] == basea && !tropaAukeratuta)
				{
					if (!Tropa_Sortu)Tropa_Sortu = true;
					Basetik_sortu_tropa = true;
				}
			}
			
			break;

			case SDL_MOUSEBUTTONUP:

			if (tropaAukeratuta) {
				if (TERRENO[infoPos.y][infoPos.x] <= 1 && RANGO_JOKALARIARENA[infoPos.y][infoPos.x] == 1 && TRAYECTORIA[infoPos.y][infoPos.x] == 1)
					Tropa_Dest_Aukeratu(infoPos.x, infoPos.y, tropa_org.x, tropa_org.y, 1, Detektatutako_Tropa);
				Rangoa(rango, EZABATU, &tropa_org.x, &tropa_org.y);
				tropaAukeratuta = false;
				mugituX = true;
				mugituGeneral = true;
				if (TERRENO[infoPos.y][infoPos.x] > 1) { mugituX = false; mugituGeneral = true; }
			}
			//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

			for (int yy = 0; yy < TALE_Y; yy++) { //pa borrar trayectoria de mierda
				for (int xx = 0; xx < TALE_X; xx++) {
					TRAYECTORIA[yy][xx] = 0;
				}
			}
			ZenbatMugitu = desplazamendu_kopurua;
			desplazamendu_kopurua = 0;
			Lehenengo_pos_aukeratuta = false;
			infoPosy_tmp = 0; infoPosx_tmp = 0;
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
			case SDLK_w:mapPos.x += (int)(TAMA�OIMAGEN * 0.5); mapPos.y -= (int)(TAMA�OIMAGEN * 0.5); break;
			case SDLK_s:mapPos.x -= (int)(TAMA�OIMAGEN * 0.5); mapPos.y += (int)(TAMA�OIMAGEN * 0.5); break;
			case SDLK_d:mapPos.x -= (int)(TAMA�OIMAGEN * 0.5); mapPos.y -= (int)(TAMA�OIMAGEN * 0.5); break;
			case SDLK_a:mapPos.x += (int)(TAMA�OIMAGEN * 0.5); mapPos.y += (int)(TAMA�OIMAGEN * 0.5); break;
			case SDLK_1:
				if (Basetik_sortu_tropa == true) PERTSONAK[tropa_org.y][tropa_org.x] = Barrako_tropa_aukeratu();
				Basetik_sortu_tropa = false; 
				break;
			case SDLK_2: if (Basetik_sortu_tropa == true) PERTSONAK[tropa_org.y][tropa_org.x] = Barrako_tropa_aukeratu(); Basetik_sortu_tropa = false; break;
			case SDLK_q: mugituX = false; mugituY = false;�=-1; break;
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
	TTF_Init();
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
			iso((TAMA�OIMAGEN * 0.5) * xx + mapPos.x, (TAMA�OIMAGEN * 0.5) * yy - mapPos.y);

			laukia(isometric.x, isometric.y, TAMA�OIMAGEN, TAMA�OIMAGEN, &laukiakk);

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
	infoPos.x = ((cart.x - 50 - mapPos.x) / (TAMA�OIMAGEN * 0.5));
	infoPos.y = ((cart.y + mapPos.y) / (TAMA�OIMAGEN * 0.5));
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
	Desplazamendua();
	TrayectoriaMarraztu();
	Textuak_idatzi();
	Tropa_Aukeratzeko_barra_sortu();
	
	SDL_RenderPresent(renderer);
}
void Textuak_idatzi() {
	textuaIdatzi(350, 20, "Jokalaria: ");
	if (PERTSONAK[infoPos.y][infoPos.x] > 0) {
		textuaIdatzi(10, 100, "Tropa ID: ");
		textuaIdatzi(10, 130, "bizitza: ");
		textuaIdatzi(10, 160, "atakea: ");
		textuaIdatzi(10, 190, "rangoa: ");
	 }


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

