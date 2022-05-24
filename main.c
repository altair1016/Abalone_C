/* Created by Marco Iannella, Mattia Primavera*/

#include "abalone.h"

int main(int argc, char **argv)
{
    if (argv[1] != NULL)
    {
        if (strcmp(argv[1], "-m")==0|| strcmp(argv[1], "-M")==0)
        {
            menu();
        }
        else if(strcmp(argv[1], "-h")==0|| strcmp(argv[1], "-H")==0)
        {
            help();
        }
        else if (strcmp(argv[1], "-rvsr" )==0|| strcmp(argv[1], "-RVSR")==0)
        {
            robotVsRobot();
        }
        else if (strcmp(argv[1], "-hvsr")==0|| strcmp(argv[1], "-HVSR")==0)
        {
            humanVsRobot();
        }
        else if(strcmp(argv[1], "-t") == 0)
            modaliteTest();
    }
    else
            humanVsHuman();
    
    return 0;
}

