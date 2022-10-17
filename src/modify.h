#include <stdio.h>
#include <stdlib.h>


Personne *enregistrer_personne(Graphe *, char *);
int filiation_pere_enfant(Personne *, Personne *);
int filiation_mere_enfant(Personne *, Personne *);
int annuler_pere_enfant(Personne *);
int annuler_mere_enfant(Personne *);
void liberer_graphe(Graphe *);

