/* Created by Marco Iannella, Mattia Primavera*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define LENGTH 121
#define COLONNE 11
#define LIGNE 11

typedef struct{
	int x;
	int y;
}Point;
typedef struct{
	Point arrive;
	Point depart;
	Point range;
}Mouvement;
typedef struct{
	int numeroBillesNoires;
	int numeroBillesBlanches;
	char joueurActuel;
}InfoPartie;
typedef struct{
	char** liste_movs;
	int liste_longeur;        
}Test;


/*Prototypes Fonctions*/
void creation_plateau(char [][COLONNE]);
void affiche_plateau(char [][COLONNE]);
int convertCord(char *, int);
Mouvement parseMouvement(char *);
void affiche_de_base(char [][COLONNE]);
int convertCoordY(int , int );
char typeAlignement(Mouvement, char);
void deplacementSing(Mouvement, char [][COLONNE], InfoPartie*);
int legaliteMouvementSing(Mouvement mouvement, char [][COLONNE]);
int controleInput(char*, char[][COLONNE], InfoPartie*);
int legaliteLigne(char[][COLONNE], Mouvement mouvement, InfoPartie* infoPartiePtr);
int compteBilles(Mouvement, char );
char typeMouvement(Mouvement, char , InfoPartie* );
void deplacementLigne(char [][COLONNE], Mouvement ,InfoPartie*, int legalite );
void deplacementLateral(char [][COLONNE], Mouvement , char , char );
void finPartie(InfoPartie*); 
void decrementeBilles(InfoPartie*);
int legaliteLateral(char [][COLONNE], Mouvement, char, char);
int legalite(char[][COLONNE], Mouvement , InfoPartie* , char );
void deplace(char [][COLONNE], Mouvement , char , InfoPartie *, int legalite);
int controleExistanceMouvement(char [][COLONNE], Mouvement mouvement, InfoPartie* infoPartiePtr, char alignement);
void help();
int  menu();
void humanVsHuman();
void robotVsRobot();
void humanVsRobot();
void sauvegardePartie(char [][COLONNE], InfoPartie*);
void executeTest(Test* );
void modaliteTest();