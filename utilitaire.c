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
// utilit� : permet de d�tecter si l'utilisateur a enfonc� une touche du clavier durant le d�compte
// param�tres d'entr�e : dur�e du d�compte en secondes
// param�tres de sortie : 1 si l'utilisateur a appuy� sur une touche, 0 sinon

int decompte( int dureeDecompte ) {
	fd_set readfds;
	struct timeval Duree;
	int resultat;

	//initialisation
	FD_ZERO( &readfds );
	FD_SET( 0, &readfds );

	//dur�e du d�compte
	Duree.tv_sec = dureeDecompte;
	Duree.tv_usec = 0;

	//surveille l'entr�e standard (clavier) sur une dur�e max
	resultat = select( 1, &readfds, NULL, NULL, &Duree );
	if( resultat == 1 )
		return 1;	//l'utilisateur a appuy� sur une touche

	return 0; //aucune touche pr�ss�e durant le d�compte
}
