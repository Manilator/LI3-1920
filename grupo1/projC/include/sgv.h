/**
@file sgv.h
\brief Módulo de sistema de gestão de vendas
*/
#ifndef ___SGV__H___
#define ___SGV__H___

#include "info.h"

#include <glib.h>

typedef struct sgv* SGV;

typedef struct startValues* StartValues;

SGV startSGV(SGV, StartValues);

SGV initSGV();

StartValues initStartValues();

void setPathsSV(StartValues, char*, char*, char*);

/*2*/
char ** getProductsStartedByLetter(SGV, char);

/*3*/
double * getProductSalesAndProfit(SGV, char* , int, int);

/*4*/
char *** getProductsNeverBought(SGV, int);

/*5*/
char** getClientsOfAllBranches(SGV);

/*6*/
int * getClientsAndProductsNeverBoughtCount(SGV);

/*7*/
int ** getProductsBoughtByClient(SGV, char*);

/*8*/
Querie8Aux getSalesAndProfit(SGV, int, int);

/*9*/
Querie9Aux getProductBuyers(SGV, char*, int);

/*10*/
Info * getClientsFavoriteProducts(SGV, char*, int);

/*11*/
Aux * getTopSoldProducts(SGV, int);

/*12*/
Money * getClientTopProfitProducts(SGV, char*, int);

char* getClientsPath(StartValues);

char* getProductsPath(StartValues);

char* getSalesPath(StartValues);

int getValidClients(StartValues);

int getValidProducts(StartValues);

int getValidSales(StartValues);

int getReadClients (StartValues);

int getReadProducts (StartValues);

int getReadSales (StartValues);


int listSize(char**);

void destroySGV(SGV);

void destroyStartValues(StartValues);

void freeStringList(char **);

void freeStringMatrix(char ***);

void freeIntMatrix(int **);

#endif
