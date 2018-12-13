#ifndef dpll_h
#define dpll_h
#include "structure.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "variable.h"
#include "clause.h"
#include "lecture.h"
#include "utile.h"

#define VIDE 0
#define BRANCHE1 1
#define BRANCHE2 2
#define MONO 4
#define PUR 3


int nombre_clauses_satisfaite, variables_courante, CLAUSE_VIDE;

Action *init_action();

void init_pile_action();

void empiler_action();

int depiler_action();

void dpll(Clause *f);

#endif
