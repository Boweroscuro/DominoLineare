#include <stdio.h>
#include <stdlib.h>

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
        if(i % 5 == 0) printf("\n\n");
        printf("|\t %i - [%i|%i] \t| ", i, tessere[i][0], tessere[i][1]);
    }
}

struct lista{
    int x;
    int y;
    struct lista* next;
}typedef nodo; //per la facilit� ad inserire sia a destra che sinistra le tessere

nodo* createNodo(int x, int y)
{
    nodo* n = (nodo*) malloc(sizeof(nodo));
    n -> x = x;
    n -> y = y;
    n -> next = NULL;
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
        while(curr -> next != NULL) curr = curr -> next;
        curr -> next = n_nodo;
    }
}

void PrintingGame(nodo* g, nodo* T)
{
    nodo* aux = g;
    while(aux != NULL)
    {
        printf("[%i|%i]", aux -> x, aux -> y);
        aux = aux -> next;
    }
    printf("\n");

    printf("\n\tLe tue tessere:\n");
    nodo* Taux = T; 
    int i = 0;
    while(Taux != NULL)
    {
        if(i % 5 == 0) printf("\n");
        printf("[%i|%i] ", Taux -> x, Taux -> y);
        Taux = Taux -> next;
        i++;
    }
    printf("\n");
}

void freeList(nodo* l)
{
    nodo* temp = l;
    while(l != NULL)
    {
        temp = l;
        l = l-> next;
        free(temp);
    }
}
