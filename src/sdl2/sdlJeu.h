#ifndef SDLJEU_H
#define SDLJEU_H
#include "ObjetSDL.h"
#include "Bouton.h"
#include "Jeu.h"
#include <iostream>

using namespace std;

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

//! \brief Module gérant la boucle du jeu
class sdlJeu {
public:
    sdlJeu();
    ~sdlJeu();
    int sdlBoucleMenu();
    int sdlBoucleCharger();
    int sdlBoucleJeu();
    Jeu jeu;

private:
    bool menuRunning, gameRunning, menuChargerRunning;

    int selectionMenu;
    
    ObjetSDL fondMenu;
    ObjetSDL fondCharger;
    ObjetSDL fondJeu;
    ObjetSDL carreClair;
    ObjetSDL carreClair2;

    Bouton boutonRecommencer;
    Bouton boutonJouer;
    Bouton boutonCharger;
    Bouton boutonQuitter;
    
    
    TTF_Font * font24;
    TTF_Font * font32;
    TTF_Font * font48;
    TTF_Font * font64;
    SDL_Color blanc;
    SDL_Color grisEcriture;
    
    SDL_Window * window;
    SDL_Renderer * renderer;
    
    void sdlAffichageMenu();

    void sdlAffichageMenuCharger();

    void sdlAffichageJeu();
    void sdlAffichagePlateau(float mouseX, float mouseY);
    void sdlAffichagePionSelectionne(float mouseX, float mouseY);
    void sdlAffichagePionsRestants(float mouseX, float mouseY);

    void renderText(float p_x, float p_y, const char* p_text, TTF_Font* font, SDL_Color textColor);
    void renderCenterText(float p_x, float p_y, const char* p_text, TTF_Font* font, SDL_Color textColor);
    //void recommencerPartie();
};


#endif