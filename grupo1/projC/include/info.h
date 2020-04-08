#ifndef ___INFO_H___
#define ___INFO_H___

#include <glib.h>

typedef struct info{
  char * product_code;
  int unitsSold;
}*Info;

typedef struct aux{
  char * product_code;
  int * totalClients;
  int * unitsSold;
}*Aux;


typedef struct money{
  char * product_code;
  double moneySpent;
}*Money;


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

#endif
