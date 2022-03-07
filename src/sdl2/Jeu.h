#ifndef _JEU 
#define _JEU

#include <string>
#include "Pion.h"

struct Joueur {
	int id;
	std::string name;
	bool estGagnant;
};

class Jeu {
private:
	int prochainPion;
	int joueurQuiDesigne; 
	int joueurQuiPlace;
	int numeroTour;

public:
	Jeu();
	~Jeu();

	bool sourisPrendUnPion;
	bool plateauPlein;
	int pionSelectionne;

	Pion pionsDisponibles[16];
	int grillePion[4][4];
	Joueur joueurs[2];

	void chargerImagesPions(SDL_Renderer * renderer);

	int getJoueurQuiDesigne() const;
	int getJoueurQuiPlace() const;

	bool verifCaractCommune(int indicePion1, int indicePion2, 
						int indicePion3, int indicePion4) const;
	bool verifierVictoire() const;
	bool verifierPlateauPlein() const;

	void echangerRolesJoueurs();

};

#endif