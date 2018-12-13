#ifndef variable_h
#define variable_h

#include "structure.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "variable.h"
#include "clause.h"
#include "lecture.h"

void init_list_variable();

Variable init_variable(int n);

void afficher_variable(int num);

void afficher_liste_variable();

int inverse(int num_variable);

#endif
