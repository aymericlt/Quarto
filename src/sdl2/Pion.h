#ifndef _PION
#define _PION

#include "ObjetSDL.h"

class Pion
{
public:
	Pion();
	Pion(const bool c, const bool h, const bool s, const bool f, 
			const bool dispo, unsigned char id);
	~Pion();

	ObjetSDL image;
	
	/**\brief Constructeur avec parametres.
	\details Initialise toutes les donnees membres avec
	les donnees fournies en parametre. Celui qu_on va utiliser pour le jeu car il 
	permettra d_obtenir 16 pions differents	
	couleur  0:Claire | 1:Fonce
	hauteur  0:Basse  | 1:Haute
	sommet   0:Creux  | 1:Plein
	forme    0:Rond   | 1:Carre
	*/


	bool getCouleur() const;
	bool getHauteur() const;
	bool getSommet() const;
	bool getForme() const;

	bool getDisponible() const;
	int getID() const;

	void setCouleur(bool c);
	void setHauteur(bool h);
	void setSommet(bool s);
	void setForme(bool f);

	void setDisponible(bool dispo);
	void setID(int id);
	
private:
	bool couleur;
	bool hauteur;
	bool sommet;
	bool forme;

	bool disponible;
	int identifiant;
};
#endif
