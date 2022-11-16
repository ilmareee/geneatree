#include "genearbre.h"
#include "inittree.h"
#include "modify.h"


/* demande à l'utilisateur s'il veut rajouter de nouvelles personnes a l arbre*/
void
init(Graphe *arbre)
{
	int ret;
	char nom[256];
	char placetrigg = 'O';

	while (placetrigg == 'O' || placetrigg == 'o'){
		printf("Vous allez rentrer une nouvelle personne\n");
		printf("Rentrer son nom : ");
		ret = scanf("%255s", nom);
		getchar();
		if(ret == 1){
			recplacement(arbre, nom);
			printf("Voulez vous rentrer une autre personne ?\n"
					"Entrer O ou o pour oui, N ou n pour non :");
			scanf("%c", &placetrigg);
			getchar();
		} else {
			printf("Erreur d'input, veuillez recommencer\n");
		};
	};
}


/* ajoute récursivement la personne donnée au graphe ainsi que ses parents
 * et établit la filiation*/
Personne *
recplacement(Graphe *arbre, char nom[256])
{
	Personne *parent, *currpers;
	char pnom[256];
	int trigg = 1, ret;

	currpers = enregistrer_personne(arbre, nom);
	printf("%s vient d'être enregistre(e)\n", nom);

	while (trigg){
		printf("%s a-t-iel un pere ?\n"
				"Si oui, rentrer son nom, sinon écrire NULL : ", nom);
		ret = scanf("%255s", pnom);
		getchar();
		if (ret == 1){
			if(strcmp(pnom, "NULL")){ // retourne 1 si pnom =/= "NULL"
				parent = trouver_personne(pnom, *arbre);
				if (parent == NULL) parent = recplacement(arbre, pnom);
				filiation_pere_enfant(currpers, parent);
			};
			trigg = 0;
		} else {
			printf("Erreur d'input, veuillez recommencer");
		};
	};

	trigg = 1;
	while (trigg){
		printf("%s a-t-iel une mere ?\n"
				"Si oui, rentrer son nom, sinon écrire NULL : ", nom);
		ret = scanf("%255s", pnom);
		getchar();
		if (ret == 1){
			if(strcmp(pnom, "NULL")){
				parent = trouver_personne(pnom, *arbre);
				if (parent == NULL) parent = recplacement(arbre, pnom);
				filiation_mere_enfant(currpers, parent);
			};
			trigg = 0;
		} else {
			printf("Erreur d'input, veuillez recommencer");
		};
	};

	return currpers;
}

