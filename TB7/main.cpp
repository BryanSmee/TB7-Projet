#include "Header.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

int main() {
	Arbre arbre = (Arbre)malloc(sizeof(struct Noeud));
	arbre->jeton.lex = FONCTION;
	arbre->jeton.valeur.fonction = PARTIE_ENTIERE;
	arbre->jeton_gauche = (Arbre)malloc(sizeof(struct Noeud));
	arbre->jeton_droit = NULL;
	arbre->jeton_gauche->jeton.lex = OPERATEUR;
	arbre->jeton_gauche->jeton.valeur.operateur = PLUS;
	arbre->jeton_gauche->jeton_gauche = (Arbre)malloc(sizeof(struct Noeud));
	arbre->jeton_gauche->jeton_gauche->jeton.lex = REEL;
	arbre->jeton_gauche->jeton_gauche->jeton.valeur.reel = 2;
	arbre->jeton_gauche->jeton_gauche->jeton_droit = NULL;
	arbre->jeton_gauche->jeton_gauche->jeton_gauche = NULL;
	arbre->jeton_gauche->jeton_droit = (Arbre)malloc(sizeof(struct Noeud));
	arbre->jeton_gauche->jeton_droit->jeton.lex = VAR;
	arbre->jeton_gauche->jeton_droit->jeton_droit = NULL;
	arbre->jeton_gauche->jeton_droit->jeton_gauche = NULL;
	for (float x = 0; x <= 10; x += 0.5) {
		printf("%f\n", evaluateur(arbre, x));

	}
	_getch();
	return 0;
}