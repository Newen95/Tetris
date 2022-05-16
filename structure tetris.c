#include<stdio.h>
#include<stdlib.h>
#include<time.h>




//fonction rotation
	//création d'un tableau intermédiaire
	//parcourt le tableau de la pièce
	//pour chaque caractère crée son équivalent réorienté dans le tableau intermédiaire	




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




//fonction affichage tableau
	//affiche le numéro de chaque colonne
	//parcourt le tableau final à l'exception des quatre premières lignes
	//place un "|" puis marque le caractère correspondant
	//à la fin de chaque ligne place un "|" supplémentaire




//fonction affichage orientation
	//affiche les nombres correspondant aux choix
	//appelle la fonction rotation
	//affiche les pièces réorientées




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




//fonction principale
	srand(time(NULL));
	//creation des pieces
    		//piece 1
			//creation du tableau
			//remplissage du tableau
    		//piece 2
    		//piece 3
    		//piece 4
    		//piece 5
    		//piece 6
   		//piece 7




	//création tableau final




	//definition du pseudo
	//appelle la fonction tour tant que la partie n'est pas perdue
	//appelle la fonction affichage tableau
	//appelle la fonction stockage score
	//appelle la fonction affichage classement






