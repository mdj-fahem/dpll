#include "utile.h"
/* renvoi le mono litteral si il'existe : 0 sinon **/
int mono_litteral() {
	for ( int i=0; i<nombreClause; i++ )
		if ( formule[i].taille_courante == 1 && !formule[i].satisfaite )
			for( int j=0; j<formule[i].taille; j++ )
				if ( ! liste_variable[formule[i].variables[j]].enleve )
					return formule[i].variables[j];
	return 0;
}

/* retourne un litteral pur ou 0 sinon */
int litteral_pur() {
	int i;
	for (i=1; i<=nombreVariable; i++ )
		if ( liste_variable[i].pur && !liste_variable[i].enleve ) 
			return i;
	return 0;
}

/* retourne la prochaine variable à mettre a vrai si il aucun mono ni pur trouvé */
int prochaine_variable(){
	int max = 0, num = 0;
	for (int i=1; i<nombreVariable; i++ ) {
		if ( ! liste_variable[i].enleve && (liste_variable[i].nombre_occurence_courant > max || liste_variable[inverse(i)].nombre_occurence_courant > max) ){
			max = liste_variable[i].nombre_occurence;
			num = i;
		}
	}
	return num;
}

/* retourne un mono ou un litteral pur, ou la prochaine variable de la liste */
int prochaine_variable_a_choisir(Action *a) {
	int mono = mono_litteral();
	if ( mono ) { 
		//printf("un mono \n"); 
		a->type_branche = MONO; 
		return mono; 
	}
	int pur = litteral_pur();
	if ( pur ) { 
		//printf("pur\n"); 
		a->type_branche = PUR; 
		return pur;
	}
	a->type_branche=BRANCHE1; 
	return prochaine_variable();
}

/* enleve les clauses satisfaite lorsque une variable est choisi */
int enlever_clauses_satisfaite(Action *a){
	//printf("enlever clauses\n");
	int num = a->num_variable, nb_clauses_enlevee = 0;
	for (int i=0; i<liste_variable[num].nombre_occurence; i++ ) {
		if ( formule[liste_variable[num].clauses[i]].satisfaite ) continue;
		formule[liste_variable[num].clauses[i]].satisfaite = 1;
		formule[liste_variable[num].clauses[i]].satisfaite_par = num;
		nb_clauses_enlevee++;
	}
	liste_variable[num].enleve = 1;
	return nb_clauses_enlevee;
}

/* enleve les litteraux inverses des clauses de la formule */
void enlever_les_litteraux_inverses(Action *a) {
	//printf("enlever litteraux inverses \n");
	int num = inverse(variables_courante);
	for (int i=0; i<liste_variable[num].nombre_occurence; i++ ) {
			formule[liste_variable[num].clauses[i]].taille_courante--;
			liste_variable[num].nombre_occurence_courant--;
			if ( formule[liste_variable[num].clauses[i]].taille_courante <= 0 )
				CLAUSE_VIDE = 1;
	}
	liste_variable[num].enleve = 1;
}

/* restaurer les clauses enlevées */
int restaurer_clauses(Action *a) {
	int num = a->num_variable, nb_clauses_restauree = 0;
	//printf("restaurer les clauses \n");
	liste_variable[num].enleve = 0;
	for (int i=0; i<liste_variable[num].nombre_occurence; i++ ){
		if ( formule[liste_variable[num].clauses[i]].satisfaite_par == num ) {
			formule[liste_variable[num].clauses[i]].satisfaite = 0;
			formule[liste_variable[num].clauses[i]].satisfaite_par = 0;
			nb_clauses_restauree++;
		}
	}
	return nb_clauses_restauree;
}
/* restaurer les litteraux (inverse) enlevés */
void restaurer_litteraux(Action *a) {
	//printf("restaurer l'inverse \n");
	int num = inverse(a->num_variable);
	liste_variable[num].enleve = 0;
	for (int i=0; i<liste_variable[num].nombre_occurence; i++ ) {
		formule[liste_variable[num].clauses[i]].taille_courante++;
		liste_variable[num].nombre_occurence_courant++;
	}
}

/* affiche la solution en remontant la pile */
void afficher_solution(FILE *fichier_solution) {
	Action *a = pile_action->tete;
	fprintf(fichier_solution,"%d ",nombreVariable/2);
	while ( a ) {
		fprintf(fichier_solution,"%d ",a->num_variable);
		a = a->action_precedente;
	}
	printf("\n");
}

/* solution trouvée */
void solution() {
    printf("temps = %f\n", (float)(clock()-t1)/CLOCKS_PER_SEC);
    printf("nombre noeud : %d \n",pile_action->nombre_noeuds);
	FILE *fichier_solution = fopen("solution","w");
	printf("solution trouvée \n");
	afficher_solution(fichier_solution);
	exit(0);
}

void aucune_solution() {
	printf("probleme inconsistant \n");
	exit(0);
}
