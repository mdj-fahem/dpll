#include "structure.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "variable.h"
#include "clause.h"
#include "utile.h"
#include "lecture.h"
#include <time.h>

int main() {
	/* lire la formule */
	lire_la_formule();
	
	float temps;
	t1 = clock();    
	/* trouver un modele avec DPLL */
	dpll(formule);
	
	/* libérer la mémoire */
	free(liste_variable);
	free(formule);
	return 0;
}
