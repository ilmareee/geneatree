#include "genearbre.h"
#include "modify.h"
#include "inittree.h"
#include "out.h"
#include "sort.h"

int
main()
{
	Graphe arbre = {NULL};
	int noquit = 1, act;

	printf("Veuillez initialiser votre arbre genealogique\n");
	init(&arbre);

	while(noquit){
		printf("Que voulez vous faire ?\n"
				"RECREATE. recreer le graphe\n"
				"FILIATIONS. modifier les filiations\n"
				"VALID. vérifier la validite du graphe\n"
				"ORDER. ordonner le graphe (ordre alphabetique\n"
				"PRINT. afficher des elements du graphe\n"
				"\nRentrer un nombre :");
		scanf("%i", &act);
		getchar();
		switch (act){
			case RECREATE :
				liberer_graphe(&arbre);
				init(&arbre);
				break;
			case FILIATIONS :
				filiations(&arbre);
				break;
			case VALID :
				if (chercher_anomalie(arbre)) printf("Graphe invalide : il existe une boucle de filiation\n");
				else printf("Graphe valide\n");
				break;
			case ORDER :
				ordonner_graphe(&arbre);
				printf("L'arbre a bien ete ordonne\n");
				break;
			case PRINT :
				printinterface(arbre);
				break;
			case QUIT :
				liberer_graphe(&arbre);
				noquit = 0;
				break;
			default :
				printf("Erreur d'input, action non reconnue\n");
				break;
		};
		printf("Appuyer sur n'importe quelle touche pour continuer\n");
		getchar();
	};
	return 0;
}

/* gere l'interface pour modifier les filiations */
void
filiations(Graphe *arbre)
{
	int act, nquit = 1;
	char *enf, *par;

	while (nquit){
		printf("Que voulez-vous faire ?\n"
				"AMERE. ajouter une mere a quelqu'un\n"
				"APERE. ajouter un pere a quelqu'un\n"
				"DMERE. supprimer la mere de quelqu'un\n"
				"DPERE. supprimer le pere de quelqu'un\n"
				"QUIT. quitter ce menu pour le menu principal\n"
				"\nEntrer un chiffre : ");
		scanf("%i",&act);
		getchar();
		switch (act){
			case AMERE :
				printf("Rentrer le nom de l'enfant : ");
				scanf("%ms", &enf);
				getchar();
				printf("Rentrer le nom du parent : ");
				scanf("%ms", &par);
				getchar();
				if (filiation_mere_enfant(trouver_personne(enf, *arbre), trouver_personne(par, *arbre))) printf("L'enfant avait deja un parent, veuillez le supprimer avant\n");
				else printf("La filiation a bien ete enregistree\n");
				break;
			case APERE :
				printf("Rentrer le nom de l'enfant : ");
				scanf("%ms", &enf);
				getchar();
				printf("Rentrer le nom du parent : ");
				scanf("%ms", &par);
				getchar();
				if (filiation_pere_enfant(trouver_personne(enf, *arbre), trouver_personne(par, *arbre))) printf("L'enfant avait deja un parent, veuillez le supprimer avant\n");
				else printf("La filiation a bien ete enregistree\n");
				break;
			case DMERE :
				printf("Rentrer le nom de l'enfant : ");
				scanf("%ms", &enf);
				getchar();
				if (annuler_mere_enfant(trouver_personne(enf, *arbre))) printf("L'enfant n'avait pas ce parent\n");
				else printf("La filiation a bien ete supprimee\n");
				break;
			case DPERE :
				printf("Rentrer le nom de l'enfant : ");
				scanf("%ms", &enf);
				getchar();
				if (annuler_pere_enfant(trouver_personne(enf, *arbre))) printf("L'enfant n'avait pas ce parent\n");
				else printf("La filiation a bien ete supprimee\n");
				break;
			case QUIT :
				nquit = 0;
				break;
			default :
				printf("Input non reconnu\n");
				break;
		};
		printf("Appuyer sur n'importe quelle touche pour continuer");
		getchar();
	};
}


/* gere l'interface pour choisir quoi afficher */
void
printinterface(Graphe arbre)
{
	int act, nquit = 1, gennbr;
	char *nom;

	while (nquit){
		printf("Que voulez-vous faire ?\n"
				"ALL. afficher tout le graphe\n"
				"ASCEND. afficher l'ascendance d'une personne\n"
				"GEN. afficher une generation de la descendance d'une personne\n"
				"ALLGEN. afficher toute la descendance d'une personne\n"
				"QUIT. quitter ce menu pour le menu principal\n"
				"\nEntrer un chiffre : ");
		scanf("%i",&act);
		getchar();
		switch (act){
			case ALL :
				afficher_graphe(arbre);
				break;
			case ASCEND :
				printf("Rentrer le nom de la personne cherchee : ");
				scanf("%ms", &nom);
				getchar();
				print_ascend(trouver_personne(nom, arbre), 0, ROOT);
				break;
			case GEN:
				printf("Rentrer le nom de la personne cherchee : ");
				scanf("%ms", &nom);
				printf("Rentrer la generation a afficher (1-enfants, 2-petits-enfants,...)");
				scanf("%i", &gennbr);
				getchar();
				if (gennbr < 1) printf("Le nombre de generations doit etre superieur strict a 0");
				else print_gen(trouver_personne(nom, arbre), gennbr);
				break;
			case ALLGEN:
				printf("Rentrer le nom de la personne cherchee : ");
				scanf("%ms", &nom);
				printf("Rentrer la generation a afficher (1-enfants, 2-petits-enfants,...)");
				scanf("%i", &gennbr);
				getchar();
				if (gennbr < 1) printf("Le nombre de generations doit etre superieur strict a 0");
				else print_all_gen(trouver_personne(nom, arbre), gennbr);
				break;
			case QUIT :
				nquit = 0;
				break;
			default :
				printf("Input non reconnu\n");
				break;
		};
		printf("Appuyer sur n'importe quelle touche pour continuer");
		getchar();
	};
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

