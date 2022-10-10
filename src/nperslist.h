#include <stdio.h>
#include <stdlib.h>

#define PERSNUM 10

typedef struct {
	int age;
	char fname;
	char lname;
	char tel [13];
	char genre;
	Personne *pere;
	Personne *mere;
	Personne *madelphe;
	Personne *padelphe;
	Personne *enf;
	Personne *suiv;
} Personne;

void disp_indiv(Personne *);
Indiv *new_indiv(void);
int same_indiv(Personne *, Personne *);

