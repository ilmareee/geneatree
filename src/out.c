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

		parclist = parclist->suiv;
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

/* affiche les enfants d'une personne */
void
print_child(Personne *parent)
{
	Personne *enf = parent->enf;
	if (!enf) return;

	if (enf->mere == parent){
		while (enf->madelphe != parent->enf) {
			printf ("%s,  ", enf->nom);
			enf = enf->madelphe;
		};
		printf ("%s", enf->nom);
	} else {
		while (enf->padelphe != parent->enf) {
			printf ("%s,  ", enf->nom);
			enf = enf->padelphe;
		};
		printf ("%s", enf->nom);
	};
}


/* affiche une génération donnée */
void
print_gen(Personne *parent, int genc)
{
	Personne *enf = parent->enf;
	if (!enf) return;

	if (genc == 1) print_child(parent);
	else if (enf->mere == parent){
		while (enf->madelphe != parent->enf) {
			print_gen(enf, genc-1);
			printf("  |  ");
			enf = enf->madelphe;
		};
		print_gen(enf, genc-1);
	} else {
		while (enf->padelphe != parent->enf) {
			print_gen(enf, genc-1);
			printf("  |  ");
			enf = enf->padelphe;
		};
		print_gen(enf, genc-1);
	};
}


/* affiche toutes les générations jusqu'à la génération donnée */
void
print_all_gen(Personne * parent, int genc)
{
	int i;
	for(i = 1; i <= genc; i++){
		print_gen(parent, i);
		printf("\n");
	};
}

