#include "ObjetSDL.h"

ObjetSDL::ObjetSDL() {
    texture = nullptr;
    x = 0;
    y = 0;
    w = 100; //Si rien n'est fait l'image est affichée en 100x100
    h = 100;
}

ObjetSDL::~ObjetSDL() {
    texture = nullptr;
}

void ObjetSDL::chargerTexture(SDL_Renderer * renderer, const char* filename) {
    texture = IMG_LoadTexture(renderer, filename);
    
    if (texture == nullptr) {
		std::cout << "Failed to load texture. Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        exit(1);
    }
}

void ObjetSDL::afficher(SDL_Renderer * renderer) {
    int ok;

    SDL_Rect r;
    r.x = x;
    r.y = y;
    r.w = w;
    r.h = h;

    ok = SDL_RenderCopy(renderer, texture, nullptr, &r);
    if (ok != 0) {
        std::cout << "Failed to print texture. Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        exit(1);
    }
}

void ObjetSDL::afficherCentre(float decalageX, float decalageY, int largeurFenetre, int hauteurFenetre, SDL_Renderer * renderer) {
    int ok;

    SDL_Rect r;
    r.x = largeurFenetre/2 - w/2 + decalageX;
    r.y = hauteurFenetre/2 - h/2 + decalageY;
    r.w = w;
    r.h = h;

    ok = SDL_RenderCopy(renderer, texture, nullptr, &r);
    if (ok != 0) {
        std::cout << "Failed to print texture. Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        exit(1);
    }
}

void ObjetSDL::afficher(SDL_Renderer * renderer, float posX, float posY, float taille) {
    int ok;

    SDL_Rect r;
    r.x = posX;
    r.y = posY;
    r.w = w * (taille / 100.0);
    r.h = h * (taille / 100.0);

    ok = SDL_RenderCopy(renderer, texture, nullptr, &r);
    if (ok != 0) {
        std::cout << "Failed to print texture. Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        exit(1);
    }
}