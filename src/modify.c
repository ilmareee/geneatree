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
 *  * son pere sur lui en tant que son adelphe paternel (depuis le pere
 *   * si il n'avait encore aucun enfant */
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
 *  * sa mere sur lui en tant que son adelphe maternel (depuis la mere
 *   * si elle n'avait encore aucun enfant */
void
filiation_mere_enfant(Personne *enf, Personne *mere)
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


/* annule la filiation pere-enfant :
 * - supprime le pointeur de l'enfant sur la pere
 * - "resoude" la chaine des adelphes sans l'enfant*/
void
annuler_pere_enfant(Personne *enf)
{
	Personne *parcfil = enf->pere;
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
}


/* annule la filiation mere-enfant :
 * - supprime le pointeur de l'enfant sur la mere
 * - "resoude" la chaine des adelphes sans l'enfant*/
void
annuler_mere_enfant(Personne *enf)
{
	Personne *parcfil = enf->mere;
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
}

