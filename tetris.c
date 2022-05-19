#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#define NbColonneGrille 10
#define NbLigneGrille 14
#define DureeDecompte 10




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




void afficherLignePiece(int pieceReorientee[], int numLignePiece) {		//affiche la ligne souhaitee d'une piece passée en paramètres
	int numLignePieceEnCours = 0;
	int ligneVide;
	for (int ligne = 0; ligne < 4; ligne++) {
		ligneVide = 1;
		for (int colonne = 0; colonne < 4; colonne++) {
			if (pieceReorientee[ligne * 4 + colonne] == 1) {
				ligneVide = 0;

			}
		}
		if (ligneVide == 0) {
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
				return;
			}
		}
	}
	printf("    ");
}




void rotation(int* piece8, int angle, int* pieceReorientee) {		//permet de retourner la piece souhaitee dans la direction indiquee
	int piece16[16];
	for (int rang = 0; rang < 8; rang++) {		//conversion de la piece de format 8 en piece de format 16
		piece16[rang] = piece8[rang];
	}
	for (int rang = 8; rang < 16; rang++) {
		piece16[rang] = 0;
	}
	if (angle == 0) {				//applique la formule adaptée selon l'angle de rotation souhaité
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




void remplissageGrille(int grille[],int piece16[],int colonneChoisie,int ligneChoisie){			//reporte la piece sur la grille à un emplacement donné en paramètres
	for(int lignePiece = 0;lignePiece<4;lignePiece++){
		for(int colonnePiece = 0;colonnePiece<4;colonnePiece++){
			if(piece16[lignePiece*4+colonnePiece] == 1){					
				grille[(lignePiece + ligneChoisie)*10 + (colonnePiece + colonneChoisie)] = 1;		//emplacement de la piece sur la grile
			}
			printf("étape3");
		}
		printf("étape2");
	}
	printf("étape1");
}




int positionPiece(int grille[],int piece16[], int colonneChoisie){		// retourne la ligne où placer la piece passée en paramètres
	int ligneFinale;
	int ligneVide = 1;
	int ligneAInspecter;

	while(ligneVide == 1){					//cherche la première ligne non-vide et la stocke dans ligneAInspecter
		for(int ligneGrille = 0;ligneGrille<14;ligneGrille++){
			for(int colonneGrille = 0;colonneGrille<10;colonneGrille++){
				if(grille[ligneGrille*10+colonneGrille] == 1){
					ligneAInspecter = ligneGrille;
					ligneVide = 0;
				}
			}
			
		}
	}
	int collision = 0;
	
	while(collision == 0){				// tant qu'aucune collision n'est détectée avec une autre pièce ou la fin de la grille on continue		
		for(int ligneAInspecter;ligneAInspecter<14;ligneAInspecter++){				//on parcourt la grille en commençant à ligneAInspecter
			for(int colonneGrille = 0;colonneGrille<10;colonneGrille++){
				if(grille[(ligneAInspecter)*10+colonneGrille] == 1){			//si la case inspectée est remplie on la compare à la case correspondante de la pièce
					for(int lignePiece = 0;lignePiece<4;lignePiece++){
						for(int colonnePiece = 0;colonnePiece<4;colonnePiece++){
							if(piece16[lignePiece*4+colonnePiece] == 1){
								if((lignePiece + ligneAInspecter)*10 + (colonnePiece + colonneChoisie) == ligneAInspecter*10+colonneGrille){
									ligneFinale = ligneAInspecter - 1;			//s'il y a collision on retourne la ligne précédente
									collision == 1;
								}
							}
						}
					}
				}
			}
			if(ligneAInspecter == 13){			//si on arrive à la dernière ligne de la grille on retourne cette dernière
				ligneFinale = ligneAInspecter;
				collision = 1;
				
			}
		}
	}	
	return ligneFinale;	
}




void decompte(){
	int etape = 0;
	do{
		printf("%d\n",DureeDecompte-etape);
		sleep(1);
		etape++;
	}while(DureeDecompte-etape>0);
	//demarre à 10
	//chaque seconde retire 1
}




void affichageGrille(int grille[]) {				//affiche la grille de jeu
	printf(" 1 2 3 4 5 6 7 8 9 10\n");
	for (int ligne = 4; ligne < NbLigneGrille; ligne++) {			//parcourt le tableau à l'exception des 4 premières lignes
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




void afficherPiecesOrientees(int piece[], int indiceDepart){ 				//affiche les différentes orientations possibles d'une piece passée en paramètres
	int* pieceReorientee[4];
	int centrePiece[4];
	int espace[4];
	for (int rang = 0; rang < 4; rang++) {
		pieceReorientee[rang] = calloc(16, sizeof(int));			//crée un tableau contenant les différentes orientations de la pièce
		rotation(&piece[indiceDepart], rang*90, pieceReorientee[rang]);		//crée un second tableau contenant le centre de chaque orientation de la pièce
		centrePiece[rang] = trouverCentre(pieceReorientee[rang]);
		for (int i = 0; i < centrePiece[rang];i++) {
			printf(" ");
		}
		printf("%d",rang+1);							//écrit les numéros de chaque orientation avec le nombre d'espace approprié
		for (int i = centrePiece[rang] + 1; i < 4; i++) {
			printf(" ");
		}
		printf(" ");
	}
	printf("\n");
	for (int lignePiece = 1; lignePiece < 5; lignePiece++) {			//affiche ligne par ligne les orientations de la pièce
		for (int piece = 0; piece < 4; piece++) {
			afficherLignePiece(pieceReorientee[piece], lignePiece);
			printf(" ");
		}
		printf("\n");
	}
	printf("\n");
}




//fonction stockage score
	//ouvre le fichier classement en mode écriture
	//inscrit le score du joueur à la suite des autres
	//ferme le fichier



//fonction lecture score
	//ouvre le fichier classement en mode lecture
	//crée un tableau de joueurs avec leur score et leur pseudo
	//retourne ce tableau
	




//fonction meilleurs scores
	//parcourt le fichier classement
	//sépare les informations des différents joueurs
	//sépare le score et le pseudo des joueurs
	//crée un tableau contenant les informations de chaque joueurs
	//les informations de chaque joueur sont elles-mêmes stokées dans un tableau
	//classe les joueurs selon leur score




//fonction affichage classement
	//ouvre le fichier en mode lecture
	//les les scores des dix meilleurs joueurs
	//appelle la fonction meilleurs scores
	//affiche les 10 meilleurs scores
	//ferme le fichier




void tour(int grille[],int piece[]){
	int numPiece, orientationChoisie, colonneChoisie, ligneChoisie;
	int pieceReorientee[16];
	int orientationCorrecte = 0;
	int colonneCorrecte = 0;

	numPiece = 0 + (rand()%6)*8;		//choix aléatoire d'une pièce parmi les 7 possibles
	affichageGrille(grille);
	afficherPiecesOrientees(piece,numPiece);
	//decompte();

	do{
		printf("Choisissez l'orientation de la pièce : ");
		scanf("%d",&orientationChoisie);
		printf("\n");
		if(orientationChoisie >= 1 && orientationChoisie <= 4){
			orientationCorrecte = 1;	
		}
		else{
			printf("L'orientation choisie n'est pas valide veuillez recommencer.\n\n");
		}
	}while(orientationCorrecte == 0);

    do{
	    printf("Choisissez la colonne où placer la pièce : ");
	    scanf("%d",&colonneChoisie);
	    printf("\n");
	    if(colonneChoisie >= 1 && colonneChoisie <= 10){
			colonneCorrecte = 1;	
		}
		else{
			printf("La colonne choisie n'est pas valide veuillez recommencer.\n\n");
		}
    }while(colonneCorrecte == 0);
    
	rotation(&piece[numPiece],orientationChoisie,pieceReorientee);
	/*printf("rotation\n");
	ligneChoisie = positionPiece(grille,pieceReorientee,colonneChoisie);
	printf("position\n");
	remplissageGrille(grille,pieceReorientee,colonneChoisie,ligneChoisie);
	printf("remplissage\n");
	affichageGrille(grille);*/
}
	
	
	
		


	//génération aléatoire d'une pièce
	//appelle la fonction affichage tableau
	//appelle la fonction affichage orientation
	//appelle la fonction décompte
	//choix de l'orientation
	//choix de la colonne
	//appelle la fonction rotation
	//appelle la fonction placement pièce




void main() {							//fonction principale
	srand(time(NULL));

	int piece[7 * 8];						//crée et initialise les différentes pièces sous forme d'un tableau à une dimension
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

	printf("Bienvenue dans Tetris.\n\n\n");
	char pseudo[10], testPseudo[10];
	int pseudoCorrect = 0;
	do {
		printf("Choisissez votre pseudo (max 10 caractères): ");			//demande à l'utilisateur de choisir son pseudo et vérifie que celui-ci n'est pas trop long
		scanf("%s", testPseudo);
		printf("\n");
		if (strlen(testPseudo) <= 10) {
			strcpy(pseudo, testPseudo);
			pseudoCorrect = 1;
			printf("Votre pseudo est %s.\n\n\n", pseudo);
		}
		else {
			printf("Votre pseudo est trop long veuillez recommencer (max 10 caractères).\n");
		}
	} while (pseudoCorrect == 0);
	//affichageGrille(grille);
	//afficherPieceOrientee(piece, 16);
	//decompte();
	tour(grille,piece);
}
//appelle la fonction tour tant que la partie n'est pas perdue
//appelle la fonction affichage tableau
//appelle la fonction stockage score
//appelle la fonction affichage classement






