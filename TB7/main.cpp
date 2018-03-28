#include "Header.h"
#include "evaluateur.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

int main() {
	Arbre arbre = (Arbre)malloc(sizeof(struct Noeud));
	arbre->jeton.lex = FONCTION;
	arbre->jeton.valeur.fonction = SQRT;
	arbre->jeton_gauche = (Arbre)malloc(sizeof(struct Noeud));
	arbre->jeton_droit = NULL;
	arbre->jeton_gauche->jeton.lex = OPERATEUR;
	arbre->jeton_gauche->jeton.valeur.operateur = MOINS;
	arbre->jeton_gauche->jeton_droit = (Arbre)malloc(sizeof(struct Noeud));
	arbre->jeton_gauche->jeton_droit->jeton.lex = REEL;
	arbre->jeton_gauche->jeton_droit->jeton.valeur.reel = 5;
	arbre->jeton_gauche->jeton_droit->jeton_droit = NULL;
	arbre->jeton_gauche->jeton_droit->jeton_gauche = NULL;
	arbre->jeton_gauche->jeton_gauche = (Arbre)malloc(sizeof(struct Noeud));
	arbre->jeton_gauche->jeton_gauche->jeton.lex = VAR;
	arbre->jeton_gauche->jeton_gauche->jeton_droit = NULL;
	arbre->jeton_gauche->jeton_gauche->jeton_gauche = NULL;
	int erreur = 0;
	for (float x = 0; x <= 10; x += 0.5) {
		float y = evaluateur(arbre, x, &erreur);
		if(erreur == 0) printf("%f\n", y);
	}
	_getch();
	return 0;
}