// tetris.h

#ifndef TETRIS_H
#define TETRIS_H

#define DureeDecompteNiveau1 7 //en secondes
#define DureeDecompteNiveau2 5 //en secondes
#define DureeDecompteNiveau3 3 //en secondes

void initialiserPieces( int piece[] );
void tour( int grille[], int piece[], int* score, int niveau );
int main();

#endif
