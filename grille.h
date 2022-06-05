// grille.h

#ifndef GRILLE_H
#define GRILLE_H

#define NbColonneGrille 10
#define NbLigneGrille 14

void affichageGrille( int grille[] );
int positionPiece( int grille[], int piece16[], int colonneChoisie );
void remplissageGrille( int grille[], int piece16[], int colonneChoisie, int ligneEmplacement );

void decalerLignesAuDessus( int grille[], int ligneASupprimer );
int supprimerLigne( int grille[], int ligneHaut, int ligneBas );
int testerFin( int grille[] );

#endif