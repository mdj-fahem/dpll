#include "lecture.h"
#include <ctype.h>

/****************************************************************************
 *****        lit la formule a partir du fichier 'formule' ******************
 * *************************************************************************/
void lire_la_formule() {
	FILE *fichier = fopen("formule","r");
	fscanf(fichier,"%d",&nombreVariable);
	nombreVariable = nombreVariable*2;
	fscanf(fichier,"%d",&nombreClause);
	init_list_variable();
	init_formule();
	/* lire toute les clause */
	int i=0, c;
	while(! feof(fichier) ){
		c = -1;
		while ( c != 0 ) {
			fscanf(fichier,"%d",&c);
			if ( c!=0 ) ajout_variable(i,c);
		}
		i++;
		if ( i==nombreClause ) break;
	}
	fclose(fichier);
}

/*************************************************************
 ********* fonction qui affiche la formule                 ***
 ************************************************************/
 
void afficher_la_formule() {
	printf("nb_variable : %d - nb_clause : %d\n",nombreVariable,nombreClause);
	afficher_liste_variable(liste_variable);
	afficher_formule(formule);
}

