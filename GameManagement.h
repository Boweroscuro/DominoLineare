#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define LEFT 'a'
#define RIGHT 'd'

/**
 * Domino lineare
 * semplice giochetto scritto in c
 * Tessere speciali:
 * 0|0 -> può essere accostata a qualunque altra tessera. Esempio: [1|2][0|0][5|6]
 * 11|11 -> somma 1 a tutte le cifre di tutte le tessere sul piano di gioco tranne il 6 che diventa 1. La tessera può essere posizionata in qualunque posizione e le sue cifre vegono sostituite con la cifra adiacente dopo averla incrementata di 1. Esempio: [1|6][6|3][11|11] diventa [2|1][1|4][4|4]
 * 12|21 -> copia “a specchio” la tessera adiacente. La tessera può essere posizionata in qualunque posizione e le sue cifre vegono sostituite con le cifre della tessera adiacente in ordine inverso. Esempio: [1|2][2|3][12|21] diventa [1|2][2|3][3|2]
 * 
 * @author  Francesco Gerlin
 */


int tessere[24][2] = {  {0, 0}, {1, 1}, {1, 2}, {1, 3}, {1, 4}, {1, 5}, {1, 6},
                        {2, 2}, {2, 3}, {2, 4}, {2, 5}, {2, 6},
                        {3, 3}, {3, 4}, {3, 5}, {3, 6},
                        {4, 4}, {4, 5}, {4, 6},
                        {5, 5}, {5, 6},
                        {6, 6}, {11, 11} , {12, 21} };

int NumeroTessere = 24;

/**
 * Print delle tessere disponibili nel gioco
*/
void printTessere()
{
    for(int i = 0; i < 2; i++)
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

/**
 * Crea una nuova tessera
 * @param int x 
 * @param int y
 * @return nodo* la tessera creata
*/
nodo* createNodo(int x, int y)
{
    nodo* n = (nodo*) malloc(sizeof(nodo));
    n -> x = x;
    n -> y = y;
    n -> next = NULL;
    return n; 
}

/**
 * Mette la tessera all'inizio della lista
 * @param nodo**
 * @param int x
 * @param int y
*/
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

/**
 * Mette la tessera alla fine della lista
 * @param nodo**
 * @param int x
 * @param int y
*/
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

/**
 * Stampa il gioco
 * @param nodo* la lista in cui inserisce le tessere da giocare
 * @param nodo* T le tue tessere che vuoi giocare
*/
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

/**
 * Dealloca la memoria dinamica della lista
 * @param nodo* l
*/
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

/**
 * Selezione la tessera che vuoi giocare
 * @param nodo* T la lista di tessere
 * @param int p la posizione della tessera
 * @return un array di dimensione 2 contenente la x e la y della tessera
*/
int* selectT(nodo* T, int p)
{   
    nodo* curr = T;  
    int* aux = (int*) malloc(sizeof(int) * 2);

    int j = 0;
    while(j != p - 1)
    {
        curr = curr -> next;
        j++;
    }

    aux[0] = curr -> x;
    aux[1] = curr -> y;
    return aux;
}

/**
 * Controlla che esistino ancora possibili tessere inseribili nel gioco
 * @param nodo* g Gioco
 * @param nodo* T tessere in tuo possesso
 * @return bool true o false
*/
bool check_game(nodo* g, nodo* T)
{
    nodo* currg = g;
    nodo* currt = T;
    int x, y;

    if(currg == NULL) return true;

    x = currg -> x;
    while(currg -> next != NULL) currg = currg -> next;
    y = currg -> y;

    if(x == 0 || y == 0 || x == 11 || y == 11 ||  x == 12 || y == 21) return true;

    int count = 0;
    while(currt != NULL)
    {
        if(currt -> x == x || currt -> x == y || currt -> y == x || currt -> y == y) count++;
        else if(currt -> x == 0 || currt -> y == 0) count++;
        else if(currt -> x == 11 || currt -> y == 11) count++;
        else if(currt -> x == 12 || currt -> y == 21) count++;
        currt = currt -> next;
    }

    return count;
}

/**
 * sum_tessere serve per aumentare e sistemare le tessere che sono state modificate dalla tessera 11|11
 * @param nodo* il gioco
 * @return true cosi check_tessere finisce subito
*/
bool sum_tessere(nodo* g)
{
    nodo* curr = g;

    while(curr != NULL)
    {
        curr -> x += 1;
        curr -> y += 1;
        if(curr -> x > 6) curr -> x = 1;
        if(curr -> y > 6) curr -> y = 1;
        curr = curr -> next;
    }

    return true;
}

/**
 * controllo la prima tessera di game
 * @param nodo* game
 * @param int* la tessera selezionata da selectT 
 * @param char che il char selezionato sia uguale a quello impostato su RIGHT
 * @return bool true o false 
*/
bool check_tesseradx(nodo* game, int *temp, char c)
{   
    if(c == RIGHT)
    {
        if((temp[0] == 0 || temp[0] == 12 || temp[0] == 11) && game == NULL) return false;

        nodo* it = game;

        if(it == NULL) return true;
        if(temp[0] == 0) return true;

        while(it -> next != NULL) it = it -> next;

        if(temp[0] == 12)
        {
            temp[0] = it -> y;
            temp[1] = it -> x;
            return true;
        }

        if(temp[0] == 11)
        {
            temp[0] = it -> y;
            temp[1] = it -> y;
            return sum_tessere(game);
        }

        if(it -> y == 0) return true;

        if(it -> y == temp[0] || it -> y == temp[1])
        { 
            if(it -> y == temp[0]) return true;
            else
            {
                int aux = temp[0];
                temp[0] = temp[1];
                temp[1] = aux;
                return true;
            }
        }
    }
    
    return false;
}


/**
 * controllo l'ultima tessera di game
 * @param nodo* game
 * @param int* la tessera selezionata da selectT 
 * @param char che il char selezionato sia uguale a quello impostato su LEFT
 * @return bool true o false 
*/
bool check_tesserasx(nodo* game, int *temp, char c)
{   
    if(c == LEFT)
    {
        
        if((temp[0] == 0 || temp[0] == 12 || temp[0] == 11) && game == NULL) return false;

        nodo* it = game;

        if(it == NULL) return true;
        if(temp[0] == 0) return true;

        if(temp[0] == 11)
        {
            temp[0] = it -> x;
            temp[1] = it -> x;
            return sum_tessere(game);
        }

        if(temp[0] == 12)
        {
            temp[0] = it -> y;
            temp[1] = it -> x;
            return true;
        }

        if(it -> x == 0) return true;
        
        if(it -> x == temp[0] || it -> x == temp[1])
        { 
            if(it -> x == temp[1])
            {
                return true;
            }
            else
            {
                int aux = temp[0];
                temp[0] = temp[1];
                temp[1] = aux;
                return true;
            }
        }
    }
    return false;
}

/**
 * Cancella la tessera selezionata e inserita dentro al gioco
 * @param nodo** lista delle tessere
 * @param int posizione della tessera
*/
void deleteTessera(nodo** T, int pos) 
{
    nodo* curr = *T;
    
    if(pos == 1)
    {
        *T = curr-> next;
    }
    else
    {
        int i = 1;
        while(i != pos - 1)
        {
            i++;
            curr = curr -> next;    
        }

        nodo* temp = curr -> next;
        curr -> next = curr->next->next;
        free(temp);
    }
}

/**
 * somma tutte le tessere
 * @param nodo* g il gioco
 * @return un intero il punteggio
*/
int punteggio(nodo* g)
{
    nodo* curr = g;
    int sum = 0;

    while(curr != NULL)
    {
        sum += curr -> x + curr -> y;
        curr = curr -> next;
    }

    return sum;
}