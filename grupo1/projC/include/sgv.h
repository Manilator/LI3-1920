#ifndef ___SGV__H___
#define ___SGV__H___

#include "info.h"

#include <glib.h>

typedef struct sgv* SGV;

typedef struct startValues* StartValues;

SGV startSGV(SGV, StartValues);

SGV initSGV();

StartValues initStartValues(char*, char*, char*);

char ** productsByLetter(SGV, char);

double * productValuesByMonth(SGV, char* , int, int);

char *** productsNotBought(SGV, int);

int * productsClientsNotUsed(SGV);

int ** clientShoppingLog(SGV, char*);

Info * clientMostBoughtByMonth(SGV, char*, int);

Aux * nMostBought(SGV, int);

char* getClientsPath(StartValues);

char* getProductsPath(StartValues);

char* getSalesPath(StartValues);

int getValidClients(StartValues);

int getValidProducts(StartValues);

int getValidSales(StartValues);

int getReadClients (StartValues);

int getReadProducts (StartValues);

int getReadSales (StartValues);

char** query5(SGV);

char *** query9(SGV, char*, int, int*, int*);
/*void query9(SGV);*/

Querie8Aux query8(SGV, int, int);

int listSize(char**);

Money * query12(SGV, char*, int);

void freeStringList(char **);

void freeStringMatrix(char ***);

void freeIntMatrix(int **);

#endif
