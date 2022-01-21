#pragma once
#define SDL_MAIN_HANDLED
#include "SDL2/SDL.h"
#include <stdbool.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>


Uint32 buttons;
static int width = 500;
static int heigth = 500;
int mousex, mousey;
int exitw, exith, controlsw, controlsh, playw, playh;
SDL_Texture* initialize_texture_from_file(const char* file_name, SDL_Renderer* renderer);
int Botoiak(int step, SDL_Rect exit, SDL_Rect controls, SDL_Rect play);
void mousePos();
void nextStep(int step,SDL_Texture* menuaImage, SDL_Texture* exitImage, SDL_Texture* playImage, SDL_Texture* controlsImage, SDL_Renderer* renderer);
void hover1(SDL_Rect pantailaOsoa, SDL_Rect exit, SDL_Rect controls, SDL_Rect play, SDL_Renderer* renderer, SDL_Texture* menuaImage, SDL_Texture* exitImage, SDL_Texture* playImage, SDL_Texture* controlsImage);
void sortuIrudiak(SDL_Renderer* renderer);
void hartu_running(bool* interruptorea);
void menuFinala(SDL_Renderer* renderer, int paow, int poh);
void menu(SDL_Window* window, SDL_Renderer* renderer,int paow, int poh, int step);
void Botoiak2(SDL_Renderer* renderer, SDL_Rect hasieraraBuelta, SDL_Texture* redVictory, SDL_Texture* blueVictory, SDL_Texture* btv2, SDL_Texture* rtv2);
void hover2(SDL_Renderer* renderer, SDL_Rect hasieraraBuelta, SDL_Rect pantailaOsoa, SDL_Texture* redVictory, SDL_Texture* blueVictory, SDL_Texture* btv2, SDL_Texture* rtv2);