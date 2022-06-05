// piece.h

#ifndef PIECE_H
#define PIECE_H

enum NomPiece { PieceI, PieceO, PieceT, PieceL, PieceJ, PieceZ, PieceS };


int trouverBordGauche( int piece16[] );
int trouverBordDroit( int piece16[] );
int trouverLigneBas( int piece16[] );
int trouverLigneHaut( int piece16[] );
int trouverCentre( int piece16[] );

void rotation( int* piece8, int angle, int* pieceReorientee );
void afficherLignePiece( int pieceReorientee[], int numLignePiece );
void afficherPiecesOrientees( int piece[], enum NomPiece nomPiece );

#endif