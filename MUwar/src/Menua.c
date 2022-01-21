#include "Utils.h"

int exitw = 114, exith = 55, controlsw = 232, controlsh = 53, playw = 136, playh = 56, hbh = 54, hbw = 150;
Uint32 buttons;
int mousex, mousey;
bool* running = NULL;
bool  menua = true, bukaeraMenua = true, irabazi = true;


void mousePos()
{
	SDL_PumpEvents();

	buttons = SDL_GetMouseState(&mousex, &mousey);

	printf("%d, %d \n", mousex, mousey);

}

void hartu_running(bool* interruptorea)
{
	running = interruptorea;
}


int Botoiak(int step, SDL_Rect exit, SDL_Rect controls, SDL_Rect play)
{
	mousePos();

	if ((mousex < (exit.x + exit.w) && mousex > exit.x && mousey < (exit.y + exit.h) && mousey > exit.y) && (buttons & SDL_BUTTON_LMASK) != 0)
	{
		step = 1;
	}
	if ((mousex < (play.x + play.w) && mousex > play.x && mousey < (play.y + play.h) && mousey > play.y) && (buttons & SDL_BUTTON_LMASK) != 0)
	{
		step = 2;
	}
	if ((mousex < (controls.x + controls.w) && mousex > controls.x && mousey < (controls.y + controls.h) && mousey > controls.y) && (buttons & SDL_BUTTON_LMASK) != 0)
	{
		step = 3;
	}

	return step;
}

void hover1(SDL_Rect pantailaOsoa, SDL_Rect exit, SDL_Rect controls, SDL_Rect play, SDL_Renderer* renderer, SDL_Texture* menuaImage, SDL_Texture* exitImage, SDL_Texture* playImage, SDL_Texture* controlsImage)
{
	mousePos();

	if (mousex < (exit.x + exit.w) && mousex > exit.x && mousey < (exit.y + exit.h) && mousey > exit.y)
	{
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, exitImage, NULL, &pantailaOsoa);
	}
	else if (mousex < (controls.x + controls.w) && mousex > controls.x && mousey < (controls.y + controls.h) && mousey > controls.y)
	{
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, controlsImage, NULL, &pantailaOsoa);
	}
	else if ((mousex < (play.x + play.w) && mousex > play.x && mousey < (play.y + play.h) && mousey > play.y))
	{
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, playImage, NULL, &pantailaOsoa);
	}
	else
	{
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, menuaImage, NULL, &pantailaOsoa);
	}
}

void nextStep(int step, SDL_Texture* menuaImage, SDL_Texture* exitImage, SDL_Texture* playImage, SDL_Texture* controlsImage, SDL_Renderer* renderer)
{
	if (step == 1)
	{
		menua = false;
		*running = false;

	}
	if (step == 2)
	{
		SDL_DestroyTexture(exitImage);
		SDL_DestroyTexture(playImage);
		SDL_DestroyTexture(controlsImage);
		SDL_DestroyTexture(menuaImage);
		SDL_RenderClear(renderer);
		menua = false;
		bukaeraMenua = true;
		irabazi = true;
	}
	if (step == 3)
	{
		SDL_DestroyTexture(exitImage);
		SDL_DestroyTexture(playImage);
		SDL_DestroyTexture(controlsImage);
		SDL_DestroyTexture(menuaImage);
		SDL_RenderClear(renderer);
		menua = false;
		irabazi = false;
		bukaeraMenua = true;

	}
}

SDL_Texture* initialize_texture_from_file(const char* file_name, SDL_Renderer* renderer)
{
	SDL_Surface* image = IMG_Load(file_name);
	SDL_Texture* image_texture = SDL_CreateTextureFromSurface(renderer, image);
	SDL_FreeSurface(image);
	return image_texture;
}

void menu(SDL_Window* window, SDL_Renderer* renderer, int paow, int poh, int step)
{
	SDL_Texture* menuaImage = initialize_texture_from_file("1.png", renderer);
	SDL_Texture* exitImage = initialize_texture_from_file("4.png", renderer);
	SDL_Texture* playImage = initialize_texture_from_file("2.png", renderer);
	SDL_Texture* controlsImage = initialize_texture_from_file("3.png", renderer);

	while (menua)
	{
		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);
		SDL_GetWindowSize(window, &width, &heigth);
		SDL_RenderClear(renderer);
		SDL_Rect pantailaOsoa = { (int)(width / 2 - paow / 2),(int)(heigth / 2 - poh / 2), paow, poh };
		SDL_Rect exit = { (int)(width / 2 - exitw / 2), (int)(poh * 0.812 + (heigth - poh) / 2), exitw, exith };  //Orriaren tamainare erdia - argazkiaren tamainaren erdia posizioa kuadratzeko
		SDL_Rect controls = { (int)(width / 2 - controlsw / 2), (int)(poh * 0.684 + (heigth - poh) / 2), controlsw, controlsh };
		SDL_Rect play = {(int)(width / 2 - playw / 2), (int)(poh * 0.544 + (heigth - poh) / 2), playw, playh };

		SDL_RenderCopy(renderer, menuaImage, NULL, &pantailaOsoa);


		hover1(pantailaOsoa, exit, controls, play, renderer, menuaImage, exitImage, playImage, controlsImage);
		step = Botoiak(step, exit, controls, play);
		nextStep(step, menuaImage, exitImage, playImage, controlsImage, renderer);
		SDL_RenderPresent(renderer);
	}

}

void menuFinala(SDL_Renderer* renderer, int paow, int poh)
{

	SDL_Texture* blueVictory = initialize_texture_from_file("BlueTeamVictory.png", renderer);
	SDL_Texture* redVictory = initialize_texture_from_file("RedTeamVictory.png", renderer);
	SDL_Texture* btv2 = initialize_texture_from_file("btv2.png", renderer);
	SDL_Texture* rtv2 = initialize_texture_from_file("rtv2.png", renderer);

	while (bukaeraMenua && running)
	{
		SDL_RenderClear(renderer);
		SDL_Rect pantailaOsoa = { width / 2 - paow / 2, heigth / 2 - poh / 2, paow, poh };
		if (irabazi)
		{
			SDL_SetRenderDrawColor(renderer, 0xFF, 0x16, 0x16, SDL_ALPHA_OPAQUE);
			SDL_RenderCopy(renderer, redVictory, NULL, &pantailaOsoa);
		}
		if (irabazi == false)
		{
			SDL_SetRenderDrawColor(renderer, 0x00, 0x4A, 0xAD, SDL_ALPHA_OPAQUE);
			SDL_RenderCopy(renderer, blueVictory, NULL, &pantailaOsoa);
		}
		SDL_Rect hasieraraBuelta = { (int)(width / 2 - hbw / 2),(int)(poh * 0.816 + (heigth - poh)/ 2), hbw, hbh };

		hover2(renderer, hasieraraBuelta, pantailaOsoa, redVictory, blueVictory, btv2, rtv2);
		Botoiak2(renderer, hasieraraBuelta, redVictory, blueVictory, btv2, rtv2);
		SDL_RenderPresent(renderer);
	}
}
void hover2(SDL_Renderer* renderer, SDL_Rect hasieraraBuelta, SDL_Rect pantailaOsoa, SDL_Texture* redVictory, SDL_Texture* blueVictory, SDL_Texture* btv2, SDL_Texture* rtv2)
{
	mousePos();
	if (irabazi)
	{
		if (mousex < (hasieraraBuelta.x + hasieraraBuelta.w) && mousex > hasieraraBuelta.x && mousey < (hasieraraBuelta.y + hasieraraBuelta.h) && mousey > hasieraraBuelta.y)
		{
			SDL_RenderClear(renderer);
			SDL_RenderCopy(renderer, rtv2, NULL, &pantailaOsoa);
		}
		else
		{
			SDL_RenderClear(renderer);
			SDL_RenderCopy(renderer, redVictory, NULL, &pantailaOsoa);
		}
	}
	if (irabazi == false)
	{
		if (mousex < (hasieraraBuelta.x + hasieraraBuelta.w) && mousex > hasieraraBuelta.x && mousey < (hasieraraBuelta.y + hasieraraBuelta.h) && mousey > hasieraraBuelta.y)
		{
			SDL_RenderClear(renderer);
			SDL_RenderCopy(renderer, btv2, NULL, &pantailaOsoa);
		}
		else
		{
			SDL_RenderClear(renderer);
			SDL_RenderCopy(renderer, blueVictory, NULL, &pantailaOsoa);
		}
	}
}
void Botoiak2(SDL_Renderer* renderer, SDL_Rect hasieraraBuelta, SDL_Texture* redVictory, SDL_Texture* blueVictory, SDL_Texture* btv2, SDL_Texture* rtv2)
{
	mousePos();
	if ((mousex < (hasieraraBuelta.x + hasieraraBuelta.w) && mousex > hasieraraBuelta.x && mousey < (hasieraraBuelta.y + hasieraraBuelta.h) && mousey > hasieraraBuelta.y) && (buttons & SDL_BUTTON_LMASK) != 0)
	{
		bukaeraMenua = false;
		menua = true;
		*running = true;
		SDL_DestroyTexture(btv2);
		SDL_DestroyTexture(rtv2);
		SDL_DestroyTexture(blueVictory);
		SDL_DestroyTexture(redVictory);
		SDL_RenderClear(renderer);
	}
}
