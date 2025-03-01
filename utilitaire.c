// utilitaire.c

#ifdef _WIN32
#include <Windows.h>
#include <search.h>
#else
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#endif

#include "utilitaire.h"

// decompte
// utilité : permet de détecter si l'utilisateur a enfoncé une touche du clavier durant le décompte
// paramètres d'entrée : durée du décompte en secondes
// paramètres de sortie : 1 si l'utilisateur a appuyé sur une touche, 0 sinon

int decompte( int dureeDecompte ) {
	fd_set readfds;
	struct timeval Duree;
	int resultat;

	//initialisation
	FD_ZERO( &readfds );
	FD_SET( 0, &readfds );

	//durée du décompte
	Duree.tv_sec = dureeDecompte;
	Duree.tv_usec = 0;

	//surveille l'entrée standard (clavier) sur une durée max
	resultat = select( 1, &readfds, NULL, NULL, &Duree );
	if( resultat == 1 )
		return 1;	//l'utilisateur a appuyé sur une touche

	return 0; //aucune touche préssée durant le décompte
}
