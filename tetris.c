#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#ifdef _WIN32
#include <Windows.h>
#include <couleurs.h>
#else
//#include <sys/time.h>
//#include <sys/types.h>
#include <unistd.h>
#endif




#define NbColonneGrille 10
#define NbLigneGrille 14
#define DureeDecompte 5


int trouverBordGauche(int piece16[]) {
	int bordGauche = 4;
	for( int ligne = 0; ligne < 4; ligne++ ) {			//boucle parcourant la piece pour déterminer le bord gauche de la pièce
		for( int colonne = 0; colonne < 4; colonne++ ) {
			if( piece16[ ligne * 4 + colonne ] == 1 ) {
				if( colonne < bordGauche ) {
					bordGauche = colonne;
				}
			}
		}
	}
	return bordGauche;
}


int trouverBordDroit( int piece16[] ) {
	int bordDroit = 0;
	for( int ligne = 0; ligne < 4; ligne++ ) {			//boucle parcourant la piece pour déterminer le bord droit de la pièce
		for( int colonne = 0; colonne < 4; colonne++ ) {
			if( piece16[ ligne * 4 + colonne ] == 1 ) {
				if( colonne > bordDroit ) {
					bordDroit = colonne;
				}
			}
		}
	}
	return bordDroit;
}


int trouverLigneBas( int piece16[] ) {
	int ligneBas = 0;
	for( int ligne = 0; ligne < 4; ligne++ ) {			//boucle parcourant la piece pour déterminer la ligne du bas de la pièce
		for( int colonne = 0; colonne < 4; colonne++ ) {
			if( piece16[ ligne * 4 + colonne ] == 1 ) {
				if( ligne > ligneBas ) {
					ligneBas = ligne;
				}
			}
		}
	}
	return ligneBas;
}


int trouverLigneHaut( int piece16[] ) {
	int ligneHaut = 4;
	for( int ligne = 0; ligne < 4; ligne++ ) {			//boucle parcourant la piece pour déterminer la ligne du haut de la pièce
		for( int colonne = 0; colonne < 4; colonne++ ) {
			if( piece16[ ligne * 4 + colonne ] == 1 ) {
				if( ligne < ligneHaut ) {
					ligneHaut = ligne;
				}
			}
		}
	}
	return ligneHaut;
}


int trouverCentre(int piece16[]) {	//fonction permettant de trouver le centre d'une fonction entrée en paramètres
	int bordGauche = 3;
	int bordDroit = 0;
	int largeur = 0;
	int centre;
	
	bordDroit = trouverBordDroit( piece16 );
	bordGauche = trouverBordGauche( piece16 );

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


void remplissageGrille(int grille[],int piece16[],int colonneChoisie,int ligneEmplacement){			//reporte la piece sur la grille à un emplacement donné en paramètres
	int xCasePiece = 0;
	int yCasePiece = 0;
	int centrePiece = trouverCentre(piece16);
	for( int lignePiece = 0; lignePiece < 4; lignePiece++ ) {
		for( int colonnePiece = 0; colonnePiece < 4; colonnePiece++ ) {
			xCasePiece = colonneChoisie - centrePiece + colonnePiece;
			yCasePiece = ligneEmplacement + lignePiece;
			if( piece16[ lignePiece * 4 + colonnePiece ] == 1 ) {
				grille[yCasePiece * NbColonneGrille + xCasePiece] = 1;
			}
		}
	}
}


int positionPiece( int grille[], int piece16[], int colonneChoisie ) {		// retourne la ligne où placer la piece passée en paramètres
	int ligneFinale = NbLigneGrille - 1;
	int centrePiece = trouverCentre( piece16 );
	int collision = 0;
	int xCasePiece = 0;
	int yCasePiece = 0;

	for( int ligneGrille = 0; ( ligneGrille < NbLigneGrille ) && ( collision == 0 ); ligneGrille++ ) {
		if( ligneGrille == 11 )
		{
			int iToto = 0;
		}
		for( int lignePiece = 0; ( lignePiece < 4 ) && ( collision == 0 ); lignePiece++ ) {
			for( int colonnePiece = 0; ( colonnePiece < 4 ) && ( collision == 0 ); colonnePiece++ ) {
				xCasePiece = colonneChoisie - centrePiece + colonnePiece;
				yCasePiece = ligneGrille + lignePiece;
				if( (yCasePiece > NbLigneGrille - 1) && ( piece16[ lignePiece * 4 + colonnePiece ] == 1 ) )  {
					collision = 1;
					ligneFinale = ligneGrille - 1;
				}
				else {
					if( yCasePiece < NbLigneGrille ) {
						if( ( grille[ yCasePiece * NbColonneGrille + xCasePiece ] == 1 ) && ( piece16[ lignePiece * 4 + colonnePiece ] == 1 ) ) {
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


int decompte(){
	fd_set rfds;
	struct timeval tv;
	int retval;

	// Surveiller stdin (fd 0) en attente d'entrées
	FD_ZERO( &rfds );
	FD_SET( 0, &rfds );

	// Durée du décompte
	tv.tv_sec = DureeDecompte;
	tv.tv_usec = 0;

	retval = select( 1, &rfds, NULL, NULL, &tv );
	if( retval == 1 )
		return 1;		// L'utilisateur a appuyé sur une touche.

	return 0;
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
		pieceReorientee[rang] = (int*) calloc(16, sizeof(int));			//crée un tableau contenant les différentes orientations de la pièce
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
		for (int numPiece = 0; numPiece < 4; numPiece++) {
			afficherLignePiece(pieceReorientee[numPiece], lignePiece);
			printf(" ");
		}
		printf("\n");
	}
	printf("\n");
	for (int rang = 0; rang < 4; rang++) {
		free(pieceReorientee[rang]);
	}
}


void stockageScore(char pseudo[],int score){            //stocke les données du joueur dans le fichier classement
    char stringScore[5];
    sprintf(stringScore,"%d",score);
	FILE* fichierClassement = fopen("classement.txt","a+");     //ouvre le fichier en mode écriture
	if (fichierClassement == NULL){
	    printf("Impossible d'ouvrir le fichier\n");
	}
    fprintf(fichierClassement,"%s;%s\n",pseudo,stringScore);                 //inscrit le pseudo et le score
	fclose(fichierClassement);                           //ferme le fichier
}


int* lectureScore(){
    FILE* fichierClassement = fopen("classement.txt","r+");
    if (fichierClassement == NULL){
	    printf("Impossible d'ouvrir le fichier\n");
	}





	//ouvre le fichier classement en mode lecture
	//crée un tableau de joueurs avec leur score et leur pseudo
	//retourne ce tableau

	return( NULL );
}




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




void decalerLignesAuDessus( int grille[], int ligneASupprimer ) {
	for( int ligne = ligneASupprimer; ligne > 0; ligne-- ) {
		for( int colonne = 0; colonne < NbColonneGrille; colonne++ ) {
			grille[ligne * NbColonneGrille + colonne] = grille[(ligne - 1) * NbColonneGrille + colonne];
		}
	}
}


int supprimerLigne( int grille[],  int ligneHaut, int ligneBas ) {
	int lignePleine;
	int nbLignesSupprimees = 0;
	for( int ligne = ligneHaut; ligne <= ligneBas; ligne++ ) {
		lignePleine = 1;
		for( int colonne = 0; (colonne < NbColonneGrille) && (lignePleine == 1); colonne++ ) {
			if( grille[ligne * NbColonneGrille + colonne] == 0 ) {
				lignePleine = 0;
			}
		}
		if( lignePleine == 1) {
			decalerLignesAuDessus(grille, ligne);
			nbLignesSupprimees++;
		}
	}
	return nbLignesSupprimees;
}


int testerFin( int grille[] ) {
	for( int colonne = 0; colonne < NbColonneGrille; colonne++ ) {
		if( grille[3 * NbColonneGrille + colonne] == 1) {	//ligne 3 = première ligne cachée
			return 1;
		}
	}
	return 0;
}


void tour( int grille[], int piece[], int* score ) {
	int numPiece, orientationChoisie, colonneChoisie, ligneEmplacement, colonneMin, colonneMax, ligneHaut, ligneBas;
	int pieceReorientee[ 16 ];
	int orientationCorrecte = 0;
	int colonneCorrecte = 0;


	numPiece = ( rand() % 7 ) * 8;		//choix aléatoire d'une pièce parmi les 7 possibles	
	printf("Score actuel : %d\n\n", *score);
	affichageGrille( grille );
	afficherPiecesOrientees( piece, numPiece );

	do {
		printf( "Choisissez l'orientation de la pièce : " );
		fflush(stdout);
		orientationChoisie = 0;
		if( decompte() == 1 ) {
			scanf( "%d", &orientationChoisie );
			scanf( "%*[^\n]" );
			getchar();
			printf( "\n" );
			if( orientationChoisie >= 1 && orientationChoisie <= 4 ) {
				orientationCorrecte = 1;
			}
			else {
				printf( "L'orientation choisie n'est pas valide, veuillez recommencer.\n\n" );
			}
		}
		else
		{
			orientationChoisie = 1 + rand() % 3;
			printf( "%d\n", orientationChoisie);
			orientationCorrecte = 1;
		}
	} while( orientationCorrecte == 0 );
	orientationChoisie = ( orientationChoisie - 1 ) * 90;

	rotation( &piece[ numPiece ], orientationChoisie, pieceReorientee );
	colonneMin = trouverCentre( pieceReorientee ) - trouverBordGauche( pieceReorientee ) + 1;
	colonneMax = trouverCentre( pieceReorientee ) - trouverBordDroit( pieceReorientee ) + NbColonneGrille;

	do {
		printf( "Choisissez la colonne où placer la pièce (de %d à %d) : ", colonneMin, colonneMax );
		fflush(stdout);


		if( decompte() == 1 ) {
			scanf( "%d", &colonneChoisie );
			scanf( "%*[^\n]" );
			getchar();
			printf( "\n" );
			if(colonneChoisie >= colonneMin && colonneChoisie <= colonneMax){
				colonneCorrecte = 1;
			}
			else {
				printf( "La colonne choisie n'est pas valide, veuillez recommencer.\n\n" );
			}
		}

		else
		{
			colonneChoisie = colonneMin + rand() % (NbColonneGrille - colonneMin);
			printf( "%d\n", colonneChoisie);
			colonneCorrecte = 1;
		}
	} while( colonneCorrecte == 0 );
	colonneChoisie--;

	ligneEmplacement = positionPiece( grille, pieceReorientee, colonneChoisie );
	remplissageGrille( grille, pieceReorientee, colonneChoisie, ligneEmplacement );
	ligneHaut = trouverLigneHaut( piece );
	ligneBas = trouverLigneBas( piece );
	*score += supprimerLigne( grille, ligneEmplacement + ligneHaut, ligneEmplacement + ligneBas );
}


void initialiserPieces( int piece[] )
{

	for( int rang = 0; rang < 56; rang++ ) { // initialisation des cases vides
			piece[ rang ] = 0;
	}	

	// Pièce 1
	// @@@@@
	piece[ 0 ] = 1; piece[ 1 ] = 1; piece[ 2 ] = 1; piece[ 3 ] = 1;

	// Pièce 2
	// @@
	// @@
	piece[ 8 ] = 1; piece[ 9 ] = 1; piece[ 12 ] = 1; piece[ 13 ] = 1;

	// Pièce 3
	// @@@
	//  @
	piece[ 16 ] = 1; piece[ 17 ] = 1; piece[ 18 ] = 1; piece[ 21 ] = 1;

	// Pièce 4
	// @@@
	// @
	piece[ 24 ] = 1; piece[ 25 ] = 1; piece[ 26 ] = 1; piece[ 28 ] = 1;

	// Pièce 5
	// @@@
	//   @
	piece[ 32 ] = 1; piece[ 33 ] = 1; piece[ 34 ] = 1; piece[ 38 ] = 1;

	// Pièce 6
	// @@
	//  @@
	piece[ 40 ] = 1; piece[ 41 ] = 1; piece[ 45 ] = 1; piece[ 46 ] = 1;

	// Pièce 7
	//  @@
	// @@
	piece[ 49 ] = 1; piece[ 50 ] = 1; piece[ 52 ] = 1; piece[ 53 ] = 1;
}


	//génération aléatoire d'une pièce
	//appelle la fonction affichage tableau
	//appelle la fonction affichage orientation
	//appelle la fonction décompte
	//choix de l'orientation
	//choix de la colonne
	//appelle la fonction rotation
	//appelle la fonction placement pièce

int main() {							//fonction principale


	int termine = 0;
	int score = 0;
	srand(time(NULL));

	int piece[7 * 8];						//crée et initialise les différentes pièces sous forme d'un tableau à une dimension
	initialiserPieces( piece );

	int grille[NbLigneGrille * NbColonneGrille] = { 0 };

	//couleur( "32" );	//affichage en vert
	printf("Bienvenue dans Tetris !\n\n\n");
	//printf("\033[31;108mBienvenue dans Tetris !\033[00m\n\n\n");
	//couleur( "0" );

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
			printf("Votre pseudo est trop long, veuillez recommencer (max 10 caractères).\n");
		}
	} while (pseudoCorrect == 0);

	while( termine == 0 ) {
		tour( grille, piece, &score);
		if( testerFin( grille ) == 1 ) {
			printf("La partie est terminée !\n\n");
			printf( "Votre score finale est : %d\n\n", score );
			termine = 1;
		}
	}
	stockageScore(pseudo,score);
}
//appelle la fonction tour tant que la partie n'est pas perdue
//appelle la fonction affichage tableau
//appelle la fonction stockage score
//appelle la fonction affichage classement






