#include "genearbre.h"
#include "modify.h"
#include "inittree.h"

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


/* cherche une anomalie du graphe, ie si la descendance d'une personne
 * permet de boucler et revenir à elle même
 * pour qu'une telle boucle existe, il faut qu'en "remontant" la parenté
 * on arrive toujours sur qqun n'ayant pas de pere/mere, le temps pour l'atteindre
 * etant au plus la taille du graphe*/
int
chercher_anomalie(Graphe arbre)
{
	size_t gsize = 1, i;
	Personne *parclist = arbre.tete, *parcparent;
	int err;

	if (parclist == NULL) return 0;
	while (parclist->suiv){
		parclist = parclist->suiv;
		gsize ++;
	};

	parclist = arbre.tete;
	while (parclist){
		parcparent = parclist;
		err = 1;
		for (i = 0; i < gsize; i++){
			if (!parcparent->pere){
				err = 0;
				break;
			};
			parcparent = parcparent->pere;
		};
		if (err) return ERRCYC;

		parcparent = parclist;
		err = 1;
		for (i = 0; i < gsize; i++){
			if (!parcparent->mere){
				err = 0;
				break;
			};
			parcparent = parcparent->mere;
		};
		if (err) return ERRCYC;
	};

	return 0;
}

