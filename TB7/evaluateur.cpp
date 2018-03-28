#define _USE_MATH_DEFINES

#include "Header.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <conio.h>

int factorielle(int x) {
	int resultat = 1;
	for (int i = x; i > 0; i--) resultat *= i;
	return resultat;

}

float evaluateur(Arbre arbre, float x, int * erreur) {
	float retour = 0;
	float resultat;
	*erreur = 0;
	if (arbre == NULL) {
		printf("Erreur 200 : Arbre non defini\n");
		*erreur = 200;
	}
	else {
		switch (arbre->jeton.lex)
		{
		case VAR:
			retour = x;
			break;
		case REEL:
			retour = arbre->jeton.valeur.reel;
			break;
		case FONCTION:
			switch (arbre->jeton.valeur.fonction) {
			case ABS:
				retour = fabs(evaluateur(arbre->jeton_gauche, x, erreur));
				break;
			case SIN:
				retour = sin(evaluateur(arbre->jeton_gauche, x, erreur));
				break;
			case COS:
				retour = cos(evaluateur(arbre->jeton_gauche, x, erreur));
				break;
			case LOG:
				resultat = evaluateur(arbre->jeton_gauche, x, erreur);
				if (resultat > 0) {
					retour = log10(resultat);
				}
				else {
					printf("Erreur 251, le log d'un nombre negatif n'est pas possible\n");
					*erreur = 251;
				}

				break;
			case TAN:
				resultat = evaluateur(arbre->jeton_gauche, x, erreur);
				if (cos(resultat) != 0) {
					retour = sin(resultat) / cos(resultat);
				}
				else {
					printf("Erreur 253, tan infinie\n");
					*erreur = 253;
				}
				break;
			case EXP:
				retour = exp(evaluateur(arbre->jeton_gauche, x, erreur));
				break;
			case SQRT:
				resultat = evaluateur(arbre->jeton_gauche, x, erreur);
				if (resultat >= 0) retour = sqrt(resultat);
				else {
					printf("Erreur 252, la racine d'un nombre negatif n'est pas possible\n");
					*erreur = 252;
				}
				break;
			case LN:
				resultat = evaluateur(arbre->jeton_gauche, x, erreur);
				if (resultat != 0) {
					retour = log(resultat);
				}
				else {
					printf("Erreur 251, le log d'un nombre negatif n'est pas possible\n");
					*erreur = 251;
				}
				break;
			case FACTORIELLE:
				retour = (float)factorielle((int)evaluateur(arbre->jeton_gauche, x, erreur));
				break;
			case PARTIE_ENTIERE:
				retour = float(int(evaluateur(arbre->jeton_gauche, x, erreur)));
				break;
			case PARTIE_DECIMALE:
				resultat = evaluateur(arbre->jeton_gauche, x, erreur);
				retour = resultat - float(int(resultat));
				break;
			default:
				printf("Erreur 201, fonction non definie\n");
				*erreur = 201;
				break;
			}
			break;
		case OPERATEUR:
			switch (arbre->jeton.valeur.operateur) {
			case PLUS:
				retour = evaluateur(arbre->jeton_gauche, x, erreur) + evaluateur(arbre->jeton_droit, x, erreur);
				break;
			case MOINS:
				retour = evaluateur(arbre->jeton_gauche, x, erreur) - evaluateur(arbre->jeton_droit, x, erreur);
				break;
			case FOIS:
				retour = evaluateur(arbre->jeton_gauche, x, erreur) * evaluateur(arbre->jeton_droit, x, erreur);
				break;
			case DIV:
				resultat = evaluateur(arbre->jeton_droit, x, erreur);
				if (resultat == 0) {
					printf("Erreur 250 : Division par 0\n");
					*erreur = 250;
				}
				else retour = evaluateur(arbre->jeton_gauche, x, erreur) / resultat;
				break;
			}
			break;
		default:
			printf("Erreur 210, jeton non compris\n");
			*erreur = 210;

		}
	}
	
	return retour;
}