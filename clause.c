#include "clause.h"

/* initialise la liste des clauses de la formule */
void init_formule() {
	int i;
	formule = malloc(sizeof(Clause)*nombreClause);
	for (i=0; i<nombreClause; i++)
		formule[i] = init_clause(i);
}

/* initialise une nouvelle clause    ***/
Clause init_clause(int num) {
	Clause c = { .num_clause=num, .taille=0, .taille_courante=0, .satisfaite=0, .satisfaite_par=0 , .variables = malloc(sizeof(int)*nombreVariable) };
	return c;
}
/* ajout_variable(c,v) ajoute la variable v à la clause c **/
void ajout_variable(int num_clause, int num_var) {
	formule[num_clause].variables[formule[num_clause].taille] = num_var;
	formule[num_clause].taille++;
	formule[num_clause].taille_courante++;
	liste_variable[num_var].clauses[liste_variable[num_var].nombre_occurence] = num_clause;
	liste_variable[num_var].nombre_occurence++;
	liste_variable[num_var].nombre_occurence_courant++;
	liste_variable[num_var].enleve = 0;
	/* si son inverse existe dans une clause alors mettre pur à 0 , si ce n'est pas déja fais*/
	if ( liste_variable[num_var].pur && liste_variable[inverse(num_var)].nombre_occurence>0 ) {
		liste_variable[num_var].pur = 0;
		liste_variable[inverse(num_var)].pur = 0;
	}
}

/* la fonction qui affiche la clause *****/
void afficher_clause(int num_clause) {
	for (int i=0; i<formule[num_clause].taille; i++ )
		if ( liste_variable[formule[num_clause].variables[i]].enleve == 0 )
			printf("%d(%d)  ",liste_variable[formule[num_clause].variables[i]].numero, liste_variable[formule[num_clause].variables[i]].nombre_occurence);
	printf("\n---> taille : %d - numéro clause : %d \n",formule[num_clause].taille, num_clause);
}

void afficher_formule() {
	printf("liste des clauses : \n");
	for ( int i=0; i<nombreClause; i++ )
		afficher_clause(i);
}


