#pragma once
typedef enum {
	REEL, OPERATEUR, FONCTION, ERREUR, FIN, PAR_OUVR, PAR_FERM, VAR, NO_TOKEN
} typelexique;

typedef enum {
	ABS, SIN, COS, LOG, TAN, EXP, SQRT, LN, FACTORIELLE, PARTIE_ENTIERE, PARTIE_DECIMALE
} typefonction;

typedef enum {
	PLUS, MOINS, FOIS, DIV
} typeope;

typedef union {
	float reel;
	typefonction fonction;
	typeope operateur;
} typevaleur;

typedef struct {
	typelexique lex;
	typevaleur valeur;
} typejeton;

typedef struct Noeud {
	typejeton jeton;
	struct Noeud * jeton_gauche;
	struct Noeud * jeton_droit;
} Noeud;

typedef Noeud * Arbre;

typedef struct Maillon {
	typejeton jeton;
	struct Maillon * jeton_suivant;
} Maillon;

void afficher_erreur(int erreur);

float evaluateur(Arbre arbre, float x);

