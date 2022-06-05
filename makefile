tetris.exe: tetris.o piece.o grille.o utilitaire.o classement.o
	gcc tetris.o piece.o grille.o utilitaire.o classement.o -o tetris.exe -Wall

piece.o: piece.c piece.h
	gcc -c piece.c -o piece.o -Wall
	
classement.o: classement.c classement.h
	gcc -c classement.c -o classement.o -Wall
	
grille.o: grille.c grille.h
	gcc -c grille.c -o grille.o -Wall
	
utilitaire.o: utilitaire.c utilitaire.h
	gcc -c utilitaire.c -o utilitaire.o -Wall
	
tetris.o: tetris.c tetris.h classement.h piece.h grille.h utilitaire.h couleurs.h
	gcc -c tetris.c -o tetris.o -Wall

clean:
	rm -f *.o

