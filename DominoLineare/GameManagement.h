#include"GameManagement.c"

void printTessere();
nodo* createNodo(int x, int y);
void prepend(nodo** l, int x, int y);
void append(nodo** l, int x, int y);
void PrintingGame(nodo* g, nodo* T);
void freeList(nodo* l);