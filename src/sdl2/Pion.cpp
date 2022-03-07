#include "Pion.h"
#include <iostream>
using namespace std;


Pion::Pion() {
    couleur = 0;
    hauteur = 0;
    sommet = 0;
    forme = 0;
    disponible = 1;
    identifiant = 0;
}

Pion::Pion(const bool c, const bool h, const bool s, 
                    const bool f, const bool dispo, unsigned char id) {
    couleur = c;
    hauteur = h;
    sommet = s;
    forme = f;
    disponible = dispo;
    identifiant = id;
}

Pion::~Pion() {

}

bool Pion::getCouleur() const {
    return couleur;
}

bool Pion::getHauteur() const {
    return hauteur;
}

bool Pion::getSommet() const {
    return sommet;
}

bool Pion::getForme() const {
    return forme;
}

bool Pion::getDisponible() const {
    return disponible;
}

int Pion::getID() const {
    return identifiant;
}

void Pion::setCouleur(bool c) {
    couleur = c;
}

void Pion::setHauteur(bool h) {
    hauteur = h;
}

void Pion::setSommet(bool s) {
    sommet = s;
}

void Pion::setForme(bool f) {
    forme = f;
}

void Pion::setDisponible(bool dispo) {
    disponible = dispo;
}

void Pion::setID(int id)
{
    identifiant = id;
}