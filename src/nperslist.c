#include "nperslist.h"

int
main()
{
	int i, j;
	Personne **perslist = (Personne **) malloc(PERSNUM * sizeof(Personne *));

	printf("You must enter the data for PERSNUM persons\n\n");
	for(i = 0; i < PERSNUM; i++){
		printf("\n Person n°%i\n", i);
		*(perslist + i) = new_indiv();
		for (j = 0; j < i; j++){
			if (same_indiv(*(perslist + i), *(perslist + j))){
				printf("This person was entered multiple times :\n");
				disp_indiv(*(perslist + i));
			};
		};
	};

	for(i = 0; i < PERSNUM; i++){
		free(*(perslist + i));
	}
	free(perslist);

	return 0;
}


/* prints the data of an individual */
void
disp_indiv(Personne *pers)
{
	printf("Age : %i\n"
			"Initials : %c %c\n"
			"Tel : %s\n\n", pers->age, pers->fname, pers->lname, pers->tel);
}


/* Returns a pointer to the newly created/allocated individual */
Personne *new_indiv(void)
{
	Personne *pers = (Personne *) malloc(sizeof(Personne));

	printf("Enter their age : ");
	scanf("%i", &pers->age);
	getchar();
	printf("Enter their initials (with a space between them) : ");
	scanf("%c %c", &pers->fname, &pers->lname);
	getchar();
	printf("Enter their phone number (with country code) : ");
	scanf("%12c", &pers->tel);

	return pers;
}


/* tests if two individuals have the exact same data */
int
same_indiv(Personne *p1, Personne *p2)
{
	int i;

	if (p1->age != p2->age) return 0;
	if (p1->fname != p2->fname) return 0;
	if (p1->lname != p2->lname) return 0;
	for (i = 0; i < 13; i++){
		if (p1->tel[i] != p2->tel[i]) return 0;
	};

	return 1;
}

