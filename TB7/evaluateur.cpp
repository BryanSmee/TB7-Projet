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

float evaluateur(Arbre arbre, float x) {
	if (arbre == NULL) {
		printf("Erreur 200 : Arbre non defini");
		exit(200);
	}
	float retour;
	float resultat;
	switch (arbre->jeton.lex) 
	{
	case VAR :
		retour = x;
		break;
	case REEL :
		retour = arbre->jeton.valeur.reel;
		break;
	case FONCTION :
		switch (arbre->jeton.valeur.fonction) {
		case ABS :
			retour = fabs(evaluateur(arbre->jeton_gauche,x));
			break;
		case SIN :
			retour = sin(evaluateur(arbre->jeton_gauche, x));
			break;
		case COS :
			retour = cos(evaluateur(arbre->jeton_gauche, x));
			break;
		case LOG :
			resultat = evaluateur(arbre->jeton_gauche, x);
			if (resultat > 0) {
				retour = log10(resultat);
			}
			else {
				printf("Erreur 251, le log d'un nombre negatif n'est pas possible");
				exit(251);
			}
			
			break;
		case TAN :
			resultat = evaluateur(arbre->jeton_gauche, x);
			if (cos(resultat) != 0) {
				retour = sin(resultat) / cos(resultat);
			}
			else {
				printf("Erreur 253, tan infinie");
				exit(253);
			}
			break;
		case EXP :
			retour = exp(evaluateur(arbre->jeton_gauche, x));
			break;
		case SQRT :
			resultat = evaluateur(arbre->jeton_gauche, x);
			if(resultat >= 0 ) retour = sqrt(resultat);
			else {
				printf("Erreur 252, la racine d'un nombre negatif n'est pas possible");
				exit(252);
			}
			break;
		case LN :
			resultat = evaluateur(arbre->jeton_gauche, x);
			if (resultat != 0) {
				retour = log(resultat);
			}
			else {
				printf("Erreur 251, le log d'un nombre negatif n'est pas possible");
				exit(251);
			}
			break;
		case FACTORIELLE :
			retour = (float)factorielle((int)evaluateur(arbre->jeton_gauche, x));
			break;
		case PARTIE_ENTIERE :
			retour = float(int(evaluateur(arbre->jeton_gauche, x)));
			break;
		case PARTIE_DECIMALE :
			resultat = evaluateur(arbre->jeton_gauche, x);
			retour = resultat - float(int(resultat));
			break;
		default :
			printf("Erreur 201, fonction non definie");
			exit(201);
			break;
		}
		break;
	case OPERATEUR:
		switch (arbre->jeton.valeur.operateur) {
		case PLUS:
			retour = evaluateur(arbre->jeton_gauche, x) + evaluateur(arbre->jeton_droit, x);
			break;
		case MOINS:
			retour = evaluateur(arbre->jeton_gauche, x) - evaluateur(arbre->jeton_droit, x);
			break;
		case FOIS:
			retour = evaluateur(arbre->jeton_gauche, x) * evaluateur(arbre->jeton_droit, x);
			break;
		case DIV:
			resultat = evaluateur(arbre->jeton_droit, x);
			if (resultat == 0) {
				printf("Erreur 250 : Division par 0");
				exit(250);
			}
			else retour = evaluateur(arbre->jeton_gauche, x) / resultat;
			break;
		}
		break;
	default : 
		printf("Erreur 210, jeton non compris");
		exit(210);

	}
	return retour;
}