#include "genearbre.h"
#include "modify.h"


Personne *
enregistrer_personne(Graphe *arbre, char *nom)
{
	Personne *parclist = arbre->tete;
	Personne *nouv = (Personne *) calloc(1, sizeof(Personne));
	int i;

	for (i = 0; *(nom + i) != '\0' && i < 255; i++) nouv->nom[i] = *(nom + i);
	nouv->nom[i] = '\0';
	free(nom);

	if (parclist == NULL){
		arbre->tete = nouv;
		return nouv;
	};

	while (parclist->suiv != NULL){
		parclist = parclist->suiv;
	};
	parclist->suiv = nouv;

	return nouv;
}


/* crée un pointeur de l'enfant sur son pere, et du dernier enfant de
 * son pere sur lui en tant que son adelphe paternel (depuis le pere
 * si il n'avait encore aucun enfant
 * retourne 1 si l'enfant avait déjà un père, 0 en cas de succès*/
int
filiation_pere_enfant(Personne *enf, Personne *pere)
{
	Personne *frat = pere->enf;

	if (enf->pere) return 1;
	enf->pere = pere;
	if (frat == NULL){
		pere->enf = enf;
		return 0;
	};

	while (frat != NULL) frat = frat->padelphe;
	frat->padelphe = enf;

	return 0;
}


/* crée un pointeur de l'enfant sur sa mere, et du dernier enfant de
 * sa mere sur lui en tant que son adelphe maternel (depuis la mere
 * si elle n'avait encore aucun enfant
 * retourne 1 si l'enfant avait déjà un père, 0 en cas de succès*/
int
filiation_mere_enfant(Personne *enf, Personne *mere)
{
	Personne *frat = mere->enf;

	if (enf->mere) return 1;
	enf->mere = mere;
	if (frat == NULL){
		mere->enf = enf;
		return 0;
	};

	while (frat != NULL) frat = frat->madelphe;
	frat->madelphe = enf;

	return 0;
}


/* annule la filiation pere-enfant :
 * - supprime le pointeur de l'enfant sur la pere
 * - "resoude" la chaine des adelphes sans l'enfant
 * retourne 1 si l'enfant n'a pas de père, 0 sur un succès*/
int
annuler_pere_enfant(Personne *enf)
{
	Personne *parcfil = enf->pere;
	if (!parcfil) return 1;

	enf->pere = NULL;
	if (parcfil->enf == enf){
		if (enf->padelphe == enf) parcfil->enf = NULL;
		else parcfil->enf = enf->padelphe;
	} else {
		parcfil = parcfil->enf;
		while (parcfil->padelphe != enf) parcfil = parcfil->padelphe;
		parcfil->padelphe = enf->padelphe;
	};
	enf->padelphe = enf;
	return 0;
}


/* annule la filiation mere-enfant :
 * - supprime le pointeur de l'enfant sur la mere
 * - "resoude" la chaine des adelphes sans l'enfant
 * retourne 1 si l'enfant n'a pas de père, 0 sur un succès*/
int
annuler_mere_enfant(Personne *enf)
{
	Personne *parcfil = enf->mere;
	if (!parcfil) return 1;

	enf->mere = NULL;
	if (parcfil->enf == enf){
		if (enf->madelphe == enf) parcfil->enf = NULL;
		else parcfil->enf = enf->madelphe;
	} else {
		parcfil = parcfil->enf;
		while (parcfil->madelphe != enf) parcfil = parcfil->madelphe;
		parcfil->madelphe = enf->madelphe;
	};
	enf->madelphe = enf;

	return 0;
}


/*libere tout l'espace utilisé par le graphe actuel*/
void
liberer_graphe(Graphe *arbre)
{
	Personne *tmp1, *tmp2;
	if (!arbre->tete) return;

	tmp1 = arbre->tete;
	tmp2 = tmp1->suiv;

	while (tmp2){
		free(tmp1);
		tmp1 = tmp2;
		tmp2 = tmp1->suiv;
	};
	free(tmp1);
	arbre->tete = NULL;
}
