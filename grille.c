// grille.c

#include <stdio.h>
#include <stdlib.h>
#include "couleurs.h"
#include "grille.h"
#include "piece.h"

// affichageGrille
// utilit� : affiche la grille de jeu
// param�tres d'entr�e : grille de format 10x14
// param�tres de sortie : rien

void affichageGrille( int grille[] ) {
	printf( " 1 2 3 4 5 6 7 8 9 10\n" );

	//parcourt le tableau � l'exception des 4 premi�res lignes (lignes cach�es)
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
// utilit� : retourne la ligne o� placer la pi�ce pass�e en param�tre
// param�tres d'entr�e : grille de format 10x14, pi�ce de format 4x4
// param�tres de sortie : ligne o� placer la pi�ce

int positionPiece( int grille[], int piece16[], int colonneChoisie ) {
	int ligneFinale = NbLigneGrille - 1;
	int centrePiece = trouverCentre( piece16 );
	int collision = 0;
	int xCasePiece = 0;	//coordonn�e horizontale d'une case de la pi�ce projet�e sur la grille
	int yCasePiece = 0; //coordonn�e verticale d'une case de la pi�ce projet�e sur la grille

	//pour chaque ligne de la grille on regarde si la projection de la pi�ce sur la grille rentre en colision avec les �l�ments remplis de la grille
	for( int ligneGrille = 0; ( ligneGrille < NbLigneGrille ) && ( collision == 0 ); ligneGrille++ ) {
		for( int lignePiece = 0; ( lignePiece < 4 ) && ( collision == 0 ); lignePiece++ ) {
			for( int colonnePiece = 0; ( colonnePiece < 4 ) && ( collision == 0 ); colonnePiece++ ) {
				xCasePiece = colonneChoisie - centrePiece + colonnePiece;
				yCasePiece = ligneGrille + lignePiece;
				//on regarde si la pi�ce projet�e sort du tableau
				if( ( yCasePiece > NbLigneGrille - 1 ) && ( piece16[ lignePiece * 4 + colonnePiece ] != Aucune ) ) {
					collision = 1; //collision de la pi�ce
					ligneFinale = ligneGrille - 1; //on retient la ligne du dessus
				}
				else {
					if( yCasePiece < NbLigneGrille ) {
						if( ( grille[ yCasePiece * NbColonneGrille + xCasePiece ] != Aucune ) && ( piece16[ lignePiece * 4 + colonnePiece ] != Aucune ) ) {
							collision = 1; //collision de la pi�ce
							ligneFinale = ligneGrille - 1; //on retient la ligne du dessus
						}
					}
				}
			}
		}
	}

	return ligneFinale;
}




// remplissageGrille
// utilit� : reporte la pi�ce sur la grille � un emplacement donn� en param�tre
// param�tres d'entr�e : grille de format 10x14, pi�ce de format 4x4, colonne choisie, ligne de report de la pi�ce
// param�tres de sortie : grille modifi�e

void remplissageGrille( int grille[], int piece16[], int colonneChoisie, int ligneEmplacement ) {
	int xCasePiece = 0;
	int yCasePiece = 0;
	int centrePiece = trouverCentre( piece16 );
	for( int lignePiece = 0; lignePiece < 4; lignePiece++ ) {
		for( int colonnePiece = 0; colonnePiece < 4; colonnePiece++ ) {
			//coordon�es de projection de la pi�ce
			xCasePiece = colonneChoisie - centrePiece + colonnePiece;
			yCasePiece = ligneEmplacement + lignePiece;
			
			//copie de la pi�ce sur la grille
			if( piece16[ lignePiece * 4 + colonnePiece ] != Aucune ) {
				grille[ yCasePiece * NbColonneGrille + xCasePiece ] = piece16[ lignePiece * 4 + colonnePiece ];
			}
		}
	}
}




// decalerLignesAuDessus
// utilit� : permet de d�caler d'une ligne vers le bas les lignes situ�es au-dessus de la ligne � supprimer
// param�tres d'entr�e : grille de format 10x14, la ligne plaine � supprimer
// param�tres de sortie : grille modifi�e

void decalerLignesAuDessus( int grille[], int ligneASupprimer ) {
	for( int ligne = ligneASupprimer; ligne > 0; ligne-- ) {
		for( int colonne = 0; colonne < NbColonneGrille; colonne++ ) {
			grille[ ligne * NbColonneGrille + colonne ] = grille[ ( ligne - 1 ) * NbColonneGrille + colonne ];
		}
	}
}



// supprimerLigne
// utilit� : permet de supprimer les lignes pleines situ�es au niveau de la pi�ce dans la grille
// param�tres d'entr�e : grille de format 10x14, premi�re ligne � tester (ligneHaut), derni�re ligne � tester (ligneBas), 
// param�tres de sortie : grille modifi�e

int supprimerLigne( int grille[], int ligneHaut, int ligneBas ) {
	int lignePleine; //1 si la ligne est pleine, 0 sinon
	int nbLignesSupprimees = 0;

	//on parcourt les lignes situ�es au niveau de la pi�ce
	for( int ligne = ligneHaut; ligne <= ligneBas; ligne++ ) {
		lignePleine = 1; //ligne pleine par d�faut
		for( int colonne = 0; ( colonne < NbColonneGrille ) && ( lignePleine == 1 ); colonne++ ) {
			if( grille[ ligne * NbColonneGrille + colonne ] == Aucune ) {
				lignePleine = 0; //la ligne n'est pas pleine
			}
		}

		//si la ligne est pleine on d�cale d'une ligne vers le bas les lignes du dessus
		if( lignePleine == 1 ) {
			decalerLignesAuDessus( grille, ligne );
			nbLignesSupprimees++;
		}
	}
	return nbLignesSupprimees;
}




int testerFin( int grille[] ) {
	for( int colonne = 0; colonne < NbColonneGrille; colonne++ ) {
		if( grille[ 3 * NbColonneGrille + colonne ] != Aucune ) {	//ligne 3 = premi�re ligne cach�e
			return 1;
		}
	}
	return 0;
}

