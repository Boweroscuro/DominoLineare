//893323 
//gcc -O2 -std=c99 --pedantic *.c -o iap
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "GameManagement.h"

int main()
{
    //gioco
    nodo* game = NULL;      
    nodo* myT = NULL;

    int *temp;
    int n = 0;

    system("CLS");
    printf("\t\tDomino Lineare");
    printf("\nImmetti un numero di tessere con cui giocare: ");
    
    scanf("%i", &n);
    getchar();

    srand(time(0));

    for(int i = 0; i < n; i++) //riempimento delle tessere
    {
        int r = rand() % NumeroTessere;
        append(&myT, tessere[r][0], tessere[r][1]);
    }

    int sz = n;

    char s;
    printf("AI (y/n)?");
    s = getchar();

    system("CLS");
    PrintingGame(game, myT);
    
    if(s == 'y')
    {
        int i = 1;
        while(check_game(game, myT) && i <= sz)
        {
        
            temp = selectT(myT, i);

            if(check_tesseradx(game, temp, RIGHT))
            {
                append(&game, temp[0], temp[1]);  
                deleteTessera(&myT, i);
                i = 1;
                sz--;  
            }
            else if(check_tesserasx(game, temp, LEFT))
            {
                prepend(&game, temp[0], temp[1]);
                deleteTessera(&myT, i);
                i = 1;
                sz--;
            }
            i++;
            if(i > sz && check_game(game, myT)) i = 1;
            
        }
        system("CLS");
        PrintingGame(game, myT);
    }
    else
    {
        while(check_game(game, myT))
        {  
            int p = 0;
        
            scanf("%i", &p);
            getchar();

            if(p > 0 && p <= sz)
            {
                char c; 
                temp = selectT(myT, p);
                printf("Dove vuoi piazzarla(a/d): \n");
                c = getchar();
            
                if(check_tesseradx(game, temp, c))
                {
                    append(&game, temp[0], temp[1]);  
                    deleteTessera(&myT, p);
                    sz--;  
                }
                else if(check_tesserasx(game, temp, c))
                {
                    prepend(&game, temp[0], temp[1]);
                    deleteTessera(&myT, p);
                    sz--;
                }

                system("CLS");
                PrintingGame(game, myT);
            }
        }
    }

    printf("Hai fatto ben %i punti!\n", punteggio(game));

    freeList(game);
    freeList(myT);
    free(temp);
    
    return 0;
}
