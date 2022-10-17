#include "genearbre.h"
#include "out.h"


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


/* affiche une personne en tant que membre d'un arbre (racine a gauche)*/
void
print_pers(Personne *moi, size_t tabc, int dir)
{
	size_t i;

	for (i = 0; i < tabc; i++) printf("    ");

	if (dir == ROOT) printf("%s\n", moi->nom);
	else if (dir == LEFT){
		printf ("%s\n", moi->nom);
		for (i = 0; i < tabc; i++) printf("    ");
		printf("/\n");
	} else {
		printf("\\\n");
		for (i = 0; i < tabc; i++) printf("    ");
		printf ("%s\n", moi->nom);
	};
}


/* affiche l'ascendance d'une personne */
void
print_ascend(Personne *tmproot, size_t tabc, int dir)
{
	if (tmproot->mere) print_ascend(tmproot->mere, tabc+1, LEFT);
	print_pers(tmproot, tabc, dir);
	if (tmproot->pere) print_ascend(tmproot->pere, tabc+1, RIGHT);
}
