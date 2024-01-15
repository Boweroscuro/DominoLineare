//893323
#include <stdio.h>
#include <stdlib.h>
#include "GameManagement.h"

nodo* game = NULL;    nodo* myT = NULL;

int main()
{
    system("CLS");
    printf("\t\tDomino Lineare");
    //printTessere();
    printf("\nImmetti un numero di tessere con cui giocare: ");

    int n = 0;
    scanf("%i", &n);
    getchar();

    system("CLS");

    for(int i = 0; i < n; i++)
    {
        append(&myT, i, i+1);
        append(&game, i, i+1);
    }
    
    printf("\n");

    PrintingGame(game, myT);

    freeList(game);
    freeList(myT);

    return 0;
}
