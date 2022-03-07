#ifndef OBJET_SDL_H
#define OBJET_SDL_H

#include <iostream>

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

class ObjetSDL {
public:
    ObjetSDL();
    ~ObjetSDL();

    float x, y; //coin de l'image
    float h, w; //taille de l'image

    SDL_Texture * texture;

    void chargerTexture(SDL_Renderer * renderer, const char* filename);

    void afficher(SDL_Renderer * renderer);
    void afficher(SDL_Renderer * renderer, float posX, float posY, float taille);

    void afficherCentre(float decalageX, float decalageY, int largeurFenetre, int hauteurFenetre, SDL_Renderer * renderer);

private:
    
};

#endif