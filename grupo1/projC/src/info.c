#include "info.h"
#include "constants.h"
#include <string.h>

struct info{
  char * product_code;
  int unitsSold;
};

struct querie8Aux{
  int totalUnits;
  int totalSales;
  double totalBilled;
};

struct querie9Aux{
    char ** clientsN;
    char ** clientsP;
    int totalN;
    int totalP;
};

struct aux{
  char * product_code;
  int * totalClients;
  int * unitsSold;
};

struct money{
  char * product_code;
  double moneySpent;
};


Querie8Aux initQuerie8Aux(){
    Querie8Aux aux = g_malloc(sizeof(struct querie8Aux));
    aux->totalBilled = 0.0f;
    aux->totalUnits  = 0;
    aux->totalSales = 0;

    return aux;
}

int getQuerie8AuxUnits(Querie8Aux aux){
    return aux->totalUnits;
}

double getQuerie8AuxBilled(Querie8Aux aux){
    return aux->totalBilled;
}

int getQuerie8AuxSales(Querie8Aux aux){
    return aux->totalSales;
}

void updateQuerie8(Querie8Aux aux, double billed, int units, int sales){
    aux->totalBilled += billed;
    aux->totalUnits  += units;
    aux->totalSales += sales;
}

void freeQuerie8Aux(Querie8Aux aux){
    g_free(aux);
}

int compareMoney(gconstpointer a, gconstpointer b)
{
    Money money1 = (const Money)a;
    Money money2 = (const Money)b;
    return (money2->moneySpent) - (money1->moneySpent);
}

Money cloneMoney(Money money)
{
    Money clone = g_malloc(sizeof(struct money));

    clone->product_code = strdup(money->product_code);
    clone->moneySpent = money->moneySpent;

    return clone;
}

void freeMoney(Money money)
{
    g_free(money->product_code);
}


Aux cloneAux(Aux aux){
    Aux clone = g_malloc(sizeof(struct aux));
    clone->totalClients = g_malloc(sizeof(int*)*N_BRANCHES);
    clone->unitsSold = g_malloc(sizeof(int*)*N_BRANCHES);

    clone->product_code = strdup(aux->product_code);
    int i;
    for (i = ZERO; i < N_BRANCHES; i++) {
        clone->unitsSold[i] = aux->unitsSold[i];
        clone->totalClients[i] = aux->totalClients[i];
    }
    return clone;
}

void freeAux(Aux aux){
    g_free(aux->product_code);
    g_free(aux->totalClients);
    g_free(aux->unitsSold);
}

int compareAux(gconstpointer a, gconstpointer b){
    Aux n1 = (const Aux)a;
    Aux n2 = (const Aux)b;
    int total1=0,total2=0;
    int i;
    for (i = 0; i < N_BRANCHES; i++) {
        total1 += n1->unitsSold[i];
        total2 += n2->unitsSold[i];
    }
    return total2 - total1;
}

int compareInfo(gconstpointer a, gconstpointer b){
    Info info1 = (const Info)a;
    Info info2 = (const Info)b;
    return (info2->unitsSold) - (info1->unitsSold);
}

void freeInfo(Info info){
    g_free(info->product_code);

}

Info cloneInfo(Info info){
    Info clone = g_malloc(sizeof(struct info));
    clone->product_code = strdup(info->product_code);

    clone->unitsSold = info->unitsSold;
    return clone;
}

Money initMoney(char* key, double value)
{
    Money money = g_malloc(sizeof(struct money));
    money->product_code = strdup(key);

    money->moneySpent = value;
    return money;
}

void updateMoney(Money money, double value)
{
    (money->moneySpent) += value;
}


void updateAux(Aux aux, int branch, int * value){
    (aux->totalClients[branch])++;
    int i;
    for (i = ZERO; i < MONTHS; i++)
        aux->unitsSold[branch] += value[i];
}


Aux initAux(char* key, int branch, int * value){
    Aux aux = g_malloc(sizeof(struct aux));
    aux->totalClients = g_malloc(sizeof(int*)*N_BRANCHES);
    aux->unitsSold = g_malloc(sizeof(int*)*N_BRANCHES);

    aux->product_code = strdup(key);
    int i;
    for (i = ZERO; i < N_BRANCHES; i++) {
        aux->unitsSold[i] = ZERO;
        aux->totalClients[i] = ZERO;
    }

    aux->totalClients[branch] = ONE;
    for (i = ZERO; i < MONTHS; i++)
        aux->unitsSold[branch] += value[i];

    return aux;
}

void updateInfo(Info info, int value){
    (info->unitsSold) += value;
}


Info initInfo(char* key, int value){
    Info info = g_malloc(sizeof(struct info));
    info->product_code = strdup(key);

    info->unitsSold = value;
    return info;
}

void freeInfoList(Info* list){
    int i = 0;
    while(list[i] != NULL){
        freeInfo(list[i++]);
    }
}

void freeAuxList(Aux* list){
    int i = 0;
    while(list[i] != NULL){
        freeAux(list[i++]);
    }
}

void freeMoneyList(Money* list){
    int i = 0;
    while(list[i] != NULL){
        freeMoney(list[i++]);
    }
}

char* getInfoProduct(Info info){
    return info->product_code;
}

char* getAuxProduct(Aux aux){
    return aux->product_code;
}

char* getMoneyProduct(Money money){
    return money->product_code;
}

int getInfoUnitsSold(Info info){
    return info->unitsSold;
}

double getMoneySpent(Money money){
    return money->moneySpent;
}

int getAuxUnitsSold(Aux aux, int i){
    return aux->unitsSold[i];
}

int getAuxTotalClients(Aux aux, int i){
    return aux->totalClients[i];
}

void updateTotalN(Querie9Aux aux){
    (aux->totalN)++;
}

void updateTotalP(Querie9Aux aux){
    (aux->totalP)++;
}

int getQuerie9TotalN(Querie9Aux aux){
    return aux->totalN;
}

int getQuerie9TotalP(Querie9Aux aux){
    return aux->totalP;
}

Querie9Aux initQuerie9Aux(int size){
    Querie9Aux aux = g_malloc(sizeof(struct querie9Aux));
    aux->clientsN = g_malloc(sizeof(char*)*size);
    aux->clientsP = g_malloc(sizeof(char*)*size);
    aux->totalN  = 0;
    aux->totalP = 0;

    return aux;
}

void updateClientsN(Querie9Aux aux, int i, char* key){
    aux->clientsN[i] = strdup(key);
}

void updateClientsP(Querie9Aux aux, int i, char* key){
    aux->clientsP[i] = strdup(key);
}

void updateClients(Querie9Aux aux, int i, int j){
    aux->clientsN[i] = NULL;
    aux->clientsP[j] = NULL;
}

char * getQuerie9ClientN(Querie9Aux aux, int i){
    return aux->clientsN[i];
}

char * getQuerie9ClientP(Querie9Aux aux, int i){
    return aux->clientsP[i];
}

void freeQuerie9Aux(Querie9Aux aux){
    int i=0;
    while(aux->clientsP[i] != NULL)
        g_free(aux->clientsP[i++]);
    i = 0;
    while(aux->clientsN[i] != NULL)
        g_free(aux->clientsN[i++]);
}
