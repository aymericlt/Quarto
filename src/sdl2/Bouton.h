#ifndef BOUTON_H
#define BOUTON_H

#include <iostream>
#include "ObjetSDL.h"


#ifdef _WIN32
#include <SDL.h>
#include <SDL_ttf.h>  
#include <SDL_image.h>
#elif __linux__
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#endif

class Bouton {
public:
    Bouton();
    //Bouton(float x, float y, float w, float h, SDL_Renderer * renderer = nullptr, const char* filename0 = "", const char* filename1 = "");
    ~Bouton();

    ObjetSDL etatsBouton[2]; //0 normal, 1 presse
    int idBouton;


    void setX(float x);
    void setY(float y);

    void setWidth(float w);
    void setHeight(float h);

    void chargerTexture(SDL_Renderer * renderer, const char* filename0, const char* filename1);

    void afficher(SDL_Renderer * renderer, float mouseX = -1, float mouseY = -1);
    void afficher(SDL_Renderer * renderer, float mouseX, float mouseY, float posX, float posY, float taille = 100); //taille en pourcentage de l'originale (100 = rien à faire) 

    void actualiserSelection(float mouseX, float mouseY, int& selection); //Affecte id à selection si la souris est le bouton;
    void actualiserSelection(float mouseX, float mouseY, int& selection, float posX, float posY, float taille = 100);

    bool isIn(float mouseX, float mouseY);
    bool isIn(float mouseX, float mouseY, float posX, float posY, float taille = 100);

    void setSurface(SDL_Surface * surf);

private:

};

#endif