#include "variable.h"

/* initialise la liste des variables */
void init_list_variable() {
	int i;
	liste_variable = malloc(sizeof(Variable)*(nombreVariable+1));
	/* ajout de toutes les variables dans la liste */
	for ( i=0; i<=nombreVariable; i++)
		liste_variable[i] = init_variable(i);
}

/* initialise une variable avec le numéro n */
Variable init_variable(int n) {
	Variable v = { .numero = n, .nombre_occurence = 0, .nombre_occurence_courant=0, .pur=1, .enleve=1, .clauses = malloc(sizeof(int)*nombreClause) };
	return v;
}

/* affiche la variable v */
void afficher_variable(int num) {
	if ( num>nombreVariable ) return;
	printf("%d ",liste_variable[num].numero);
}

/* affiche la liste des variable */
void afficher_liste_variable() {
	//printf("liste des variables : \n");
	for ( int i=1; i<=nombreVariable; i++ )
		afficher_variable(i);
	//printf("\n");
}

/* retourne la négation de du littéral */
int inverse(int num_variable) {
	if ( num_variable <= 0 ) exit(1);
	if ( num_variable % 2 == 0 ) 
		return num_variable-1;
	return num_variable+1;
}

