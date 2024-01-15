//893323
#include<stdio.h>
#include<stdlib.h>
#include "GameManagement.c"

int main()
{
    system("CLS");
    printf("\t\tDomino Lineare");
    //printTessere();
    printf("\nImmetti un numero di tessere con cui giocare: ");

    int n = 0;
    //scanf("%i", &n);
    //getchar();

    nodo* game = NULL;
    nodo* myT = NULL;

    system("CLS");

    for(int i = 0; i < 10; i++)
    {
        prepend(&myT, i, i+1);
        prepend(&game, i, i+1);
    }
    
    printf("\n gioco: \n");
    
    PrintingGame(game, myT);

    return 0;
}
