// classement.c

#include <stdio.h>
#include <stdlib.h>
#include "classement.h"

// stockageScore
// utilit� : stocke le pseudo du joueur avec son score au format "pseudo" \t "score" dans le fichier classement.txt
// param�tres d'entr�e : pseudo et score
// param�tres de sortie : rien

void stockageScore( char pseudo[], int score ) {
	char stringScore[ 5 ];
	sprintf( stringScore, "%d", score );
	FILE* fichierClassement = fopen( "classement.txt", "a+" );		//ouvre le fichier en mode �criture
	if( fichierClassement == NULL ) {
		printf( "Impossible d'ouvrir le fichier\n" );
	}
	fprintf( fichierClassement, "%s\t%s\n", pseudo, stringScore );		//�crit le pseudo et le score
	fclose( fichierClassement );	//ferme le fichier
}




// lectureScore
// utilit� : lit le contenu du fichier classement.txt et cr�e un tableau des joueurs avec leur score 
// param�tres d'entr�e : pointeur sur le tableau des joueurs � cr�er, pointeur sur le nombre de joueurs (= nombre de lignes du fichier)
// param�tres de sortie : tableau des joueurs rempli

void lectureScore( Joueur** tabJoueurs, int* nbLignes) {
	
	if( nbLignes == NULL ) {
		return;
	}

	//ouvre le fichier classement.txt en lecture
	FILE* fichierClassement = fopen( "classement.txt", "r+" );
	if( fichierClassement == NULL ) {
		printf( "Impossible d'ouvrir le fichier\n" );
		return;
	}

	//calcul du nombre de lignes dans le fichier
	char ligne[ 20 ];
	while( fgets( ligne, 20, fichierClassement ) != NULL ) {
		(*nbLignes)++;
	}

	rewind(fichierClassement); //revenir au d�but du fichier

	//cr�ation d'un tableau de joueurs avec leur score et leur pseudo
	*tabJoueurs = malloc( *nbLignes * sizeof( Joueur ) );
	if( *tabJoueurs == NULL ) {
		return;
	}

	int numLigne = 0;
	while( fgets( ligne, 20, fichierClassement ) != NULL ) {	// 20 = nbre max de caract�res d'une ligne
		sscanf( ligne, "%s\t%d", (*tabJoueurs)[numLigne].pseudo, &(*tabJoueurs)[numLigne].score);
		numLigne++;
	}

	fclose( fichierClassement );		//ferme le fichier
}




// comparaisonScore
// utilit� : compare le score de 2 joueurs
// param�tres d'entr�e : pointeur sur une premi�re case du tableau, pointeur sur une deuxi�me case du tableau
// param�tres de sortie : r�sultat de la comparaison

int comparaisonScore( const void* case1, const void* case2 ) {
	Joueur* joueur1 = (Joueur*) case1;
	Joueur* joueur2 = (Joueur*) case2;
	return joueur2->score - joueur1->score; //si r�sultat > 0 alors le score du joueur 2 est sup�rieur au score du joueur 1 (classement dans l'ordre d�croissant)
}




// afficherMeilleursScores
// utilit� : affiche les 10 meilleurs scores dans l'ordre d�croissant
// param�tres d'entr�e : tableau des joueurs avec leur score, nombre de joueurs (= nombre de lignes)
// param�tres de sortie : rien

void afficherMeilleursScores( Joueur* tabJoueurs, int nbLignes ) {
	int nbLignesAffichees = 10;
	if( nbLignes < 10 ) {
		nbLignesAffichees = nbLignes;
	}
	printf( "Classement des %d meilleurs scores :\n\n", nbLignesAffichees );
	qsort( tabJoueurs, nbLignes, sizeof( Joueur ), comparaisonScore );
	for( int i = 0; i < nbLignesAffichees; i++ ) {
		printf("%-11d%-11s%d\n",i+1,tabJoueurs[i].pseudo, tabJoueurs[ i ].score );
	}
}