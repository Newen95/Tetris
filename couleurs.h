#ifndef COULEURS_H
#define COULEURS_H

#include <stdio.h>

#define Aucune 0
#define Cyan 36
#define Jaune 33
#define Violet 35
#define Blanc 37
#define Bleu 34
#define Rouge 31
#define Vert 32

// Efface l'écran et replace le curseur en haut à gauche
#define clrscr() printf("\033[H\033[2J")

// Sélection de couleurs
#define couleur(param) printf("\033[%sm",param)
/*   param devant être un const char *, vide (identique à "0") ou formé
     d'une ou plusieurs valeurs séparées par des ; parmi
         0  réinitialisation         1  haute intensité (des caractères)
         5  clignotement             7  vidéo inversée
         30, 31, 32, 33, 34, 35, 36, 37 couleur des caractères
         40, 41, 42, 43, 44, 45, 46, 47 couleur du fond
            les couleurs, suivant la logique RGB, étant respectivement
               noir, rouge, vert, jaune, bleu, magenta, cyan et blanc */

#endif
