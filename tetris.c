#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

#define NbColonneGrille 10
#define NbLigneGrille 14




int trouverCentre(int piece16[]) {	//fonction permettant de trouver le centre d'une fonction entrée en paramètres
	int bordGauche = 3;
	int bordDroit = 0;
	int largeur = 0;
	int centre;
	for (int ligne = 0; ligne < 4; ligne++) {			//boucle parcourant la piece pour déterminer les bords de la pièce
		for (int colonne = 0; colonne < 4; colonne++) {
			if (piece16[ligne*4+colonne]==1) {
				if (colonne<bordGauche) {
					bordGauche = colonne;
				}
				if (colonne > bordDroit) {
					bordDroit = colonne;
				}
			}
		}
	}
	largeur = bordDroit - bordGauche + 1;		//détermine le centre en fonction de la largeur de la pièce
	if (largeur > 2) {
		centre = bordGauche + 1;
	}
	else if (largeur == 1) {
		centre = bordGauche;
	}
	else {
		int nbColonne[2] = { 0,0 };			//si la largeur est de 2 place le centre au dessus de la colonne la plus remplie
		for (int ligne = 0; ligne < 4; ligne++) {
			for (int colonne = bordGauche; colonne < bordGauche + 2; colonne++) {
				if (piece16[ligne * 4 + colonne] == 1) {
					if (colonne == bordGauche) {
						nbColonne[0]++;
					}
					else {
						nbColonne[1]++;
					}
				}
			}
		}
		if (nbColonne[0] >= nbColonne[1]) {	//si les deux colonnes sont autant remplies l'une que l'autre on place le centre au dessus de la colonne gauche
			centre = bordGauche;
		}
		else {
			centre = bordDroit;
		}
	}
	return centre;
}



void afficherLignePiece(int pieceReorientee[], int numLignePiece) {		//
	int numLignePieceEnCours = 0;
	int ligneVide;
	for (int ligne = 0; ligne < 4; ligne++) {
		ligneVide = 1;
		for (int colonne = 0; colonne < 4; colonne++) {
			if (pieceReorientee[ligne * 4 + colonne] == 1) {
				ligneVide = 0;

			}
		}
		//if (ligneVide == 0) {
			numLignePieceEnCours++;
			if (numLignePiece == numLignePieceEnCours) {
				for (int colonne = 0; colonne < 4; colonne++) {
					if (pieceReorientee[ligne * 4 + colonne] == 1) {
						printf("@");
					}
					else {
						printf(" ");
					}
				}
			}
		//}
	}
}




void rotation(int* piece8, int angle, int* pieceReorientee) {
	int piece16[16];
	for (int rang = 0; rang < 8; rang++) {
		piece16[rang] = piece8[rang];
	}
	for (int rang = 8; rang < 16; rang++) {
		piece16[rang] = 0;
	}
	if (angle == 0) {
		for (int rang = 0; rang < 16; rang++) {
			pieceReorientee[rang] = piece16[rang];
		}
	}
	else if (angle == 90) {
		for (int ligne = 0; ligne < 4; ligne++) {
			for (int colonne = 0; colonne < 4; colonne++) {
				pieceReorientee[ligne * 4 + colonne] = piece16[(3 - colonne) * 4 + ligne];
			}
		}
	}
	else if (angle == 180) {
		for (int ligne = 0; ligne < 4; ligne++) {
			for (int colonne = 0; colonne < 4; colonne++) {
				pieceReorientee[ligne * 4 + colonne] = piece16[(3 - ligne) * 4 + (3 - colonne)];
			}
		}
	}
	else if (angle == 270) {
		for (int ligne = 0; ligne < 4; ligne++) {
			for (int colonne = 0; colonne < 4; colonne++) {
				pieceReorientee[ligne * 4 + colonne] = piece16[colonne * 4 + (3 - ligne)];
			}
		}
	}
}



//fonction remlissage tableau
	//prend la partie concernée du tableau final
	//reporte chaque caractère du tableau intermédiaire dans le tableau final




//fonction placement pièce
	//parcourir le tableau final
	//si la ligne est vide descend d'une ligne
	//si il y a un caractère sur la ligne regarde s'il y a collision avec la pièce
	//quand il y a collision avec la pièce revient à la ligne précédente
	//appelle la fonction remplissage tableau




//fonction décompte
	//demarre à 10
	//chaque seconde retire 1




void affichageGrille(int grille[]) {
	printf(" 1 2 3 4 5 6 7 8 9 10\n");
	for (int ligne = 4; ligne < NbLigneGrille; ligne++) {
		for (int colonne = 0; colonne < NbColonneGrille; colonne++) {
			if (grille[ligne * NbColonneGrille + colonne] == 1) {
				printf("|@");
			}
			else {
				printf("| ");
			}
		}
		printf("|\n");
	}
	printf("\n");
}
//parcourt le tableau final à l'exception des quatre premières lignes
//place un "|" puis marque le caractère correspondant
//à la fin de chaque ligne place un "|" supplémentaire

/*void affichageOrientation1(int piece[], int indiceDepart) {
	int* pieceReorientee = NULL;
	pieceReorientee = calloc(16, sizeof(int));
	rotation(&piece[indiceDepart], 90, pieceReorientee);
	for (int ligne = 0; ligne < 4; ligne++) {
		int videLigne = 1;
		for (int rang = 0; rang < 4; rang++) {
			if (pieceReorientee[ligne * 4 + rang] == 1) {
				videLigne = 0;
			}
		}
		if (videLigne == 0) {
			for (int colonne = 0; colonne < 4; colonne++) {
				int videColonne = 1;
				for (int rang = 0; rang < 4; rang++) {
					if (pieceReorientee[rang * 4 + colonne] == 1) {
						videColonne = 0;
					}
				}
				if(videColonne == 0){
					if (pieceReorientee[ligne * 4 + colonne] == 1) {
						printf("@");
					}
					else {
						printf(" ");
					}
				}
			}
			printf("\n");
		}
	}
	free(pieceReorientee);

	//affiche les nombres correspondant aux choix
	//appelle la fonction rotation
	//affiche les pièces réorientées
}*/


void afficherPieceOrientee(int piece[], int indiceDepart) {
	int* pieceReorientee[4];
	int centrePiece[4];
	int espace[4];
	for (int rang = 0; rang < 4; rang++) {
		pieceReorientee[rang] = calloc(16, sizeof(int));
		rotation(&piece[indiceDepart], rang*90, pieceReorientee[rang]);
		centrePiece[rang] = trouverCentre(pieceReorientee[rang]);
		for (int i = 0; i < centrePiece[rang];i++) {
			printf(" ");
		}
		printf("%d",rang+1);
		for (int i = centrePiece[rang] + 1; i < 4 - centrePiece[rang] + 1; i++) {
			printf(" ");
		}
		printf(" ");
	}
	printf("\n");
	for (int lignePiece = 1; lignePiece < 5; lignePiece++) {
		for (int piece = 0; piece < 4; piece++) {
			afficherLignePiece(pieceReorientee[piece], lignePiece);
			printf(" ");
		}
		printf("\n");
	}
}



//fonction stockage score
	//ouvre le fichier classement en mode écriture
	//inscrit le score du joueur à la suite des autres
	//ferme le fichier




//fonction meilleurs scores
	//parcourt le fichier classement
	//sépare les informations des différents joueurs
	//sépare le score et le pseudo des joueurs
	//crée un tableau contenant les informations de chaque joueurs
	//les informations de chaque joueur sont elles-mêmes stokées dans un tableau
	//classe les joueurs selon leur score




//fonction affichage classement
	//ouvre le fichier en mode lecture
	//lis les scores des dix meilleurs joueurs
	//appelle la fonction meilleurs scores
	//affiche les 10 meilleurs scores
	//ferme le fichier




//fonction tour
	//génération aléatoire d'une pièce
	//appelle la fonction affichage tableau
	//appelle la fonction affichage orientation
	//appelle la fonction décompte
	//choix de l'orientation
	//choix de la colonne
	//appelle la fonction rotation
	//appelle la fonction placement pièce




void main() {
	srand(time(NULL));

	int piece[7 * 8];
	piece[0] = 1; piece[1] = 1; piece[2] = 1; piece[3] = 1;
	piece[8] = 1; piece[9] = 1; piece[12] = 1; piece[13] = 1;
	piece[16] = 1; piece[17] = 1; piece[18] = 1; piece[21] = 1;
	piece[24] = 1; piece[25] = 1; piece[26] = 1; piece[28] = 1;
	piece[32] = 1; piece[33] = 1; piece[34] = 1; piece[38] = 1;
	piece[40] = 1; piece[41] = 1; piece[45] = 1; piece[46] = 1;
	piece[49] = 1; piece[50] = 1; piece[52] = 1; piece[53] = 1;
	for (int rang = 0; rang < 56; rang++) {
		if (piece[rang] != 1) {
			piece[rang] = 0;
		}

	}

	int grille[NbLigneGrille * NbColonneGrille] = { 0 };

	printf("Bienvenue dans Tetris.\n");
	char pseudo[10], testPseudo[10];
	int pseudoCorrect = 0;
	do {
		printf("Veuillez choisir votre pseudo (max 10 caractères):\n");
		scanf("%s", testPseudo);
		if (strlen(testPseudo) <= 10) {
			strcpy(pseudo, testPseudo);
			pseudoCorrect = 1;
			printf("Votre pseudo est %s.\n", pseudo);
		}
		else {
			printf("Votre pseudo est trop long veuillez recommencer (max 10 caractères).\n");
		}
	} while (pseudoCorrect == 0);
	affichageGrille(grille);
	afficherPieceOrientee(piece, 16);
}
//appelle la fonction tour tant que la partie n'est pas perdue
//appelle la fonction affichage tableau
//appelle la fonction stockage score
//appelle la fonction affichage classement






