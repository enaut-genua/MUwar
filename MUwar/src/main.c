#include"jokoa.h"
int main(int argc, char* argv[])
{
	char* link[20][20] = {
							{"res/img/GRASS.png","res/img/WATER.png","res/MUwartextures/1superficies/montana.png","res/aa.png"},
							{"res/MUwartextures/heavysoldierazul/SOL_AZUL_esk1.png","res/MUwartextures/heavysoldierazul/SOL_AZUL_esk1.png","res/MUwartextures/heavysoldierazul/SOL_AZUL_esk1.png","res/MUwartextures/heavysoldierazul/SOL_AZUL_esk1.png"},
							{"res/MUwartextures/tanqueazul/tanqueazulderecha1.png","res/MUwartextures/tanqueazul/tanqueazulderecha1.png","res/MUwartextures/tanqueazul/tanqueazulderecha1.png","res/MUwartextures/tanqueazul/tanqueazulderecha1.png"},
							{"res/img/ISOTILE_NEO.png","res/img/ISOTILE1.png","res/img/RANGO.png","res/cc.png"}
	};
	mapPos.x = 400;
	mapPos.y = 900;
	persona.x = 0;
	persona.y = 0;
	soldado.orientazioa = 0;
	orco.orientazioa = 0;
	printf("\n SAKATU P TROPAK SORTU EDO MUGITZEKO\n");
	init("tutorial", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, false);

	//______________________________________________TTF_____________________________________________________________________//
	textuaGaitu();
	textuaIdatzi(10, 20, "Hola");
	//______________________________________________TTF_____________________________________________________________________//

	irudiakKargatu(terreno.irudiak, link[0]);
	irudiakKargatu(soldado.irudiak, link[1]);
	irudiakKargatu(orco.irudiak, link[2]);
	irudiakKargatu(cubo.irudiak, link[3]);
	while (isRunning)
	{
		handleEvents();		
		update();
		render();
	}
	clean();
	return 0;
}
void irudiakKargatu(SDL_Texture* gotorlekua[], char** link) {
	for (int i = 0; i < 4; i++)gotorlekua[i] = loadImage(link[i], renderer);
}
