#ifndef MENUA_H
#define MENUA_H

#include "include.h"

SDL_Texture* initialize_texture_from_file(const char* file_name, SDL_Renderer* renderer);
int Botoiak(int step, SDL_Rect exit, SDL_Rect controls, SDL_Rect play);
void mousePos();
void nextStep(int step, SDL_Texture* menuaImage, SDL_Texture* exitImage, SDL_Texture* playImage, SDL_Texture* controlsImage, SDL_Renderer* renderer);
void hover1(SDL_Rect pantailaOsoa, SDL_Rect exit, SDL_Rect controls, SDL_Rect play, SDL_Renderer* renderer, SDL_Texture* menuaImage, SDL_Texture* exitImage, SDL_Texture* playImage, SDL_Texture* controlsImage);
void hartu_running(bool* interruptorea);
void controlspantaila(SDL_Renderer* renderer, SDL_Window* window);
void Botoiak3(SDL_Renderer* renderer, SDL_Rect hasieraraBuelta, SDL_Texture* kontrols);
void menuFinala(SDL_Renderer* renderer, int paow, int poh, SDL_Window* window);
void menu(SDL_Window* window, SDL_Renderer* renderer, int paow, int poh, int step);
void Botoiak2(SDL_Renderer* renderer, SDL_Rect hasieraraBuelta, SDL_Texture* redVictory, SDL_Texture* blueVictory, SDL_Texture* btv2, SDL_Texture* rtv2);
void hover2(SDL_Renderer* renderer, SDL_Rect hasieraraBuelta, SDL_Rect pantailaOsoa, SDL_Texture* redVictory, SDL_Texture* blueVictory, SDL_Texture* btv2, SDL_Texture* rtv2);

bool lortu_jokoa_hasi(void);



#endif // !MENUA_H
