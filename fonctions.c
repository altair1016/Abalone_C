/* Created by Marco Iannella, Mattia Primavera*/

#include "abalone.h"


Mouvement parseMouvement(char *mouvement)
{
	/*Fonction qui parse la chaine passe en input par le joueur et renvoye une struct qui contient les cordonnees */ 
	Mouvement stockMouvement;
	if (mouvement != NULL)
	{
		if (strlen(mouvement) == 8)
		{
			stockMouvement.depart.x = convertCord(mouvement, 0);
			stockMouvement.depart.y = convertCoordY(atoi(mouvement+1), stockMouvement.depart.x);
			stockMouvement.range.x = convertCord(mouvement, 3);
			stockMouvement.range.y = convertCoordY(atoi(mouvement+4), stockMouvement.range.x );
			stockMouvement.arrive.x = convertCord(mouvement, 6);
			stockMouvement.arrive.y = convertCoordY(atoi(mouvement+7), stockMouvement.arrive.x);
			 
		}
		if (strlen(mouvement) == 5)
		{
			stockMouvement.depart.x = convertCord(mouvement, 0);
			stockMouvement.depart.y = convertCoordY(atoi(mouvement+1), stockMouvement.depart.x);
			stockMouvement.arrive.x = convertCord(mouvement, 3);
			stockMouvement.arrive.y = convertCoordY(atoi(mouvement+4), stockMouvement.arrive.x);
			stockMouvement.range.x = -1;
			stockMouvement.range.y = -1;
		}
	}
	else
		fprintf(stderr, "La fonction à eté appellé et aucun mouvement à eté fait!");
	return stockMouvement;
}
int convertCord(char *mouvement, int i)
{
	/*Fonction qui converti les cordonnees x de l'utilisateur en chiffres et les renvoye*/
	char car = mouvement[i];
	car = toupper(car);
	switch(car)
	{
		case 'A':
			return 9;
			break;
		case 'B':
			return 8;
			break;
		case 'C':
			return 7;
			break;
		case 'D':
			return 6;
			break;
		case 'E':
			return 5;
			break;
		case 'F':
			return 4;
			break;
		case 'G':
			return 3;
			break;
		case 'H':
			return 2;
			break;
		case 'I':
			return 1;
			break;
		default:
			printf("erreur");
	}
	return 0;
}

int convertCoordY(int posy, int posx)
{ /*Fonctions qui prends en argument les cordonnees de parseMouvement et les adapte au tableaux original et pas a celui affiché et renvoye la vraie coordonnees y sur le plateau d'origine*/
	if (posx==6)
		posy += 1;
	if (posx==7)
		posy +=2;
	if (posx==8)
		posy +=3;
	if (posx==9)
		posy +=4;
	if (posx == 4)
		posy -= 1;
	if (posx == 3)
		posy -= 2;
	if (posx == 2)
		posy -= 3;
	if (posx == 1)
		posy -= 4;

	return posy;
}

void deplace(char (*plateau)[COLONNE], Mouvement mouvement, char type_alignement, InfoPartie *infoPartiePtr, int legaliteint){
	if(mouvement.range.x == -1 && mouvement.range.y == -1){
		deplacementSing(mouvement, plateau, infoPartiePtr);
	}
	else{/*cas de deux ou trois billes à bouger*/
		switch(typeMouvement(mouvement, typeAlignement(mouvement, infoPartiePtr->joueurActuel), infoPartiePtr)){
			case 'l':
				deplacementLigne(plateau, mouvement, infoPartiePtr, legaliteint);
				break;
			case 's':
				deplacementLateral(plateau, mouvement, typeAlignement(mouvement, infoPartiePtr->joueurActuel), infoPartiePtr->joueurActuel);
				break;
		}
	}
}


void deplacementSing(Mouvement mouvement, char (*plateau)[COLONNE], InfoPartie* infoPartiePtr)
{
	/*Fonction qui deplace la bille singulaire dans le tab*/
	if (legaliteMouvementSing(mouvement, plateau))
	{
		if ((plateau[mouvement.depart.x][mouvement.depart.y] == 'B') && (plateau[mouvement.arrive.x][mouvement.arrive.y] == '.') && (infoPartiePtr->joueurActuel == 'B'))
		{
			plateau[mouvement.arrive.x][mouvement.arrive.y] = 'B';
			plateau[mouvement.depart.x][mouvement.depart.y] = '.';
		}
		else if ((plateau[mouvement.depart.x][mouvement.depart.y] == 'N') &&(plateau[mouvement.arrive.x][mouvement.arrive.y] == '.') && (infoPartiePtr->joueurActuel == 'N'))
		{
			plateau[mouvement.arrive.x][mouvement.arrive.y] = 'N';
			plateau[mouvement.depart.x][mouvement.depart.y] = '.';
		}
	}
}

void deplacementLigne(char(*plateau)[COLONNE], Mouvement mouvement, InfoPartie* infoPartiePtr, int legaliteint){
	int count, diffX, diffY;
	char joueur_adversaire;
	char joueur_actuel = infoPartiePtr->joueurActuel;
	if(joueur_actuel == 'B'){
		joueur_adversaire = 'N';
	}
	else
		joueur_adversaire = 'B';

	count = compteBilles(mouvement,  infoPartiePtr->joueurActuel);
	/*count = compteBilles(mouvement, joueur_actuel);*/

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

	/*soit on a deux bille, soit on en a trois, on les décale vers la direction du mouvement*/
	plateau[mouvement.depart.x][mouvement.depart.y] = '.';
	plateau[mouvement.depart.x + diffX * count][mouvement.depart.y + diffY * count] = joueur_actuel;
	switch(legaliteint){
		case 1: /*il faut decaler une bille adversaire*/
			plateau[mouvement.depart.x + (diffX * count) + diffX][mouvement.depart.y + (diffY * count) + diffY] = joueur_adversaire;
			break;
		case 2: /*il faut decaler deux billes adversaires*/
			plateau[mouvement.depart.x + (diffX * count) + diffX][mouvement.depart.y + (diffY * count) + diffY] = joueur_adversaire;
			plateau[mouvement.depart.x + (diffX * count) + diffX*2][mouvement.depart.y + (diffY * count) + diffY*2] = joueur_adversaire;
			break;
		default:
			break;
	}

}
void deplacementLateral(char(*plateau)[COLONNE], Mouvement mouvement, char type_alignement, char joueur_actuel){
	int count, diffX, diffY;
	count = compteBilles(mouvement,  joueur_actuel);
	switch(type_alignement){
		case 'h':
			diffY = +1;
			/*on bouge les billes à partir de la case de départ*/
			plateau[mouvement.depart.x][mouvement.depart.y] = '.';
			plateau[mouvement.depart.x][mouvement.depart.y + diffY] = '.';
			if(count == 3)
				plateau[mouvement.depart.x][mouvement.depart.y + diffY*2] = '.';
			/*on dessine les billes dans la nouvelle position*/
			plateau[mouvement.arrive.x][mouvement.arrive.y] = joueur_actuel;
			plateau[mouvement.arrive.x][mouvement.arrive.y + diffY] = joueur_actuel;
			if(count == 3)
				plateau[mouvement.arrive.x][mouvement.arrive.y + diffY*2] = joueur_actuel;
			break;
		case 'v':
			if(mouvement.depart.x - mouvement.range.x > 0)
				diffX = -1; /*cas ou la dernière bille se trouve dans les lignes inferieurs à celle où se trouve la bille de départ, cas inverse = -1;*/
			else if(mouvement.depart.x - mouvement.range.x <0) 
				diffX = +1;
			
			plateau[mouvement.depart.x][mouvement.depart.y] = '.';			
			plateau[mouvement.depart.x + diffX][mouvement.depart.y] = '.';
			if(count == 3)
				plateau[mouvement.depart.x + diffX*2][mouvement.depart.y] = '.';

			plateau[mouvement.arrive.x][mouvement.arrive.y] = joueur_actuel;
			plateau[mouvement.arrive.x + diffX][mouvement.arrive.y] = joueur_actuel;
			if(count == 3)
				plateau[mouvement.arrive.x + diffX*2][mouvement.arrive.y] = joueur_actuel;
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
			plateau[mouvement.depart.x][mouvement.depart.y] = '.';
			plateau[mouvement.depart.x + diffX][mouvement.depart.y + diffY] = '.';
			if(count == 3)
				plateau[mouvement.depart.x + diffX*2][mouvement.depart.y + diffY*2] = '.';

			plateau[mouvement.arrive.x][mouvement.arrive.y] = joueur_actuel;
			plateau[mouvement.arrive.x + diffX][mouvement.arrive.y + diffY] = joueur_actuel;
			if(count == 3)
				plateau[mouvement.arrive.x + 2*diffX][mouvement.arrive.y + diffY*2] = joueur_actuel;
			break;
	}
}


void help()
{ /*Fonction qui specifie les regles du jeu*/
	printf(" ________________________________ ABALONE - LE JEU ________________________________\n");
	printf("    															    \n");
	printf("  Abalone est un jeu français de stratégie. Il se joue a deux sur   \n");
	printf("  un plateau hexagonal composé par 61 case. Chaque joueur dispose   \n");
	printf("  de 14 billes, blanches et noires. Le but du jeu, est celui de     \n");
	printf("  pousser hors du tableau au moins 6 billes du joueur adversaire.   \n");
	printf("  Les joueurs peuvent deplacer de 1 à 3 billes a chaque manche si   \n");
	printf("  elles sont en ligne. Il a deux cas de deplacement, enligne ou	    \n");
	printf("  lateral														    \n");
	printf(" 													  			    \n");													  
	printf("  Les cordonnees - MOUVEMENT EN LIGNE:	 						    \n");
	printf("  -----------------------------------							    \n");
	printf("  Pour specifier les cordonnees il faut suivre des regle precise.   \n");
	printf("  		C3-C5-C4												    \n");
	printf("  Tout d'abord il faut specifier la bille MOTRICE,qui est toujours  \n");
	printf("  la derniere par rapport a la direction choisie. Ca veut dire:     \n");
	printf("  dans l'exemple precedent on choisi d'abord la bille MOTRICE, C3,  \n");
	printf("  ensuite on choisi la rangee, C5 qui indique donc le numero de     \n");
	printf("  billes a deplacer, 3 dans ce cas; et il faut determiner la        \n");
	printf("  position finale de la bille MOTRICE dans ce cas C4. Le mouvement  \n");
	printf("  est donc en ligne, vers la droite. Des exemple de mouvement       \n");
	printf("  																    \n");
	printf("               123 ---> 				Si on a trois billes 1,2,3  \n");
	printf(" 							pour les deplacer il faut   \n");
	printf(" 			ex: D4-D6-D5			choisir la bille MOTRICE    \n");
	printf(" 							(1), indiquer la position   \n");
	printf(" 							de la bille de rangee (3)   \n");
	printf(" 							et il faut donner la pos    \n");
	printf(" 							pour les deplacer sur la    \n");
	printf(" 							base de la bille MOTRICE,   \n");
	printf(" 							donc (2).				    \n");
	printf(" 																    \n");
	printf("  																    \n");
	printf("             <--- 123					Si on a trois billes 1,2,3  \n");
	printf("							pour les deplacer il faut   \n");
	printf(" 		    ex: C3-C1-C2			choisir la bille MOTRICE    \n");
	printf(" 							(3), indiquer la position   \n");
	printf(" 							de la bille de rangee (1)   \n");
	printf(" 							et il faut donner la pos    \n");
	printf(" 							pour les deplacer sur la    \n");
	printf(" 							base de la bille MOTRICE,   \n");
	printf(" 							donc (2).				    \n");
	printf(" 																    \n");
	printf("  																    \n");
	printf("               12 --->					Si on a deux billes 1,2     \n");
	printf(" 							pour les deplacer il faut   \n");
	printf(" 			ex: C1-C2-C2			choisir la bille MOTRICE    \n");
	printf(" 							(1), indiquer la position   \n");
	printf(" 							de la bille de rangee (2)   \n");
	printf(" 							et il faut donner la pos    \n");
	printf(" 							pour les deplacer sur la    \n");
	printf(" 							base de la bille MOTRICE,   \n");
	printf(" 							donc (2).				    \n");
	printf(" 																    \n");
	printf("  																    \n");
	printf("               1 --->					Si on a une bille           \n");
	printf("							pour la  deplacer il faut   \n");
	printf(" 		      ex: C1-C2 			choisir la bille MOTRICE    \n");
	printf(" 							(1),                        \n");
	printf(" 							et il faut donner la pos    \n");
	printf(" 							pour la  deplacer sur la    \n");
	printf(" 							base de la bille MOTRICE.   \n");
	printf("  Donc dans tous les cas du deplacement en ligne il faut imaginer   \n");
	printf("  un MOTEUR a traction posterieure dans le bloc qui pousse toutes   \n");
	printf("  les autres billes.											    \n");
	printf(" 																    \n");
	printf("  Les cordonnees - MOUVEMENT LATERAL:	 						    \n");
	printf("  -----------------------------------							    \n");
	printf("  Pour ce qui concerne le mouvement lateral, les choses changent.   \n");
	printf("  Dans ce type de mouvement en effet, il faut choisir la bille 	    \n");
	printf("  de depart la plus proche au bord ou se trouve le joueur dans le   \n");
	printf("  depart du match. Mais dans le cas d'alignement horizontal les 2   \n");
	printf("  joueurs specifie la bille la plus a gauche par rapport au tableau \n");
	printf("  affiché a l'ecran. 											    \n");
	printf("  Par example:													    \n");
	printf("        														    \n");
	printf("  		 ^					Pour bouger vers le haut le     \n");
	printf("        123						joueur choisi la bille 1 comme  \n");
	printf("							depart la 3 comme rangee        \n");
	printf("      	ex: C4-C6-D4					ou C4 est le depart, C6 la      \n");
	printf("							rangee et D4 la position finale \n");
	printf("        														    \n");
	printf("        														    \n");
	printf("  				        AMUSEZ VOUS BIEN!!!!!!      			    \n");
	printf(" __________________________________________________________________________________ \n");	
	exit(0);
}	
void humanVsHuman()
{
        char plateau[LIGNE][COLONNE];
    	Mouvement mouvement;
    	InfoPartie infoPartie;
    	char alignement, type_mouvement;
    	char *chaineJoueur = malloc(sizeof(char) * 100);
    	int count = 0;
    	int prova_legalita = 0, controllo_esistenza = 0;
    	InfoPartie *infoPartiePtr = &infoPartie;
    	/*Initialisation de la structure sur les info de la partie*/
    	infoPartiePtr->numeroBillesNoires = 14;
    	infoPartiePtr->numeroBillesBlanches = 14;
    	infoPartiePtr->joueurActuel = 'B';
    	creation_plateau(plateau);
    
    	while(1)
    	{
    	    printf("\n C'est au joueur: ");
    	    printf("\n ---------------");
        	if (count %2 == 0)
        	{
            	infoPartiePtr->joueurActuel = 'N';
            	printf("\n ****NOIR****\n");
        	}
        	else {
        	    infoPartiePtr->joueurActuel = 'B';
        	    printf("\n ****BLANC****\n");
       	 	}
        	affiche_plateau(plateau);
        	printf(" Cordonnees du prochain deplacement: ");
        	scanf("%s", chaineJoueur);
        	if(controleInput(chaineJoueur, plateau, infoPartiePtr)== 0)
        	{
        	    printf("Le mouvement saisi est incorrecte. Si vous ne savez pas la bonne syntaxe je vous renvoye a l'aide HELP");
        	    continue;            
        	}
   	    	mouvement = parseMouvement(chaineJoueur);
        	alignement = typeAlignement(mouvement, infoPartiePtr->joueurActuel);
        	type_mouvement = typeMouvement(mouvement, alignement,infoPartiePtr);
        	controllo_esistenza = controleExistanceMouvement(plateau, mouvement, infoPartiePtr, alignement);
        	if(controllo_esistenza == 0)
        	{
        	    printf("\n Le mouvement n'existe pas, ou vous ete en train de toucher les billes adversaires....dans ce cas TRICHEUR!");
        	    continue;
        	}
       		if ((prova_legalita = legalite(plateau, mouvement, infoPartiePtr, type_mouvement))!=0)
             	deplace(plateau, mouvement, typeMouvement(mouvement, alignement, infoPartiePtr), infoPartiePtr, prova_legalita);
       	 	printf("\n N° Billes deplacé = %d", compteBilles(mouvement, infoPartiePtr->joueurActuel));
        	if(prova_legalita == 0) continue;
        	count++;
    	}
   		free(chaineJoueur);
}
void executeTest(Test* modeTestPtr){
		
		int compteur_ligne = 0, i = 0, scan;
 		char* mov1 = malloc(100 * sizeof(char));
 		char* mov2 = malloc(100 * sizeof(char));
 		char** liste_movs = malloc(1*sizeof(char*));
    	while(1){
            scan = fscanf(stdin, "%s%s", mov1, mov2);
            if(feof(stdin))
            	if(scan == EOF){ printf("\nFIN FICHIER %d", compteur_ligne); break; }
            	else {printf("\nFIN ANORMALE"); break;}
	        /*printf("STR 1 = %s --- STR 2 = %s giro = %d \n", mov1, mov2, compteur_ligne);*/
	        if(!(strlen(mov1) == 8 || strlen(mov1) == 5)){
	        	/*printf("\nErreur dans la lecture du fichier TEST!\n");*/
	        	exit(0);
	        }  
			if(!(strlen(mov2) == 8 || strlen(mov2) == 5)){
	        	printf("\nErreur dans la lecture du fichier TEST!\n");
	        	exit(0);
	        }	        
	        liste_movs = realloc(liste_movs,((compteur_ligne+1)*4)*sizeof(char*));
	        liste_movs[compteur_ligne*2] = malloc(8*sizeof(char));
	        strcpy(liste_movs[compteur_ligne*2], mov1);

	        liste_movs[compteur_ligne*2+1] = malloc(8*sizeof(char));
	        strcpy(liste_movs[compteur_ligne*2+1], mov2);

	        /*printf("IN LISTA ... 1 = %s // 2 = %s , GIRO %d\n",liste_movs[compteur_ligne*2], liste_movs[compteur_ligne*2+1], compteur_ligne);*/
	        compteur_ligne++;
        }//fin while
        
        modeTestPtr->liste_movs = malloc(compteur_ligne*sizeof(char*));
        modeTestPtr->liste_movs = liste_movs;
        modeTestPtr->liste_longeur = compteur_ligne*2;
}


void modaliteTest()
{
		Test modeTest;
        char plateau[LIGNE][COLONNE];
    	Mouvement mouvement;
    	InfoPartie infoPartie;
    	char alignement, type_mouvement;
    	char *chaineJoueur = malloc(sizeof(char) * 100);
    	int count = 0;
    	int prova_legalita = 0, controllo_esistenza = 0;
    	InfoPartie *infoPartiePtr = &infoPartie;
    	/*Initialisation de la structure sur les info de la partie*/
    	infoPartiePtr->numeroBillesNoires = 14;
    	infoPartiePtr->numeroBillesBlanches = 14;
    	infoPartiePtr->joueurActuel = 'B';
    	creation_plateau(plateau);
    	executeTest(&modeTest);

    	while(1)
    	{
    	    printf("\n C'est au joueur: ");
    	    printf("\n ---------------");
        	if (count %2 == 0)
        	{
            	infoPartiePtr->joueurActuel = 'N';
            	printf("\n ****NOIR****\n");
        	}
        	else {
        	    infoPartiePtr->joueurActuel = 'B';
        	    printf("\n ****BLANC****\n");
       	 	}
        	affiche_plateau(plateau);
        	printf(" Cordonnees du prochain deplacement: ");
        	chaineJoueur = modeTest.liste_movs[count];
        	if(controleInput(chaineJoueur, plateau, infoPartiePtr)== 0)
        	{
        	    printf("Le mouvement saisi est incorrecte. Si vous ne savez pas la bonne syntaxe je vous renvoye a l'aide HELP");
        	    continue;            
        	}
   	    	mouvement = parseMouvement(chaineJoueur);
        	alignement = typeAlignement(mouvement, infoPartiePtr->joueurActuel);
        	type_mouvement = typeMouvement(mouvement, alignement,infoPartiePtr);
        	controllo_esistenza = controleExistanceMouvement(plateau, mouvement, infoPartiePtr, alignement);
        	if(controllo_esistenza == 0)
        	{
        	    printf("\n Le mouvement n'existe pas, ou vous ete en train de toucher les billes adversaires....dans ce cas TRICHEUR!");
        	    continue;
        	}
       		if ((prova_legalita = legalite(plateau, mouvement, infoPartiePtr, type_mouvement))!=0)
             	deplace(plateau, mouvement, typeMouvement(mouvement, alignement, infoPartiePtr), infoPartiePtr, prova_legalita);
       	 	printf("\n N° Billes deplacé = %d", compteBilles(mouvement, infoPartiePtr->joueurActuel));
        	if(prova_legalita == 0) continue;
        	count++;
    	}
   		free(chaineJoueur);
}

void robotVsRobot()
{
    	printf("\nEn construction, nous sommes en train d'y travailler, vous l'auriez avec la prochaine mise a jour\n");
    	exit(0);
}

void humanVsRobot()
{
    	printf("\nEn construction, nous sommes en train d'y travailler, vous l'auriez avec la prochaine mise a jour\n");
    	exit(0);
}

int menu()
{
	int choix;
	printf("____SUPER ABALONE____\n\n");
	printf(" 1. Human Vs Human \n");
	printf(" 2. Robot Vs Robot\n");
	printf(" 3. Human Vs Robot\n");
	printf(" 4. HELP \n");
	printf(" 5. Quitter\n ");

	while (choix == 0 || (choix < 0 || choix >5))
	{
		printf("\nVotre choix: ");
		scanf("%d", &choix);
		if (choix == 1)
			humanVsHuman();
		else if (choix == 2)
			robotVsRobot();
		else if(choix == 3)
			humanVsRobot();
		else if(choix == 4)
			help();
		else if(choix == 5)
			exit(0);
	}
}


void sauvegardePartie(char (*plateau)[COLONNE], InfoPartie* infoPartiePtr)
{
	int i,j;
	FILE *fichier;

	if ((fichier = fopen("sauvegarde.txt", "w")) == NULL)
		printf("Erreur à l'ouverture du fichier");
	else
	{
		for(i=0; i < LIGNE; i++)
		{
			for(j=0; j < COLONNE; j++)
				fprintf(fichier, "%c", plateau[i][j]);
			fprintf(fichier ,"\n");
		}

		fprintf(fichier, "%d %d %c", infoPartiePtr->numeroBillesBlanches, infoPartiePtr->numeroBillesNoires,  infoPartiePtr->joueurActuel);
		
	}
	
	fclose(fichier);
}


