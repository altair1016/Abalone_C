/* Created by Marco Iannella, Mattia Primavera*/

#include "abalone.h"


void creation_plateau(char (*plateau)[COLONNE]){
    /*Fonction qui crée le plateau a partir d'une chaine de Default*/
    char *chainePlateau= "------EEEEE/NNNNN\\EEEE/NNNNNN\\EEE/..NNN..\\EE/........\\E ......... D\\......../EC\\..BBB../EEB\\BBBBBB/EEEA\\BBBBB/EEEEE------";
    memcpy(plateau, chainePlateau, LENGTH);
} 
void affiche_de_base(char (*plateau)[COLONNE])
{
    /*Fonction qui affiche le vrai tableau....elle n'est pas utile pour l'utilisateur, mais pour le programmeur*/
    int i=0, j=0;
    for (i=0; i < LIGNE; i++)
    {
        printf("\n");
        for(j=0; j <COLONNE; j++)
            printf("%c ", plateau[i][j]);
    }
    printf("\n\n");
}
void affiche_plateau(char (*plateau)[COLONNE])
{
    /*Fonction qui affiche le plateau selon le modèle proposé*/
    int i,j, espaceTotales = 6, espace, entier=9;
    int car = 73;
    for(i=0; i<11; i++)
    {
        printf("\n");
        if (i==0)
            printf("  ");
        if (i ==10)
            printf(" ");
        espace=espaceTotales;
        if(i>=6)
                printf("  ");
        for(j=0; j<11; j++)
        {
            for (espace=espace; espace >=1; espace--)
            {
                printf(" ");
            }
            if (((j==0)&& i != 0 && (i <= 5)))
                printf("%c ", car--);
            if (plateau[i][j] != 'E')
                printf("%c ",  plateau[i][j]);
            else 
                printf(" ");
        }
        if (i > 6)
        {
            printf("%d", entier);
            entier--;
        }
        espaceTotales--;
    }
    printf("\n           1 2 3 4 5");
    printf("\n\n");
}