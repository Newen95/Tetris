// classement.h

#ifndef CLASSEMENT_H
#define CLASSEMENT_H

typedef struct {
	char pseudo[ 10 ];
	int score;
}Joueur;

void stockageScore( char pseudo[], int score );
void lectureScore( Joueur** tabJoueurs, int* nbLignes );
int comparaisonScore( const void* case1, const void* case2 );
void afficherMeilleursScores( Joueur* tabJoueurs, int nbLignes );

#endif