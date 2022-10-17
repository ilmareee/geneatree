#define ROOT 0
#define LEFT 1
#define RIGHT 2

void afficher_graphe(Graphe);
void afficher_pers(Personne *, size_t, int);
void print_ascend(Personne *, size_t, int);
void print_child(Personne *);
void print_gen(Personne *, int);
void print_all_gen(Personne *, int);

