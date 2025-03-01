// grille.c

#include <stdio.h>
#include <stdlib.h>
#include "couleurs.h"
#include "grille.h"
#include "piece.h"

// affichageGrille

// utilité : affiche la grille de jeu
// paramètres d'entrée : grille de format 10x14
// paramètres de sortie : rien

void affichageGrille( int grille[] ) {
	printf( " 1 2 3 4 5 6 7 8 9 10\n" );

	// parcourt le tableau à l'exception des 4 premières lignes (lignes cachées)
	for( int ligne = 4; ligne < NbLigneGrille; ligne++ ) {
		for( int colonne = 0; colonne < NbColonneGrille; colonne++ ) {
			if( grille[ ligne * NbColonneGrille + colonne ] != Aucune ) {
				printf( "|" );

				char stringCouleur[ 5 ];
				sprintf( stringCouleur, "%d", grille[ ligne * NbColonneGrille + colonne ] );
				couleur( stringCouleur );
				printf( "@" );
				couleur( "0" );
			}
			else {
				printf( "| " );
			}
		}
		printf( "|\n" );
	}
	printf( "\n" );
}


// positionPiece
// utilité : retourne la ligne où placer la pièce passée en paramètre
// paramètres d'entrée : grille de format 10x14, pièce de format 4x4
// paramètres de sortie : ligne où placer la pièce

int positionPiece( int grille[], int piece16[], int colonneChoisie ) {
	int ligneFinale = NbLigneGrille - 1;
	int centrePiece = trouverCentre( piece16 );
	int collision = 0;
	int xCasePiece = 0;
	int yCasePiece = 0;

	// vérifie les collisions de la pièce projetée sur la grille
	for( int ligneGrille = 0; ( ligneGrille < NbLigneGrille ) && ( collision == 0 ); ligneGrille++ ) {
		for( int lignePiece = 0; ( lignePiece < 4 ) && ( collision == 0 ); lignePiece++ ) {
			for( int colonnePiece = 0; ( colonnePiece < 4 ) && ( collision == 0 ); colonnePiece++ ) {
				xCasePiece = colonneChoisie - centrePiece + colonnePiece;
				yCasePiece = ligneGrille + lignePiece;
				if( ( yCasePiece > NbLigneGrille - 1 ) && ( piece16[ lignePiece * 4 + colonnePiece ] != Aucune ) ) {
					collision = 1;
					ligneFinale = ligneGrille - 1;
				}
				else {
					if( yCasePiece < NbLigneGrille ) {
						if( ( grille[ yCasePiece * NbColonneGrille + xCasePiece ] != Aucune ) && ( piece16[ lignePiece * 4 + colonnePiece ] != Aucune ) ) {
							collision = 1;
							ligneFinale = ligneGrille - 1;
						}
					}
				}
			}
		}
	}

	return ligneFinale;
}


// remplissageGrille
// utilité : reporte la pièce sur la grille à un emplacement donné
// paramètres d'entrée : grille de format 10x14, pièce de format 4x4, colonne choisie, ligne de report de la pièce
// paramètres de sortie : grille modifiée

void remplissageGrille( int grille[], int piece16[], int colonneChoisie, int ligneEmplacement ) {
	int xCasePiece = 0;
	int yCasePiece = 0;
	int centrePiece = trouverCentre( piece16 );
	for( int lignePiece = 0; lignePiece < 4; lignePiece++ ) {
		for( int colonnePiece = 0; colonnePiece < 4; colonnePiece++ ) {
			xCasePiece = colonneChoisie - centrePiece + colonnePiece;
			yCasePiece = ligneEmplacement + lignePiece;
			if( piece16[ lignePiece * 4 + colonnePiece ] != Aucune ) {
				grille[ yCasePiece * NbColonneGrille + xCasePiece ] = piece16[ lignePiece * 4 + colonnePiece ];
			}
		}
	}
}


// decalerLignesAuDessus
// utilité : décale d'une ligne vers le bas les lignes situées au-dessus de la ligne à supprimer

void decalerLignesAuDessus( int grille[], int ligneASupprimer ) {
	for( int ligne = ligneASupprimer; ligne > 0; ligne-- ) {
		for( int colonne = 0; colonne < NbColonneGrille; colonne++ ) {
			grille[ ligne * NbColonneGrille + colonne ] = grille[ ( ligne - 1 ) * NbColonneGrille + colonne ];
		}
	}
}


// supprimerLigne
// utilité : supprime les lignes pleines de la grille

int supprimerLigne( int grille[], int ligneHaut, int ligneBas ) {
	int nbLignesSupprimees = 0;
	for( int ligne = ligneHaut; ligne <= ligneBas; ligne++ ) {
		int lignePleine = 1;
		for( int colonne = 0; ( colonne < NbColonneGrille ) && ( lignePleine == 1 ); colonne++ ) {
			if( grille[ ligne * NbColonneGrille + colonne ] == Aucune ) {
				lignePleine = 0;
			}
		}
		if( lignePleine == 1 ) {
			decalerLignesAuDessus( grille, ligne );
			nbLignesSupprimees++;
		}
	}
	return nbLignesSupprimees;
}


int testerFin( int grille[] ) {
	for( int colonne = 0; colonne < NbColonneGrille; colonne++ ) {
		if( grille[ 3 * NbColonneGrille + colonne ] != Aucune ) {
			return 1;
		}
	}
	return 0;
}
