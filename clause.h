#ifndef clause_h
#define clause_h
#include "structure.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "variable.h"
#include "clause.h"
#include "lecture.h"



void init_formule();

Clause init_clause(int num);

void ajout_variable(int num_clause, int num_var);

void afficher_clause(int num_clause);

void afficher_formule();



#endif
