#include "sdlJeu.h"

int main(int argc, char* argv[])
{
    sdlJeu sjeu;
    
    int choixBoucle = 0; //-1 = quitter, 0 = menu principal, 1 = jouer, 2 = menu charger
    
    do {
        switch (choixBoucle) {
        case 0 :
            choixBoucle = sjeu.sdlBoucleMenu();
            break;
        case 1 :
            choixBoucle = sjeu.sdlBoucleJeu();
            break;
        }
    } while (choixBoucle != -1);
    
    return 0;
}