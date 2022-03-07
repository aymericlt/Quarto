#include "Bouton.h"
#include <iostream>
using namespace std;


Bouton::Bouton() {
    etatsBouton[0].texture = nullptr;
    etatsBouton[0].x = 0;
    etatsBouton[0].y = 0;
    etatsBouton[0].w = 100;
    etatsBouton[0].h = 100;

    etatsBouton[1].texture = nullptr;
    etatsBouton[1].x = 0;
    etatsBouton[1].y = 0;
    etatsBouton[1].w = 100;
    etatsBouton[1].h = 100;

}

Bouton::~Bouton() {
    etatsBouton[0].texture = nullptr;
    etatsBouton[1].texture = nullptr;
}

void Bouton::setX(float x) {
    etatsBouton[0].x = x;
    etatsBouton[1].x = x;
}

void Bouton::setY(float y) {
    etatsBouton[0].y = y;
    etatsBouton[1].y = y;
}

void Bouton::setWidth(float w) {
    etatsBouton[0].w = w;
    etatsBouton[1].w = w;
}

void Bouton::setHeight(float h) {
    etatsBouton[0].h = h;
    etatsBouton[1].h = h;
}



void Bouton::chargerTexture(SDL_Renderer * renderer, const char* filename0, const char* filename1) {
    etatsBouton[0].texture = IMG_LoadTexture(renderer, filename0);
    if (etatsBouton[0].texture == nullptr) {
		std::cout << "Failed to load texture 0. Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        exit(1);
    }

    etatsBouton[1].texture = IMG_LoadTexture(renderer, filename1);
    if (etatsBouton[1].texture == nullptr) {
		std::cout << "Failed to load texture 1. Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        exit(1);
    }
}

void Bouton::afficher(SDL_Renderer * renderer, float mouseX, float mouseY) {
    if (isIn(mouseX, mouseY)) etatsBouton[1].afficher(renderer);
    else etatsBouton[0].afficher(renderer);
}

void Bouton::afficher(SDL_Renderer * renderer, float mouseX, float mouseY, float posX, float posY, float taille) {
    /*if (isIn(mouseX, mouseY, posX, posY, taille)) cout<<"Premier affichage"<<endl;
    else cout<<"Second affichage"<<endl;*/
    
    if (isIn(mouseX, mouseY, posX, posY, taille)) etatsBouton[1].afficher(renderer, posX, posY, taille);
    else etatsBouton[0].afficher(renderer, posX, posY, taille);
}

void Bouton::actualiserSelection(float mouseX, float mouseY, int & selection) {
    if (isIn(mouseX, mouseY)) selection = idBouton;
}

void Bouton::actualiserSelection(float mouseX, float mouseY, int & selection, float posX, float posY, float taille) {
    if (isIn(mouseX, mouseY, posX, posY, taille)) selection = idBouton;
}

bool Bouton::isIn(float mouseX, float mouseY) {
    float x, y, w, h;
    x = etatsBouton[0].x;
    y = etatsBouton[0].y;
    w = etatsBouton[0].w;
    h = etatsBouton[0].h;
    
    if (mouseX >= x && mouseX <= x+w && mouseY >= y && mouseY <= y+h) return true;
    else return false;
}

bool Bouton::isIn(float mouseX, float mouseY, float posX, float posY, float taille) {
    float x, y, w, h;
    x = posX;
    y = posY;
    w = etatsBouton[0].w * (taille / 100.0);
    h = etatsBouton[0].h * (taille / 100.0);

    if (mouseX >= x && mouseX <= x+w && mouseY >= y && mouseY <= y+h) return true;
    else return false;
}