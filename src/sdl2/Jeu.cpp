#include "Jeu.h"
#include <cstring>
#include <iostream>

using namespace std;

Jeu::Jeu() {
    joueurs[0].id = 1;
    joueurs[0].name = "Joueur1";
    joueurs[0].estGagnant = false; //Donnee membre non utilisee pour l'instant

    joueurs[1].id = 2;
    joueurs[1].name = "Joueur2";
    joueurs[1].estGagnant = false;

    //Quand la partie commence, le joueur 2 va designer un pion, qui va ensuite etre
    //place par le joueur 1
    joueurQuiPlace = 1;
    joueurQuiDesigne = 2;

    int indice = 0;
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            for (int k = 0; k < 2; k++)
                for (int l = 0; l < 2; l++) {
                    pionsDisponibles[indice] = Pion(bool(i), bool(j), bool(k), bool(l), true, indice);
                    indice++;
                }

    for (int i = 0; i <  4; i++) {
        for(int j = 0; j < 4; j++) {
            grillePion[i][j]=-1; //Au debut la grille est vide
        }
    }

    sourisPrendUnPion = false;
    plateauPlein = false;
    pionSelectionne = -1;
    //sauvegardeId = 0;
}

Jeu::~Jeu () {

}

void Jeu::chargerImagesPions(SDL_Renderer * renderer) {
    for(int i = 0; i < 16; i++) {
        string istr = to_string(i);
        string str = "data/img/pions/pion" + istr + ".png";
        char filename[60];
        strcpy(filename, str.c_str());

        /*
        ObjetSDL p;
        p.w = 125;
        p.h = 125;*/

        pionsDisponibles[i].image.chargerTexture(renderer, filename);
        pionsDisponibles[i].image.w = 125;
        pionsDisponibles[i].image.h = 125;
    }
}


bool Jeu::verifCaractCommune(int indicePion1, int indicePion2, 
                    int indicePion3, int indicePion4) const {
    if (indicePion1==-1 || indicePion2==-1 || indicePion3==-1 || indicePion4==-1) return false;
    Pion p1 = pionsDisponibles[indicePion1]; //On récupère les pions dont on va vérifier les caracteristques
    Pion p2 = pionsDisponibles[indicePion2];
    Pion p3 = pionsDisponibles[indicePion3];
    Pion p4 = pionsDisponibles[indicePion4];

    if ((p1.getCouleur() == p2.getCouleur()) &&  (p2.getCouleur() == p3.getCouleur()) && (p3.getCouleur() == p4.getCouleur()))
        return true;
    if ((p1.getHauteur() == p2.getHauteur()) &&  (p2.getHauteur() == p3.getHauteur()) && (p3.getHauteur() == p4.getHauteur()))
        return true;
    if ((p1.getSommet() == p2.getSommet()) &&  (p2.getSommet() == p3.getSommet()) && (p3.getSommet() == p4.getSommet()))
        return true;
    if ((p1.getForme() == p2.getForme()) &&  (p2.getForme() == p3.getForme()) && (p3.getForme() == p4.getForme()))
        return true;
    return false;
}

bool Jeu::verifierVictoire() const {
    for (int i = 0; i <= 3; i++) { //Verification des lignes et des colonnes
        if(verifCaractCommune(grillePion[i][0], grillePion[i][1], grillePion[i][2], grillePion[i][3])) return true;
        if(verifCaractCommune(grillePion[0][i], grillePion[1][i], grillePion[2][i], grillePion[3][i])) return true;
    }
    //Verification des deux diagonales
    if(verifCaractCommune(grillePion[0][0], grillePion[1][1], grillePion[2][2], grillePion[3][3])) return true;
    if(verifCaractCommune(grillePion[0][3], grillePion[1][2], grillePion[2][1], grillePion[3][0])) return true;

    return false;
}

bool Jeu::verifierPlateauPlein() const {
    for(int i = 0; i <= 3; i++) {
        for(int j = 0; j <= 3; j++) {
            if (grillePion[i][j]==-1) return false;
        }
    }
    return true;
}

int Jeu::getJoueurQuiDesigne() const {
    return joueurQuiDesigne;
}

int Jeu::getJoueurQuiPlace() const {
    return joueurQuiPlace;
}

void Jeu::echangerRolesJoueurs() {
    if (joueurQuiDesigne == 1) {
        joueurQuiDesigne = 2;
        joueurQuiPlace = 1;
    } else {
        joueurQuiDesigne = 1;
        joueurQuiPlace = 2;
    }
}