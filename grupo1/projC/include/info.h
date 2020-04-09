#ifndef ___INFO_H___
#define ___INFO_H___

#include <glib.h>

typedef struct info* Info;

typedef struct aux* Aux;

typedef struct money* Money;

typedef struct querie8Aux* Querie8Aux;

typedef struct querie9Aux* Querie9Aux;

int compareMoney(gconstpointer, gconstpointer);

Money cloneMoney(Money);

void freeMoney(Money);

Aux cloneAux(Aux);

void freeAux(Aux);

int compareAux(gconstpointer, gconstpointer);

int compareInfo(gconstpointer, gconstpointer);

Info cloneInfo(Info);

void freeInfo(Info);

Money initMoney(char*, double);

void updateMoney(Money, double);

void updateAux(Aux, int, int *);

Aux initAux(char*, int, int *);

void updateInfo(Info, int);

Info initInfo(char*, int);

void freeInfoList(Info*);

void freeAuxList(Aux*);

void freeMoneyList(Money*);

char* getInfoProduct(Info info);

char* getAuxProduct(Aux aux);

int getAuxUnitsSold(Aux aux, int);

int getAuxTotalClients(Aux aux, int);

char* getMoneyProduct(Money money);

double getMoneySpent(Money money);

int getInfoUnitsSold(Info info);

void updateQuerie8(Querie8Aux, double, int, int);

Querie8Aux initQuerie8Aux();

int getQuerie8AuxUnits(Querie8Aux);

double getQuerie8AuxBilled(Querie8Aux);

int getQuerie8AuxSales(Querie8Aux);

void freeQuerie8Aux(Querie8Aux);
/*
void updateQuerie9(Querie9Aux, double, int, int);

Querie8Aux initQuerie9Aux();

int getQuerie9AuxUnits(Querie9Aux);

double getQuerie9AuxBilled(Querie9Aux);

int getQuerie9AuxSales(Querie9Aux);

void freeQuerie9Aux(Querie9Aux);*/

void updateTotalN(Querie9Aux);

void updateTotalP(Querie9Aux);

int getQuerie9TotalN(Querie9Aux aux);

int getQuerie9TotalP(Querie9Aux aux);

Querie9Aux initQuerie9Aux(int);

void updateClientsN(Querie9Aux, int, char*);

void updateClientsP(Querie9Aux, int, char*);

void updateClients(Querie9Aux, int, int);

char * getQuerie9ClientN(Querie9Aux, int);

char * getQuerie9ClientP(Querie9Aux, int);

void freeQuerie9Aux(Querie9Aux);

#endif
