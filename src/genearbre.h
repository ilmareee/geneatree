#include <stdio.h>
#include <stdlib.h>

#define PERSNUM 10

typedef struct {
	char nom [20];
	Personne *pere;
	Personne *mere;
	Personne *madelphe;
	Personne *padelphe;
	Personne *enf;
	Personne *suiv;
} Personne;

typedef struct {
	Personne *tete
} Graphe;

void disp_indiv(Personne *);
Indiv *new_indiv(void);
int same_indiv(Personne *, Personne *);

