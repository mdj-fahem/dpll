#ifndef utile_h
#define utile_h

#include "structure.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "variable.h"
#include "clause.h"
#include "lecture.h"
#include "dpll.h"
#include <time.h>

clock_t t1;

int mono_litteral();

int litteral_pur();

int prochaine_variable();

int prochaine_variable_a_choisir(Action *a);

int enlever_clauses_satisfaite(Action *a);

void enlever_les_litteraux_inverses(Action *a);

int restaurer_clauses(Action *a);

void restaurer_litteraux(Action *a);

void afficher_solution();

void solution();

void aucune_solution();

#endif
