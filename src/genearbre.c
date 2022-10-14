#include "genearbre.h"
#include "modify.h"

int
main()
{
	return 0;
}


/* renvoie (un pointeur sur) la personne contenant le nom cherché */
Personne *
trouver_personne(char *nomch, Graphe arbre)
{
	int i = 0, same;
	same = 1;
	Personne *indiv = arbre.tete;

	while (indiv->suiv != NULL){
		while (*(nomch+i) != '\0'){
			if (*(nomch+i) != indiv->nom[i]){
				same = 0;
				break;
			};
		};
		if (same) return indiv;
		indiv = indiv->suiv;
		i = 0;
		same = 1;
	};
	while (*(nomch+i) != '\0'){
		if (*(nomch+i) != indiv->nom[i]){
			same = 0;
			break;
		};
	};
	if (same) return indiv;

	return NULL;
}


/* affiche sur stdout les relations de chaque personne du graphe */
void
afficher_graphe(Graphe arbre)
{
	Personne *parclist = arbre.tete;

	while(parclist != NULL){
		printf("%s\n", parclist->nom);

		if (parclist->suiv != NULL){
			printf("  suivant : %s\n", parclist->suiv->nom);
		} else {
			printf("  suivant : (null)\n");
		};

		if (parclist->mere != NULL){
			printf("  mere : %s\n", parclist->mere->nom);
		} else {
			printf("  mere : (null)\n");
		};

		if (parclist->pere != NULL){
			printf("  pere : %s\n", parclist->pere->nom);
		} else {
			printf("  pere : (null)\n");
		};

		if (parclist->padelphe != NULL){
			printf("  adelphe paternel : %s\n", parclist->padelphe->nom);
		} else {
			printf("  adelphe paternel : (null)\n");
		};

		if (parclist->madelphe != NULL){
			printf("  adelphe maternel : %s\n", parclist->madelphe->nom);
		} else {
			printf("  adelphe maternel : (null)\n");
		};

		if (parclist->enf != NULL){
			printf("  enfant : %s\n\n\n", parclist->enf->nom);
		} else {
			printf("  enfant : (null)\n\n\n");
		};
	};
}

