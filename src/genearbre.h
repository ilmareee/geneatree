#include <stdio.h>

typedef struct Pers{
	char nom [256];
	struct Pers *pere;
	struct Pers *mere;
	struct Pers *madelphe;
	struct Pers *padelphe;
	struct Pers *enf;
	struct Pers *suiv;
} Personne;

typedef struct {
	Personne *tete;
} Graphe;

Personne *trouver_personne(char *,Graphe);
void afficher_graphe(Graphe);

