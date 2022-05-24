/* Created by Marco Iannella, Mattia Primavera*/

#include "abalone.h"


int controleExistanceMouvement(char (*plateau)[COLONNE], Mouvement mouvement, InfoPartie* infoPartiePtr, char alignement){
	int diffX, diffY, count;
	count = compteBilles(mouvement,  infoPartiePtr->joueurActuel);


	if(mouvement.depart.x - mouvement.range.x > 0)
		diffX = -1; /*cas ou la dernière bille se trouve dans les lignes inferieurs à celle où se trouve la bille de départ, cas inverse = -1;*/
	else if(mouvement.depart.x - mouvement.range.x <0) 
		diffX = 1;
	else if(mouvement.depart.x - mouvement.range.x == 0)
		diffX = 0;

	if(mouvement.depart.y - mouvement.range.y > 0)
		diffY = -1;
	else if(mouvement.depart.y - mouvement.range.y < 0)
		diffY = 1;
	else if(mouvement.depart.y - mouvement.range.y == 0)
		diffY = 0;

	if((mouvement.depart.x - mouvement.arrive.x > 1 || mouvement.depart.x - mouvement.arrive.x < -1) || (mouvement.depart.y - mouvement.arrive.y > 1 || mouvement.depart.y - mouvement.arrive.y < -1)){
		return 0;
	}
	if(count == 1){ 
		if(plateau[mouvement.depart.x][mouvement.depart.y] != infoPartiePtr->joueurActuel) return 0;
	}
	else{
		if(plateau[mouvement.depart.x][mouvement.depart.y] != infoPartiePtr->joueurActuel) return 0;
		if(plateau[mouvement.range.x][mouvement.range.y] != infoPartiePtr->joueurActuel) return 0;
		if(count == 3)
			if(plateau[mouvement.depart.x + diffX][mouvement.depart.y + diffY] != infoPartiePtr->joueurActuel) return 0;
	}
	return 1;
}

char typeAlignement(Mouvement mouvement, char type_joueur)
{
	/*cas ou les pions selectionne sont en ligne horizontalment*/
	if (mouvement.depart.x == mouvement.range.x)
		return 'h';
	/*cas ou les pions selectionne sont en ligne verticalment*/
	else if (mouvement.depart.y == mouvement.range.y)
		return 'v';
	/*cas ou les pions selectionne sont en ligne obliquement et ils sont 3*/
	else if ((mouvement.depart.x != mouvement.range.x) && (mouvement.depart.y != mouvement.range.y))
		return'o';

	return 'a';
}

int legaliteMouvementSing(Mouvement mouvement,char (*plateau)[COLONNE])
{
	/*Fonction qui controle la legalité d'un mouvement d'une simple qui se deplace sur le tab et renvoye 1 si le deplacement peut etre effectue, 0 autrement*/
	if (mouvement.range.y == -1){
		if ( (plateau[mouvement.arrive.x][mouvement.arrive.y] != 'N') && (plateau[mouvement.arrive.x][mouvement.arrive.y] != 'B') && (plateau[mouvement.arrive.x][mouvement.arrive.y] != '-') && (plateau[mouvement.arrive.x][mouvement.arrive.y] != '\\') && (plateau[mouvement.arrive.x][mouvement.arrive.y] != '/'))
			return 1;	
	}
	return 0;
}

int controleInput(char* mouvement, char(*plateau)[], InfoPartie* infoPartiePtr )
{
	/*Fonction qui controle la validité de la chaine inseré par l'utilisateur renvoye 0 si l'utilisateur n'à rien mis, 1 si le controle est bon, 2 si la lettre cordonnee n'est pas representee, 3 si le numero inserée n'est pas representee, 4 si entre un mouv et l'autre il n'y a pas '-'*/
	if (strcmp(mouvement, "SAUVEGARDE")==0 || strcmp(mouvement, "sauvegarde")==0  )
	{
			sauvegardePartie(plateau, infoPartiePtr);
			printf(" Sauvegarde Reussie.......\n");
			exit(0);
	}

	if (strlen(mouvement) == 5)
	{
		int i;
		for (i=0; i < 5; i++)
		{
			if ((i % 3 ==0) && (((int)(toupper(mouvement[i])) < 65) || ((int)(toupper(mouvement[i])) > 73)))
				return 2;
			if ((i % 3 ==1) && ((atoi(mouvement+i)< 1) || (atoi(mouvement+i) >9)))
				return 3;
			if ((i % 3 ==2) && (mouvement[i] != '-'))
				return 4;
		}
		return 1;
		
	}
	else if (strlen(mouvement) == 8)
	{
		int i;
	 	for (i=0; i < 8; i++)
		{
			if ((i % 3 ==0) && (((int)(toupper(mouvement[i])) < 65) || ((int)(toupper(mouvement[i])) > 73)))
				return 2;
			if ((i % 3 ==1) && ((atoi(mouvement+i)< 1) || (atoi(mouvement+i) >9)))
				return 3;
			if ((i % 3 ==2) && (mouvement[i] != '-'))
				return 4;
		}
		return 1;
	}
	return 0;
}

int compteBilles(Mouvement mouvement,  char type_joueur)
{
	/*Fonction qui compte les billes à boujer. Prends en arg une struct et le type d alignement et renvoye le numero des billes*/
	if(mouvement.range.x == -1 && mouvement.range.y == -1) return 1;
	else{/*cas 2 ou 3*/
		switch(typeAlignement(mouvement, type_joueur)){
			case 'h':
				if(mouvement.depart.y - mouvement.range.y == 2 || mouvement.depart.y - mouvement.range.y == -2) return 3;
				else if(mouvement.depart.y - mouvement.range.y == 1 || mouvement.depart.y - mouvement.range.y == -1) return 2;
			case 'v':
				if(mouvement.depart.x - mouvement.range.x == 2 || mouvement.depart.x - mouvement.range.x == -2) return 3;
				else if(mouvement.depart.x - mouvement.range.x == 1 || mouvement.depart.x - mouvement.range.x == -1) return 2;
			case 'o':
				if(mouvement.depart.x - mouvement.range.x == 2 || mouvement.depart.x - mouvement.range.x == -2) return 3;
				else if(mouvement.depart.x - mouvement.range.x == 1 || mouvement.depart.x - mouvement.range.x == -1) return 2;
		}
	}
	return 8000; /*en cas d'erreur, on va s'en rendre compte simplement*/

}

char  typeMouvement(Mouvement mouvement, char alignement, InfoPartie* infoPartiePtr){
	char retour;
	retour = 'e'; /*erreur*/
	switch(alignement){
		case 'h':
			if((mouvement.depart.y - mouvement.arrive.y == +1) && (mouvement.depart.x - mouvement.arrive.x == +1)) /*l'arrive est sur la meme ligne => mouvement en ligne */
				retour = 's';
			else if((mouvement.depart.y - mouvement.arrive.y == -1) && (mouvement.depart.x - mouvement.arrive.x == -1)) /*en ligne mais direction ouest*/
				retour = 's';
			else if((mouvement.depart.x - mouvement.arrive.x == +1) && (mouvement.depart.y == mouvement.arrive.y))
				retour = 's';
			else if((mouvement.depart.x - mouvement.arrive.x == -1) && (mouvement.depart.y == mouvement.arrive.y))
				retour = 's';
			else if((mouvement.depart.x == mouvement.arrive.x) && (mouvement.depart.y - mouvement.arrive.y == -1))
				retour = 'l';
			else if((mouvement.depart.x == mouvement.arrive.x) && (mouvement.depart.y - mouvement.arrive.y == +1)){
				retour = 'l';
			}
			break;
		case 'v':
			if((mouvement.arrive.y == mouvement.depart.y)  && (mouvement.depart.x - mouvement.arrive.x == +1))
				retour = 'l';
			else if((mouvement.arrive.y == mouvement.depart.y) && (mouvement.depart.x - mouvement.arrive.x == -1))
				retour = 'l';
			else if((mouvement.depart.y - mouvement.arrive.y == +1) && (mouvement.arrive.x == mouvement.depart.x))
				retour = 's';
			else if((mouvement.depart.y - mouvement.arrive.y == -1) && (mouvement.arrive.x == mouvement.depart.x))
				retour = 's';
			else if((mouvement.depart.y - mouvement.arrive.y == +1) && (mouvement.depart.x - mouvement.arrive.x == +1))
				retour = 's';
			else if((mouvement.depart.y - mouvement.arrive.y == -1) && (mouvement.depart.x - mouvement.arrive.x == -1))
				retour = 's';
			break;
		case 'o':
			if((mouvement.depart.x - mouvement.arrive.x == -1) && (mouvement.depart.y - mouvement.arrive.y == -1))/*vers sud est*/ 
				retour = 'l';
			else if((mouvement.depart.x - mouvement.arrive.x == +1) && (mouvement.depart.y - mouvement.arrive.y == +1)) /*vers sud est*/
				retour = 'l';
			else if((mouvement.depart.y - mouvement.arrive.y == +1) && (mouvement.arrive.x == mouvement.depart.x))
				retour = 's';
			else if((mouvement.depart.y - mouvement.arrive.y == -1) && (mouvement.arrive.x == mouvement.depart.x))
				retour = 's';
			else if((mouvement.arrive.y == mouvement.depart.y) && (mouvement.arrive.x - mouvement.depart.x == +1))
				retour = 's';
			else if((mouvement.arrive.y == mouvement.depart.y) && (mouvement.arrive.x - mouvement.depart.x == -1))
				retour = 's';
			break;
	}
	return retour;
}

int legalite(char(*plateau)[COLONNE], Mouvement mouvement, InfoPartie* infoPartiePtr, char type_mouvement){
	int retour = 0;
	if(mouvement.range.x == -1 && mouvement.range.y == -1){
		retour = legaliteMouvementSing(mouvement, plateau);
	}
	else{
		switch(type_mouvement){
			case 'l':
				retour = legaliteLigne(plateau, mouvement, infoPartiePtr);				
				break;
			case 's':
				retour = legaliteLateral(plateau, mouvement, typeAlignement(mouvement, infoPartiePtr->joueurActuel), infoPartiePtr->joueurActuel);
				break;
		}
	}
	return retour;
}

int legaliteLigne(char(*plateau)[COLONNE], Mouvement mouvement, InfoPartie* infoPartiePtr){
	int count, diffX, diffY;
	int retour = 0;
	char joueurActuel = infoPartiePtr->joueurActuel;
	count = compteBilles(mouvement,  infoPartiePtr->joueurActuel);
	if(mouvement.depart.x - mouvement.range.x > 0)
		diffX = -1; /*cas ou la dernière bille se trouve dans les lignes inferieurs à celle où se trouve la bille de départ, cas inverse = -1;*/
	else if(mouvement.depart.x - mouvement.range.x <0) 
		diffX = 1;
	else if(mouvement.depart.x - mouvement.range.x == 0)
		diffX = 0;

	if(mouvement.depart.y - mouvement.range.y > 0)
		diffY = -1;
	else if(mouvement.depart.y - mouvement.range.y < 0)
		diffY = 1;
	else if(mouvement.depart.y - mouvement.range.y == 0)
		diffY = 0;
	if (joueurActuel == 'N'){
		/*soit on a deux bille, soit on en a trois, on les décale vers la direction du mouvement*/
		switch(plateau[mouvement.depart.x + diffX * count][mouvement.depart.y + diffY * count]){
			case '.': retour = 3; break;
			case 'B': 
				switch (plateau[mouvement.depart.x + (diffX * count) + diffX][mouvement.depart.y + (diffY * count) +diffY]){
					case '.': retour = 1; break;
					case 'N': retour = 0; break;
					case '-': case ' ': case '/': case '\\': 
						decrementeBilles(infoPartiePtr); retour = 3; break;
					case 'B':
						if (count ==2) retour = 0;
						switch (plateau[mouvement.depart.x + (diffX * count) + diffX *2][mouvement.depart.y + (diffY * count) +diffY*2]){
							case '.': retour = 2; break;
							case '-': case ' ': case '/': case '\\':
								decrementeBilles(infoPartiePtr); retour = 3; break;
							case 'B': retour = 0; break;
							case 'N': retour = 0; break;
						}
						break;			
				}
				break;		
		}
	}
	else{
		switch(plateau[mouvement.depart.x + diffX * count][mouvement.depart.y + diffY * count]){
			case '.': retour = 3; break;
			case 'N': 
				switch (plateau[mouvement.depart.x + (diffX * count) + diffX][mouvement.depart.y + (diffY * count) +diffY]){
					case '.': retour = 1; break;
					case 'B': retour = 0; break;
					case '-': case ' ': case '/': case '\\': 
						decrementeBilles(infoPartiePtr); retour = 3; break;
					case 'N':
						if (count ==2) retour = 0;
						switch (plateau[mouvement.depart.x + (diffX * count) + diffX *2][mouvement.depart.y + (diffY * count) +diffY*2]){
							case '.': retour = 2; break;
							case '-': case ' ': case '/': case '\\':
								decrementeBilles(infoPartiePtr); retour = 3; break;
							case 'N': retour = 0; break;
							case 'B': retour = 0; break;
						}
						break;			
				}
				break;		
		}	
	}
	return retour;
}/*fin fonction*/



void decrementeBilles(InfoPartie* infoPartiePtr)
{
	if (infoPartiePtr -> joueurActuel == 'B')
		infoPartiePtr -> numeroBillesNoires--;
	else 
		infoPartiePtr -> numeroBillesBlanches--;
	if (infoPartiePtr->numeroBillesNoires == 8 || infoPartiePtr->numeroBillesBlanches == 8)
		finPartie(infoPartiePtr); 
}
void finPartie(InfoPartie* infoPartiePtr)
{
	if (infoPartiePtr->numeroBillesBlanches == 8 && infoPartiePtr->numeroBillesNoires > 8)
	{
		printf("Joueur NOIR à gagné!!! Felicitations");
		exit(0);
	}
	else if (infoPartiePtr->numeroBillesBlanches > 8 && infoPartiePtr->numeroBillesNoires == 8)
	{
		printf("Joueur BLANC à gagné!!! Felicitations");
		exit(0);
	}
}

int legaliteLateral(char(*plateau)[COLONNE], Mouvement mouvement, char type_alignement, char joueur_actuel)
{
	int count, diffX, diffY;
	count = compteBilles(mouvement,  joueur_actuel);
	switch(type_alignement){
		case 'h':
			diffY = +1; 
			if(plateau[mouvement.arrive.x][mouvement.arrive.y] == '.' && plateau[mouvement.arrive.x][mouvement.arrive.y + diffY] == '.')
			{
				if(count == 3)
				{
					if(plateau[mouvement.arrive.x][mouvement.arrive.y + diffY*2] == '.')
						return 1;
					else 
						return 0;
				}
				return 1;		
			}
			break;
		case 'v':
			if(mouvement.depart.x - mouvement.range.x > 0)
				diffX = -1; /*cas ou la dernière bille se trouve dans les lignes inferieurs à celle où se trouve la bille de départ, cas inverse = -1;*/
			else if(mouvement.depart.x - mouvement.range.x <0) 
				diffX = +1;
			
			if(plateau[mouvement.arrive.x][mouvement.arrive.y] == '.' && plateau[mouvement.arrive.x + diffX][mouvement.arrive.y] == '.'){
				if(count == 3)
				{
					if(plateau[mouvement.arrive.x + diffX*2][mouvement.arrive.y] == '.')
					
						return 1;
					else 
						return 0;
				}
				return 1;
			}
			break;
		case 'o':
			if(mouvement.depart.x - mouvement.range.x > 0)
			{
				diffX = -1; diffY = -1; /*cas ou la dernière bille se trouve dans les lignes inferieurs à celle où se trouve la bille de départ, cas inverse = -1;*/
			}
			else if(mouvement.depart.x - mouvement.range.x < 0)
			{
				diffX = +1; diffX = +1;
			}
			if(plateau[mouvement.arrive.x][mouvement.arrive.y] == '.' && plateau[mouvement.arrive.x + diffX][mouvement.arrive.y + diffY] == '.'){
				if(count == 3)
				{
					if(plateau[mouvement.arrive.x + 2*diffX][mouvement.arrive.y + diffY*2] == '.')
					
						return 1;
					else 
						return 0;
					}
				return 1;
			}
			break;
	}/*fin switch*/
	return 0;
}
