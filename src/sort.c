#include "genearbre.h"
#include "sort.h"

/* rechaine la liste selon l'ordre alphabetique */
void
ordonner_graphe(Graphe *arbre)
{
	size_t len = 1, i;
	Personne *parclist = arbre->tete;
	Personne **listtab;

	if (parclist == NULL) return;
	while (parclist->suiv != NULL){
		len ++;
		parclist = parclist->suiv;
	};

	listtab = (Personne **) malloc(len * sizeof(Personne *));
	parclist = arbre->tete;
	for (i = 0; i < len; i++){
		*(listtab + i) = parclist;
		parclist = parclist->suiv;
	};
	/* listtab is an array containing every person, easier
	 * to sort than a chained list as arbre */
	sorttab(listtab, len);
	arbre->tete = *listtab;
	for (i = 0; i < len - 1; i++){
		(*(listtab + i))->suiv = *(listtab + i + 1);
	};
	(*(listtab + len - 1))->suiv = NULL;

	free(listtab);

}


/* implémentation d'un merge sort */
void
sorttab(Personne **tab, size_t len)
{
	if (len == 1) return;
	sorttab(tab, len/2);
	sorttab(tab+len/2, len/2 + len%2);
	merge(tab, len/2, tab+len/2, len/2 + len%2);
}

void
merge(Personne **t1, size_t l1, Personne **t2, size_t l2)
{
	size_t i1 = 0, i2 = 0;
	Personne **tmpsort = (Personne **) malloc((l1 + l2) * sizeof(Personne *));
	while (i1 < l1 && i2 < l2){
		if (strcmp((*(t1 + i1))->nom, (*(t2 + i2))-> nom) < 0){
			*(tmpsort + i1 + i2) = *(t1 + i1);
			i1++;
		} else {
			*(tmpsort + i1 + i2) = *(t2 + i2);
			t2++;
		};
	};
	if (i1 == l1) memcpy(t1, tmpsort, (i1 + i2) * sizeof(Personne *));
	else {
		memcpy((t2 + l2 - l1 + i1), (t1 + i1), (l1 - i1) * sizeof(Personne *));
		memcpy(t1, tmpsort, (i1 + i2) * sizeof(Personne *));
	};

	free(tmpsort);
}

