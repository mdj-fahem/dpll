#include "dpll.h"

Action *init_action(int var) {
	Action *a = malloc(sizeof(a));
	a->num_variable = var;
	a->type_branche = VIDE;
	a->action_precedente = NULL;
	return a;
}

void init_pile_action() {
	nombre_clauses_satisfaite = 0;
	CLAUSE_VIDE = 0;
	pile_action = malloc(sizeof(pile_action));
	pile_action->tete = NULL;
	pile_action->nombre_noeuds = 0;
	pile_action->niveau = 0;
}

void empiler_action(Action *a) {
	pile_action->niveau++;
	//printf("empiler action var %d branche %d niveau %d\n",variables_courante,a->type_branche, pile_action->niveau);
	nombre_clauses_satisfaite+= enlever_clauses_satisfaite(a);
	if ( liste_variable[inverse(variables_courante)].nombre_occurence > 0 )
		enlever_les_litteraux_inverses(a);
	/* empiler l'action */
	a->action_precedente = pile_action->tete;
	pile_action->tete = a;
	pile_action->nombre_noeuds+=1;
}

int depiler_action(){
	Action *a = pile_action->tete;
	
	/* si on est a la première variable instancier et on a parcouru toute les branche possible alors arreter */
	if ( pile_action->tete->type_branche >= BRANCHE2 && pile_action->niveau == 1 )
		aucune_solution();
	//printf("dépiler action var %d branche %d niveau %d\n",variables_courante,a->type_branche, pile_action->niveau);
	
	/* remettre les clauses supprimer */
	nombre_clauses_satisfaite-= restaurer_clauses(a);
	/* remettre les inverses enlever */
	if (liste_variable[inverse(variables_courante)].nombre_occurence > 0 )
		restaurer_litteraux(a);
	
	/* dépiler l'action */
	pile_action->tete = pile_action->tete->action_precedente;
	pile_action->niveau--;
	variables_courante = pile_action->tete->num_variable;
	a = pile_action->tete;
	//printf("type branche : %d\n",pile_action->tete->type_branche);
	switch  (a->type_branche ) {
		case BRANCHE1:
			/* remettre les clauses supprimer */
			nombre_clauses_satisfaite-= restaurer_clauses(a);
			/* remettre les inverses enlever */
			if (liste_variable[inverse(variables_courante)].nombre_occurence > 0 )
				restaurer_litteraux(a);
			pile_action->tete->type_branche = BRANCHE2;
			//printf("prendre l'inverse de %d qui est %d \n",variables_courante, inverse(variables_courante));
			//printf("niveau : %d <========================================================\n",pile_action->niveau);
			variables_courante = inverse(variables_courante);
			pile_action->tete = pile_action->tete->action_precedente;
			return BRANCHE2;
		case BRANCHE2:
			depiler_action();
			break;
		case MONO:
			depiler_action();
			break;
		case PUR:
			depiler_action();
			break;
		default:
			break;
	}
	return BRANCHE2;
}

void dpll(Clause *f) {
	init_pile_action();
	//printf("recherche de solution .... en cours .... \n");
	while (1) {
		Action *a = init_action(VIDE);
		//printf("nombre clauses satisfaite = %d , %d\n",nombre_clauses_satisfaite, CLAUSE_VIDE);
		if ( nombre_clauses_satisfaite == nombreClause ) solution(); /* résolu */
		if ( CLAUSE_VIDE ) { /* une clauses est vide alors remonter */
			CLAUSE_VIDE = 0;
			a->type_branche =  depiler_action();
		}
		else /* sinon chercher la prochaine variable a mettre a vrai */
			variables_courante = prochaine_variable_a_choisir(a);
 		//printf("variable courante %d \n",variables_courante);
 		if ( variables_courante == 0 ) depiler_action();
 		a->num_variable = variables_courante;
		empiler_action(a);
	}
	
}
