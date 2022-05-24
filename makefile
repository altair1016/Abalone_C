#
#MakeFile pour le jeu ABALONE
#Systeme d'exploitation MACOSX avec compilateur gcc
#
abalone: main.o fonctions_controles.o fonctions.o fonctions_tableau.o
	gcc -o abalone main.o fonctions_controles.o fonctions.o fonctions_tableau.o 
#
main.o: main.c abalone.h
	gcc -c main.c
#
fonctions_controles.o: fonctions_controles.c abalone.h
	gcc -c fonctions_controles.c
#
fonctions.o: fonctions.c abalone.h
	gcc -c fonctions.c
#
fonctions_tableau.o: fonctions_controles.c abalone.h
	gcc -c fonctions_tableau.c
#
