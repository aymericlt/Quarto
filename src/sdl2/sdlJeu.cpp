#include "sdlJeu.h"
#include <cassert>
#include <string.h>

#define fps 20
#define window_width 1280
#define window_height 720

//Rspc 30 et 85 + largeur colonne/ligne de 10px
#define coin_plateau_x 40 
#define coin_plateau_y 95

#define coin_pions_restants_x 710 
#define coin_pions_restants_y 95

// ============= CLASS SDLJEU =============== //

sdlJeu::sdlJeu() {
    //Initialisation de la sdl : 
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    if (!(IMG_Init(IMG_INIT_PNG)) || (!(IMG_Init(IMG_INIT_JPG)))) {
        cout << "SDL_image could not initialize! SDL_image Error: " << SDL_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    //Creation de la fenetre : 
    window = SDL_CreateWindow("Quarto 2.0", 50, 50, window_width, window_height, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    //Creation du rendu : 
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
    {
        cout << "Erreur lors de la creation du renderer : " << SDL_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    //Initialisation des polices d'écriture
    if (TTF_Init() != 0) {
        cout << "Erreur lors de l'initialisation de la SDL_ttf : " << SDL_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    font48 = TTF_OpenFont("data/fonts/KGRedHands.ttf", 48);
    if (font48 == NULL)
        font48 = TTF_OpenFont("../data/fonts/KGRedHands.ttf", 48);
    if (font48 == NULL) {
            cout << "Erreur lors du chargement de KGRedHands.ttf! SDL_TTF Error: " << SDL_GetError() << endl; 
            SDL_Quit(); 
            exit(1);
	}

    
    font64 = TTF_OpenFont("data/fonts/KGRedHands.ttf", 64);
    if (font64 == NULL)
        font64 = TTF_OpenFont("../data/fonts/KGRedHands.ttf", 64);
    if (font64 == NULL) {
            cout << "Erreur lors du chargement de KGRedHands.ttf! SDL_TTF Error: " << SDL_GetError() << endl; 
            SDL_Quit(); 
            exit(1);
	}

    //Initialisation des couleurs
    blanc.r = 255;
    blanc.g = 255;
    blanc.b = 255;
    blanc.a = 255;

    grisEcriture.r = 216;
    grisEcriture.g = 213;
    grisEcriture.b = 219;
    grisEcriture.a = 255;
    
    jeu.chargerImagesPions(renderer);

    fondMenu.chargerTexture(renderer, "data/img/fondMenu2.png");
    fondMenu.w = 1280;
    fondMenu.h = 720;

    fondCharger.chargerTexture(renderer, "data/img/fondCharger1.png");
    fondCharger.w = 1280;
    fondCharger.h = 720;

    fondJeu.chargerTexture(renderer, "data/img/fondJeu1.png");
    fondJeu.w = 1280;
    fondJeu.h = 720;

    carreClair.chargerTexture(renderer, "data/img/carreClair.png");
    carreClair.w = 130;
    carreClair.h = 130;

    carreClair2.chargerTexture(renderer, "data/img/carreClair.png");
    carreClair2.w = 130;
    carreClair2.h = 130;

    boutonJouer.idBouton = 1;
    boutonJouer.setX(window_width/2 - 270/2);
    boutonJouer.setY(400);
    boutonJouer.setWidth(270);
    boutonJouer.setHeight(100);
    boutonJouer.chargerTexture(renderer, "data/img/boutonJouer0.png", "data/img/boutonJouer1.png");

    boutonQuitter.idBouton = -1;
    boutonQuitter.setX(window_width/2 - 270/2);
    boutonQuitter.setY(530);
    boutonQuitter.setWidth(270);
    boutonQuitter.setHeight(100);
    boutonQuitter.chargerTexture(renderer, "data/img/boutonQuitter0.png", "data/img/boutonQuitter1.png");

    

    menuRunning = false;
}

sdlJeu::~sdlJeu() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void sdlJeu::renderText(float p_x, float p_y, const char* p_text, TTF_Font* font, SDL_Color textColor) {
	SDL_Surface* surfaceMessage = TTF_RenderText_Blended(font, p_text, textColor);
	SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

	SDL_Rect src;
	src.x = 0;
	src.y = 0;
	src.w = surfaceMessage->w;
	src.h = surfaceMessage->h; 

	SDL_Rect dst;
	dst.x = p_x;
	dst.y = p_y;
	dst.w = src.w;
	dst.h = src.h;

	SDL_RenderCopy(renderer, message, &src, &dst);
	SDL_FreeSurface(surfaceMessage);
}

void sdlJeu::renderCenterText(float p_x, float p_y, const char* p_text, TTF_Font* font, SDL_Color textColor)
{
	SDL_Surface* surfaceMessage = TTF_RenderText_Blended( font, p_text, textColor);
	SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

	SDL_Rect src;
	src.x = 0;
	src.y = 0;
	src.w = surfaceMessage->w;
	src.h = surfaceMessage->h; 

	SDL_Rect dst;
	dst.x = window_width/2 - src.w/2 + p_x;
	dst.y = window_height/2 - src.h/2 + p_y;
	dst.w = src.w;
	dst.h = src.h;

	SDL_RenderCopy(renderer, message, &src, &dst);
	SDL_FreeSurface(surfaceMessage);
}

//============================MENU=============================

void sdlJeu::sdlAffichageMenu() {
    SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
    SDL_RenderClear(renderer);

    fondMenu.afficher(renderer);

    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);

    boutonJouer.afficher(renderer, mouseX, mouseY);
    boutonQuitter.afficher(renderer, mouseX, mouseY);

    SDL_RenderPresent(renderer);
}

int sdlJeu::sdlBoucleMenu() {
    menuRunning = true;
    selectionMenu = 0;

    SDL_Event events;
    
    while(menuRunning) {
        SDL_Delay(16);
        sdlAffichageMenu();
        
        while(SDL_PollEvent(&events)) {
            switch (events.type) {
                case SDL_QUIT:
                    menuRunning = false;
                    return -1;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    int mouseX, mouseY;
                    SDL_GetMouseState(&mouseX, &mouseY);
                    selectionMenu = -2;

                    boutonJouer.actualiserSelection(mouseX, mouseY, selectionMenu);
                    // boutonCharger.actualiserSelection(mouseX, mouseY, selectionMenu);
                    boutonQuitter.actualiserSelection(mouseX, mouseY, selectionMenu);

                    if (selectionMenu != -2) {
                        cout<<selectionMenu<<endl;
                        menuRunning = false;
                        return selectionMenu;
                    }
                    break;
            }
        }
    }
    return -1;
}

//============================CHARGER=============================

void sdlJeu::sdlAffichageMenuCharger() {
    SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
    SDL_RenderClear(renderer);

    fondCharger.afficher(renderer);

    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);

    boutonQuitter.afficher(renderer, mouseX, mouseY, 900, 600, 50);

    SDL_RenderPresent(renderer);
}

int sdlJeu::sdlBoucleCharger() {
    menuChargerRunning = true;
    selectionMenu = 0;
    SDL_Event events;
    
    while(menuChargerRunning) {
        SDL_Delay(16);
        sdlAffichageMenuCharger();

        while(SDL_PollEvent(&events)) {
            switch (events.type) {
                case SDL_QUIT:
                    menuChargerRunning = false;
                    return -1;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    int mouseX, mouseY;
                    SDL_GetMouseState(&mouseX, &mouseY);
                    selectionMenu = -2;

                    boutonQuitter.actualiserSelection(mouseX, mouseY, selectionMenu, 900, 600, 50);

                    if (selectionMenu != -2) {
                        cout<<selectionMenu<<endl;
                        menuRunning = false;
                        return selectionMenu;
                    }
                    break;
            }
        }
    }
    return -1;
}

//============================JOUER=============================

void sdlJeu::sdlAffichageJeu() {
    SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
    SDL_RenderClear(renderer);

    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);

    //Affichage du fond
    fondJeu.afficher(renderer);

    //Affichage statique
    boutonQuitter.afficher(renderer, mouseX, mouseY, 950, 650, 50);
    // boutonRecommencer.afficher(renderer, mouseX, mouseY, 0, 650, 50);

    sdlAffichagePlateau(mouseX, mouseY);
    sdlAffichagePionsRestants(mouseX, mouseY);
    
    char txt[50];
    if (!jeu.joueurs[0].estGagnant && !jeu.joueurs[1].estGagnant) {
        if (jeu.sourisPrendUnPion) {
            strcpy(txt, jeu.joueurs[jeu.getJoueurQuiPlace()-1].name.c_str());
            strcat(txt, " place le pion.");

            renderCenterText(0, -320, txt, font48, grisEcriture);
        } else {
            strcpy(txt, jeu.joueurs[jeu.getJoueurQuiDesigne()-1].name.c_str());
            strcat(txt, " designe un pion.");

            renderCenterText(0, -320, txt, font48, grisEcriture);
        }
    } else {
        if (jeu.joueurs[0].estGagnant) {
            strcpy(txt, jeu.joueurs[0].name.c_str());
            strcat(txt, " a gagne la partie !");

            renderCenterText(0, 0, txt, font64, grisEcriture);
        } else {
            strcpy(txt, jeu.joueurs[1].name.c_str());
            strcat(txt, " a gagne la partie !");

            renderCenterText(0, 0, txt, font64, grisEcriture);
        }
    }


    //Affichage du pion selectionne
    if (jeu.sourisPrendUnPion) sdlAffichagePionSelectionne(mouseX, mouseY);

    SDL_RenderPresent(renderer);
}

int sdlJeu::sdlBoucleJeu() {
    menuRunning = true;

    SDL_Event events;
    
    /*
    jeu.grillePion[1][1] = 5;
    jeu.grillePion[2][2] = 1;
    jeu.grillePion[3][0] = 3;
    */

    while(menuRunning) {
        
        SDL_Delay(16);
        sdlAffichageJeu();

        while(SDL_PollEvent(&events)) {
            switch (events.type) {
                case SDL_QUIT:
                    menuRunning = false;
                    return -1;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    int mouseX, mouseY;
                    SDL_GetMouseState(&mouseX, &mouseY);
                    

                    if (!jeu.sourisPrendUnPion) { //On rentre si la souris n'a pas de pion, donc que le joueur doit en selectionner un
                        //gestion des différents boutons
                        selectionMenu = -2;
                        boutonQuitter.actualiserSelection(mouseX, mouseY, selectionMenu, 950, 650, 50);
                        // boutonRecommencer.actualiserSelection(mouseX, mouseY, selectionMenu, 0, 650, 50);
                        //autres boutons
                        if (selectionMenu != -2) {
                            
                            cout<<selectionMenu<<endl;
                            menuRunning = false;
                            return selectionMenu;
                        }
                        
                        //On determine l'indice du pion selectionné
                        int id = -1;
                        if (mouseX >= 705 && mouseX <= 1190 && mouseY >= 95 && mouseY <= 630) {
                            cout<<mouseX<<endl;
                            mouseX -= 705;
                            mouseY -= 95;

                            int i = mouseX / 135;
                            int j = mouseY / 135;

                            int tempId = j*4 + i;
                            if (jeu.pionsDisponibles[tempId].getDisponible()) id = tempId;
                        }

                        if (id != -1) { //Le joueur à choisi un pion disponible
                            jeu.sourisPrendUnPion = true;
                            jeu.pionSelectionne = id;
                            jeu.pionsDisponibles[id].setDisponible(false);
                        }

                    } else {
                        if (mouseX >= 40 && mouseX <= 580 && mouseY >= 95 && mouseY <= 625) {
                            mouseX -= 40;
                            mouseY -= 95;

                            int j = mouseX / 135;
                            int i = mouseY / 135;

                            if (jeu.grillePion[i][j] == -1) { //Le joueur à posé le pion sur une case libre
                                jeu.grillePion[i][j] = jeu.pionSelectionne;
                                cout<<jeu.grillePion[i][j]<<endl;
                                jeu.pionSelectionne = -1;
                                jeu.sourisPrendUnPion = false;


                                if (jeu.verifierVictoire()) {
                                    jeu.joueurs[jeu.getJoueurQuiPlace()-1].estGagnant = true;
                                } else if (jeu.verifierPlateauPlein()) {
                                    jeu.plateauPlein = true;
                                } else {
                                    jeu.echangerRolesJoueurs();
                                }

                            }
                        }
                    }
                    
                    
                    break;
            }
        }
    }


    return -1;
}

void sdlJeu::sdlAffichagePlateau(float mouseX, float mouseY) {
    int val;
    for (int i = 0; i <= 3; i++) {
        for(int j = 0; j<= 3; j++) {
            val = jeu.grillePion[i][j];

            if (jeu.sourisPrendUnPion && val==-1 && mouseX > coin_plateau_x + j*135 && mouseX < coin_plateau_x + (j+1)*135 
                            && mouseY > coin_plateau_y + i*135 && mouseY < coin_plateau_y + (i+1)*135) {
                    carreClair.afficher(renderer, coin_plateau_x + j*135 - 2, coin_plateau_y + i*135 - 2, 100);
                }

            
            if (val != -1) {
                jeu.pionsDisponibles[val].image.afficher(renderer, coin_plateau_x + j*135, coin_plateau_y + i*135, 100);
            }
        }
    }
}

void sdlJeu::sdlAffichagePionsRestants(float mouseX, float mouseY) {
    for (int i = 0; i <= 3; i++) {
        for(int j = 0; j<= 3; j++) {
            if (jeu.pionsDisponibles[i*4+j].getDisponible()) {
                //Affichage carré blanc
                if (!jeu.sourisPrendUnPion && mouseX > coin_pions_restants_x + j*135 && mouseX < coin_pions_restants_x + (j+1)*135 
                            && mouseY > coin_pions_restants_y + i*135 && mouseY < coin_pions_restants_y + (i+1)*135) {
                    carreClair.afficher(renderer, coin_pions_restants_x + j*135 - 2, coin_pions_restants_y + i*135 - 2, 100);
                }


                //Affichage du pion
                jeu.pionsDisponibles[i*4+j].image.afficher(renderer, coin_pions_restants_x + j*135, coin_pions_restants_y + i*135, 100);
            }
        }
    }
}

void sdlJeu::sdlAffichagePionSelectionne(float mouseX, float mouseY) {
    jeu.pionsDisponibles[jeu.pionSelectionne].image.afficher(renderer, mouseX - 62, mouseY - 62, 100);
}