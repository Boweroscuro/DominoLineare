#include<stdio.h>
#include<stdlib.h>

//ricontrolla tutto le liste che qua non va un cazzo

int tessere[22][2] = {  {0, 0}, {1, 1}, {1, 2}, {1, 3}, {1, 4}, {1, 5}, {1, 6},
                        {2, 2}, {2, 3}, {2, 4}, {2, 5}, {2, 6},
                        {3, 3}, {3, 4}, {3, 5}, {3, 6},
                        {4, 4}, {4, 5}, {4, 6},
                        {5, 5}, {5, 6},
                        {6, 6}};

void printTessere()
{
    for(int i = 0; i < 22; i++)
    {
        if(i % 3 == 0) printf("\n\n");
        printf("|\t %i - [%i|%i] \t| ", i, tessere[i][0], tessere[i][1]);
    }
}

struct lista{
    int T[2];
    struct lista* next;
}typedef nodo; //per la facilit� ad inserire sia a destra che sinistra le tessere

nodo* createNodo(int x, int y)
{
    nodo* n = (nodo*) malloc(sizeof(nodo));
    n -> T[0] = x;
    n -> T[1] = y;
    return n; 
}

void prepend(nodo** l, int x, int y)
{
    nodo* n_nodo = createNodo(x , y);
    if(*l == NULL) 
    {
        *l = n_nodo;
    }
    else
    {
        n_nodo -> next = *l;
        *l = n_nodo;
    }   
}

void append(nodo** l, int x, int y)
{
    nodo* n_nodo = createNodo(x, y);
    if(*l == NULL)
    {
        *l = n_nodo;
    }
    else
    {
        nodo* curr = *l;
        if(curr -> next == NULL) printf("si cazzo");
        while(curr -> next != NULL) curr = curr -> next;
        curr -> next = n_nodo;
        curr = n_nodo;
    }
}

void PrintingGame(nodo* g, nodo* T)
{
    nodo* aux = g;
    printf("\t");
    while(aux != NULL)
    {
        printf("[%i|%i]", aux -> T[0], aux -> T[1]);
        aux = aux -> next;
    }
    printf("\n");

    printf("Le tue tessere:\n");
    nodo* Taux = T; 
    while(Taux != NULL)
    {
        printf("[%i|%i]", Taux -> T[0], Taux -> T[1]);
        Taux = Taux -> next;
    }
    printf("\n");
}
