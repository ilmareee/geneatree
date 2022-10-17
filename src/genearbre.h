#include <stdio.h>

#define ERRCYC 10
#define RECREATE 1
#define FILIATIONS 2
#define VALID 3
#define ORDER 4
#define PRINT 5
#define QUIT 0
#define AMERE 1
#define APERE 2
#define DMERE 3
#define DPERE 4
#define ALL 1
#define ASCEND 2
#define GEN 3
#define ALLGEN 4

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
void filiations(Graphe *);
void printinterface(Graphe);
int chercher_anomalie(Graphe);

