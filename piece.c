// piece.c

#include <stdio.h>
#include <stdlib.h>
#include "couleurs.h"
#include "piece.h"

int gNbOrientations[ 7 ] = { 2,1,4,4,4,2,2 };	//pour chaque pièce, correspond au nombre d'orientations possibles




// trouverBordGauche
// utilité : pour une pièce, permet de trouver la première colonne non vide (bord gauche)
// paramètres d'entrée : pièce de format 4x4
// paramètres de sortie : numéro de colonne du bord gauche

int trouverBordGauche( int piece16[] ) {
	int bordGauche = 4;
	for( int ligne = 0; ligne < 4; ligne++ ) {			
		for( int colonne = 0; colonne < 4; colonne++ ) {
			if( piece16[ ligne * 4 + colonne ] != Aucune ) {
				if( colonne < bordGauche ) {
					bordGauche = colonne;
				}
			}
		}
	}
	return bordGauche;
}




// trouverBordDroit
// utilité : pour une pièce, permet de trouver la dernière colonne non vide (bord droit)
// paramètres d'entrée : pièce de format 4x4
// paramètres de sortie : numéro de colonne du bord droit

int trouverBordDroit( int piece16[] ) {
	int bordDroit = 0;
	for( int ligne = 0; ligne < 4; ligne++ ) {
		for( int colonne = 0; colonne < 4; colonne++ ) {
			if( piece16[ ligne * 4 + colonne ] != Aucune ) {
				if( colonne > bordDroit ) {
					bordDroit = colonne;
				}
			}
		}
	}
	return bordDroit;
}




// trouverLigneBas
// utilité : pour une pièce, permet de trouver la dernière ligne non vide (ligne du bas)
// paramètres d'entrée : pièce de format 4x4
// paramètres de sortie : numéro de la ligne du bas

int trouverLigneBas( int piece16[] ) {
	int ligneBas = 0;
	for( int ligne = 0; ligne < 4; ligne++ ) {
		for( int colonne = 0; colonne < 4; colonne++ ) {
			if( piece16[ ligne * 4 + colonne ] != Aucune ) {
				if( ligne > ligneBas ) {
					ligneBas = ligne;
				}
			}
		}
	}
	return ligneBas;
}




// trouverLigneHaut
// utilité : pour une pièce, permet de trouver la première ligne non vide (ligne du haut)
// paramètres d'entrée : pièce de format 4x4
// paramètres de sortie : numéro de la ligne du haut

int trouverLigneHaut( int piece16[] ) {
	int ligneHaut = 4;
	for( int ligne = 0; ligne < 4; ligne++ ) {
		for( int colonne = 0; colonne < 4; colonne++ ) {
			if( piece16[ ligne * 4 + colonne ] != Aucune ) {
				if( ligne < ligneHaut ) {
					ligneHaut = ligne;
				}
			}
		}
	}
	return ligneHaut;
}




// afficherPiecesOrientees
// utilité : pour une pièce, affiche ses différentes orientations
// paramètres d'entrée : liste des pièces et nom de la pièce à afficher
// paramètres de sortie : rien

void afficherPiecesOrientees( int listePieces[], enum NomPiece nomPiece ) {
	int* pieceReorientee[ 4 ]; //tableau contenant les différentes orientations de la pièce
	int centrePiece[ 4 ]; //tableau contenant le centre de chaque orientation de la pièce

	//création des tableaux et affichage des numéros d'orientation
	for( int numPiece = 0; numPiece < gNbOrientations[ nomPiece ]; numPiece++ ) {
		pieceReorientee[ numPiece ] = calloc( 16, sizeof( int ) );
		
		//crée un tableau contenant les différentes orientations de la pièce
		rotation( &listePieces[ ( int ) nomPiece * 8 ], numPiece * 90, pieceReorientee[ numPiece ] );

		//crée un second tableau contenant le centre de chaque orientation de la pièce
		centrePiece[ numPiece ] = trouverCentre( pieceReorientee[ numPiece ] );		

		//écrit les numéros de chaque orientation avec le nombre d'espaces approprié
		for( int i = 0; i < centrePiece[ numPiece ]; i++ ) {
			printf( " " );
		}
		printf( "%d", numPiece + 1 );		
		for( int i = centrePiece[ numPiece ] + 1; i < 4; i++ ) {
			printf( " " );
		}
		printf( " " );
	}
	printf( "\n" );
	//affiche ligne par ligne les orientations de la pièce
	for( int lignePiece = 1; lignePiece < 5; lignePiece++ ) {			
		for( int numPiece = 0; numPiece < gNbOrientations[ nomPiece ]; numPiece++ ) {
			afficherLignePiece( pieceReorientee[ numPiece ], lignePiece );
			printf( " " );
		}
		printf( "\n" );
	}
	printf( "\n" );
	for( int rang = 0; rang < gNbOrientations[ nomPiece ]; rang++ ) {
		free( pieceReorientee[ rang ] );
	}
}



// rotation
// utilité : permet de retourner la pièce souhaitée dans la direction indiquée
// paramètres d'entrée : piece de format 4x2, angle de l'orientation
// paramètres de sortie : la piece orientée de format 4x4

void rotation( int* piece8, int angle, int* pieceReorientee ) {
	int piece16[ 16 ];

	//conversion de la piece de format 4x2 en piece de format 4x4
	for( int rang = 0; rang < 8; rang++ ) {
		piece16[ rang ] = piece8[ rang ];
	}
	for( int rang = 8; rang < 16; rang++ ) {
		piece16[ rang ] = Aucune;
	}

	//applique la formule adaptée selon l'angle de rotation souhaité
	if( angle == 0 ) {				
		for( int rang = 0; rang < 16; rang++ ) {
			pieceReorientee[ rang ] = piece16[ rang ];
		}
	}
	else if( angle == 90 ) {
		for( int ligne = 0; ligne < 4; ligne++ ) {
			for( int colonne = 0; colonne < 4; colonne++ ) {
				pieceReorientee[ ligne * 4 + colonne ] = piece16[ ( 3 - colonne ) * 4 + ligne ];
			}
		}
	}
	else if( angle == 180 ) {
		for( int ligne = 0; ligne < 4; ligne++ ) {
			for( int colonne = 0; colonne < 4; colonne++ ) {
				pieceReorientee[ ligne * 4 + colonne ] = piece16[ ( 3 - ligne ) * 4 + ( 3 - colonne ) ];
			}
		}
	}
	else if( angle == 270 ) {
		for( int ligne = 0; ligne < 4; ligne++ ) {
			for( int colonne = 0; colonne < 4; colonne++ ) {
				pieceReorientee[ ligne * 4 + colonne ] = piece16[ colonne * 4 + ( 3 - ligne ) ];
			}
		}
	}
}




// trouverCentre
// utilité : permet de trouver le centre d'une pièce
// paramètres d'entrée : piece de format 4x4
// paramètres de sortie : centre de la pièce

int trouverCentre( int piece16[] ) {
	int bordGauche = 3;
	int bordDroit = 0;
	int largeur = 0;
	int centre;

	// Calcul des bords droit et gauche
	bordDroit = trouverBordDroit( piece16 );
	bordGauche = trouverBordGauche( piece16 );

	//détermine le centre en fonction de la largeur de la pièce
	largeur = bordDroit - bordGauche + 1;
	if( largeur > 2 ) {
		centre = bordGauche + 1;
	}
	else if( largeur == 1 ) {
		centre = bordGauche;
	}
	else {
		int nbColonne[ 2 ] = { 0,0 };			//si la largeur est de 2, place le centre au dessus de la colonne la plus remplie
		for( int ligne = 0; ligne < 4; ligne++ ) {
			for( int colonne = bordGauche; colonne < bordGauche + 2; colonne++ ) {
				if( piece16[ ligne * 4 + colonne ] != Aucune) {
					if( colonne == bordGauche ) {
						nbColonne[ 0 ]++;
					}
					else {
						nbColonne[ 1 ]++;
					}
				}
			}
		}
		if( nbColonne[ 0 ] >= nbColonne[ 1 ] ) {	//si les deux colonnes sont autant remplies l'une que l'autre on place le centre au dessus de la colonne gauche
			centre = bordGauche;
		}
		else {
			centre = bordDroit;
		}
	}
	return centre;
}




// afficherLignePiece
// utilité : affiche la ligne souhaitee d'une piece
// paramètres d'entrée : piece de format 4x4, numéro de la ligne
// paramètres de sortie : rien

void afficherLignePiece( int pieceReorientee[], int numLignePiece ) {
	int numLignePieceEnCours = 0;
	int ligneVide;

	//On ignore les lignes vides
	for( int ligne = 0; ligne < 4; ligne++ ) {
		ligneVide = 1; //par défaut la ligne est vide
		
		//on vérifie si la ligne est non vide
		for( int colonne = 0; colonne < 4; colonne++ ) {
			if( pieceReorientee[ ligne * 4 + colonne ] != Aucune ) {
				ligneVide = 0;
			}
		}
		
		//affiche ligne si elle n'est pas vide
		if( ligneVide == 0 ) {
			numLignePieceEnCours++;
			if( numLignePiece == numLignePieceEnCours ) {
				for( int colonne = 0; colonne < 4; colonne++ ) {
					if( pieceReorientee[ ligne * 4 + colonne ] != Aucune ) {
						char stringCouleur[5];
						sprintf( stringCouleur, "%d", pieceReorientee[ ligne*4 + colonne ] );
						couleur(stringCouleur);
						printf( "@" );
						couleur("0");
					}
					else {
						printf( " " );
					}
				}
				return;
			}
		}
	}
	printf( "    " );
}
