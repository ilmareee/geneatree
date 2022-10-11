#include "nperslist.h"

int
main()
{
	return 0;
}


Personne *
trouver_personne(char *nomch, Graphe arbre)
{
	int i = 0;
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


Personne *
enregistrer_personne(Graphe arbre, char *nom)
{
	Personne *indiv = arbre.tete;
	Personne *nouv = (Personne *) malloc(sizeof(Personne));
	int i;

	while (indiv->suiv != NULL){
		indiv = indiv->suiv;
	};
	for (i = 0; *(nom + i) != '\0'; i++) nouv->nom[i] = *(nom + i);
	nouv->nom[i] = '\0';
	*nouv = {
		.pere = NULL;
		.mere = NULL;
		.padelphe = NULL;
		.madelphe = NULL;
		.env = NULL;
		.suiv = NULL;
	};
	indiv->suiv = nouv;

	return nouv;
}


/* crée un pointeur de l'enfant sur son pere, et du dernier enfant de
 * son pere sur lui en tant que son adelphe paternel (depuis le pere
 * si il n'avait encore aucun enfant */
void
filiation_pere_enfant(Personne *enf, Personne *pere)
{
	Personne *frat = pere->enf;

	enf->pere = pere;
	if (frat == NULL){
		pere->enf = enf;
		return;
	};

	while (frat != NULL) frat = frat->padelphe;
	frat->padelphe = enf;
}


/* crée un pointeur de l'enfant sur sa mere, et du dernier enfant de
 * sa mere sur lui en tant que son adelphe maternel (depuis la mere
 * si elle n'avait encore aucun enfant */
void
filiation_pere_enfant(Personne *enf, Personne *mere)
{
	Personne *frat = mere->enf;

	enf->mere = mere;
	if (frat == NULL){
		mere->enf = enf;
		return;
	};

	while (frat != NULL) frat = frat->madelphe;
	frat->madelphe = enf;
}
