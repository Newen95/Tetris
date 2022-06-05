// tetris.c

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "tetris.h"
#include "piece.h"
#include "grille.h"
#include "classement.h"
#include "utilitaire.h"
#include "couleurs.h"

int tabDureeDecompteNiveau[ 3 ] = { DureeDecompteNiveau1,DureeDecompteNiveau2,DureeDecompteNiveau3 };
extern int gNbOrientations[ 7 ]; //défini dans piece.c

// initialiserPieces
// utilité : initialiser le tableau des 7 pièces du jeu
// paramètres d'entrée : tableau de format 4*2*7
// paramètres de sortie : tableau rempli

void initialiserPieces( int piece[] )
{
	//dans le tableau, les pièces sont stockées chacune sur 2 lignes et 4 colonnes
	//on utilise des tableaux 1D à la place de tableaux 2D

	for( int rang = 0; rang < 56; rang++ ) { // initialisation des cases vides (56=4*2*7)
		piece[ rang ] = Aucune;
	}

	// Pièce 1
	// @@@@@
	piece[ 0 ] = Cyan; piece[ 1 ] = Cyan; piece[ 2 ] = Cyan; piece[ 3 ] = Cyan;

	// Pièce 2
	// @@
	// @@
	piece[ 8 ] = Jaune; piece[ 9 ] = Jaune; piece[ 12 ] = Jaune; piece[ 13 ] = Jaune;

	// Pièce 3
	// @@@
	//  @
	piece[ 16 ] = Violet; piece[ 17 ] = Violet; piece[ 18 ] = Violet; piece[ 21 ] = Violet;

	// Pièce 4 
	// @@@
	// @
	piece[ 24 ] = Blanc; piece[ 25 ] = Blanc; piece[ 26 ] = Blanc; piece[ 28 ] = Blanc;

	// Pièce 5
	// @@@
	//   @
	piece[ 32 ] = Bleu; piece[ 33 ] = Bleu; piece[ 34 ] = Bleu; piece[ 38 ] = Bleu;

	// Pièce 6
	// @@
	//  @@
	piece[ 40 ] = Rouge; piece[ 41 ] = Rouge; piece[ 45 ] = Rouge; piece[ 46 ] = Rouge;

	// Pièce 7
	//  @@
	// @@
	piece[ 49 ] = Vert; piece[ 50 ] = Vert; piece[ 52 ] = Vert; piece[ 53 ] = Vert;
}




// tour
// utilité : appelle toutes les fonctions utilisées durant un tour du jeu
// paramètres d'entrée : grille de format 10*14, tableau des pièces, pointeur sur le score à incrémenter , niveau du jeu
// paramètres de sortie : score actuel

void tour( int grille[], int piece[], int* score, int niveau ) {
	enum NomPiece nomPiece;
	int orientationChoisie, colonneChoisie, ligneEmplacement, colonneMin, colonneMax, ligneHaut, ligneBas;
	int pieceReorientee[ 16 ];
	int orientationCorrecte = 0; //1 si l'orientation choisie est valide, 0 sinon
	int colonneCorrecte = 0; //1 si la colonne choisie est valide, 0 sinon

	//choix aléatoire d'une pièce parmi les 7 possibles	
	nomPiece = ( enum NomPiece ) ( rand() % 7 );
	
	//affichage du score actuel
	printf( "Score actuel : %d\n\n", *score );

	//affichage de la grille et des différentes orientations de la pièce
	affichageGrille( grille );
	afficherPiecesOrientees( piece, nomPiece );

	//choix de l'orientation de la pièce
	do {
		printf( "Choisissez l'orientation de la pièce : " );
		fflush( stdout );
		orientationChoisie = 0;
		if( decompte( tabDureeDecompteNiveau[niveau-1] ) == 1 ) { //le temps de saisie est limité
			scanf( "%d", &orientationChoisie );
			scanf( "%*[^\n]" );
			getchar();
			printf( "\n" );
			if( orientationChoisie >= 1 && orientationChoisie <= gNbOrientations[ nomPiece ] ) {
				orientationCorrecte = 1;
			}
			else {
				printf( "L'orientation choisie n'est pas valide, veuillez recommencer.\n\n" );
			}
		}
		else
		{
			//l'utilisateur n'a pas choisi à temps, la sélection de l'orientation est donc aléatoire
			if(gNbOrientations[ nomPiece ] > 1){
				orientationChoisie = 1 + rand() % ( gNbOrientations[ nomPiece ]-1 );
			}
			else{
				orientationChoisie = 1;
			}
			printf( "%d\n", orientationChoisie );
			orientationCorrecte = 1;
		}
	} while( orientationCorrecte == 0 );
	orientationChoisie = ( orientationChoisie - 1 ) * 90;	//90 degrès

	//création des pièces orientées
	rotation( &piece[ ( int )nomPiece*8 ], orientationChoisie, pieceReorientee );

	//calcul de la première et de la denière colonne pouvant être choisie pour la pièce orientée
	colonneMin = trouverCentre( pieceReorientee ) - trouverBordGauche( pieceReorientee ) + 1;
	colonneMax = trouverCentre( pieceReorientee ) - trouverBordDroit( pieceReorientee ) + NbColonneGrille;

	//choix de la colonne où placer la pièce
	do {
		printf( "Choisissez la colonne où placer la pièce (de %d à %d) : ", colonneMin, colonneMax );
		fflush( stdout );

		if( decompte( tabDureeDecompteNiveau[niveau-1] ) == 1 ) { //le temps de saisie est limité
			scanf( "%d", &colonneChoisie );
			scanf( "%*[^\n]" );
			getchar();
			printf( "\n" );
			if( colonneChoisie >= colonneMin && colonneChoisie <= colonneMax ) {
				colonneCorrecte = 1;
			}
			else {
				printf( "La colonne choisie n'est pas valide, veuillez recommencer.\n\n" );
			}
		}
		else
		{
			//l'utilisateur n'a pas choisi à temps, la sélection de la colonne est donc aléatoire
			colonneChoisie = colonneMin + rand() % ( NbColonneGrille - colonneMin );
			printf( "%d\n", colonneChoisie );
			colonneCorrecte = 1;
		}
	} while( colonneCorrecte == 0 );
	colonneChoisie--;

	//calcul de ligne où placer le bas de la pièce
	ligneEmplacement = positionPiece( grille, pieceReorientee, colonneChoisie );

	//placement de la pièce sur la grille à l'emplacement calculé
	remplissageGrille( grille, pieceReorientee, colonneChoisie, ligneEmplacement );

	//les lignes pleines situées au niveau de la pièce sont supprimées
	ligneHaut = trouverLigneHaut( piece ); //première ligne située au niveau de la pièce
	ligneBas = trouverLigneBas( piece ); //dernière ligne située au niveau de la pièce
	*score += supprimerLigne( grille, ligneEmplacement + ligneHaut, ligneEmplacement + ligneBas ); //le score est incrémenté du nombre de lignes supprimées
}




// main
// utilité : fonction de démarrage du programme
// paramètres d'entrée : rien
// paramètres de sortie : rien

int main() {
	int termine = 0; //1 quand la partie est finie, 0 sinon
	int score = 0; //score du joueur
	srand( time( NULL ) ); //initialise la fonction aléatoire
	
	//Remarque : tous les tableaux 2D sont remplacés par des tableaux 1D selon le principe :
	//tab2D[colonne][ligne] => tab1D[(ligne * nbColonnes) +  colonne]

	//initialisation des 7 pièces du jeu
	int piece[ 7 * 8 ];		//différentes pièces sous forme d'un tableau à une dimension
	initialiserPieces( piece );

	int grille[ NbLigneGrille * NbColonneGrille ] = { 0 }; //grille sous forme d'un tableau à une dimension

	printf( "Bienvenue dans Tetris !\n\n\n" );

	//choix du niveau du jeu (3 niveaux)
	int niveau = 0; 
	int niveauCorrect = 0;
	do {
		printf( "Choisissez un niveau de difficulté :\n1) Facile (%d secondes)\n2) Normal (%d secondes)\n3) Difficile (%d secondes)\n\n", tabDureeDecompteNiveau[ 0 ], tabDureeDecompteNiveau[ 1 ], tabDureeDecompteNiveau[ 2 ] );
		scanf( "%d", &niveau );
		scanf( "%*[^\n]" );
		getchar();
		printf( "\n" );
		if( niveau >= 1 && niveau <= 3 ) {
			niveauCorrect = 1;
		}
		else {
			printf( "Le numéro chosi n'est pas valide. Veuillez recommencer.\n\n" );
		}

	} while(niveauCorrect == 0);


	//demande à l'utilisateur de choisir son pseudo et vérifie que celui-ci n'est pas trop long
	char pseudo[ 10 ], testPseudo[ 10 ];
	int pseudoCorrect = 0;
	do {

		printf( "Choisissez votre pseudo (max 10 caractères): " );			
		scanf( "%s", testPseudo );
		printf( "\n" );
		if( strlen( testPseudo ) <= 10 ) {
			strcpy( pseudo, testPseudo );
			pseudoCorrect = 1;
			printf( "Votre pseudo est %s.\n\n\n", pseudo );
		}
		else {
			printf( "Votre pseudo est trop long, veuillez recommencer (max 10 caractères).\n" );
		}
	} while( pseudoCorrect == 0 );

	//tours du jeu
	while( termine == 0 ) {
		tour( grille, piece, &score, niveau );
		if( testerFin( grille ) == 1 ) {
			printf( "La partie est terminée !\n\n" );
			printf( "Votre score finale est : %d\n\n", score );
			termine = 1;
		}
	}

	//affichage du classement
	stockageScore( pseudo, score ); //stocke le score du joueur dans classement.txt

	Joueur* tabJoueurs = NULL;
	int nbLignes = 0;
	lectureScore( &tabJoueurs, &nbLignes ); //lecture des joueurs (pseudo et score) sockés dans classement.txt
	afficherMeilleursScores( tabJoueurs, nbLignes ); //affiche les 10 meilleurs scores
	printf( "\n\n" );
	if( tabJoueurs != NULL )
		free( tabJoueurs );

}






