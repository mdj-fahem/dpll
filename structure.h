#ifndef structure_h
#define structure_h

typedef struct Variable Variable;
typedef struct Clause Clause;

struct Variable {
    int numero;
    int nombre_occurence;
    int nombre_occurence_courant;
    int enleve;
    int pur;
    int *clauses; /* liste des clause où la variable apparait */
};

struct Clause {
	int satisfaite; /* VRAI(1) OU FAUX(0) */
	int num_clause;
	int taille;
	int taille_courante;
    int *variables;
    int satisfaite_par;
};

Variable *liste_variable;

Clause *formule; /* tableau de clause */

typedef struct Action Action;
typedef struct Pile_Action Pile_Action;

/* une action est un noeud de l'arbre de recherche de solutions */
struct Action {
	int num_variable;
	int type_branche;
	Action *action_precedente;
};

/* la pile des actions */
struct Pile_Action {
	int nombre_noeuds;
	int niveau;
    Action *tete;
};

Pile_Action *pile_action;

#endif
