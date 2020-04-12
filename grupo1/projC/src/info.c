#include "info.h"
#include "constants.h"

#include <string.h>


/* ----------------- */
/* STRUCT DEFINITION */
/* ----------------- */

struct querie8Aux{
  int totalUnits; /**< Número total de unidades */
  int totalSales; /**< Número total de vendas */
  double totalBilled; /**< Faturação total */
};

struct querie9Aux{
    char ** clientsN; /**< Array de códigos de cliente com compras no tipo N */
    char ** clientsP; /**< Array de códigos de cliente com compras no tipo P */
    int totalN; /**< Número total de compras no tipo N */
    int totalP; /**< Número total de compras no tipo P */
};

struct info{
  char * product_code; /**< Código de produto */
  int unitsSold; /**< Número de unidades vendidas */
};

struct aux{
  char * product_code; /**< Código de produto */
  int * totalClients; /**< Array com total de clientes por mês */
  int * unitsSold; /**< Array com total de unidades vendidas por mês */
};

struct money{
  char * product_code; /**< Código de produto */
  double moneySpent; /**< Valor gasto */
};

/* --------------- */
/* INIT DEFINITION */
/* --------------- */

Query8Aux initQuery8Aux(){
    Query8Aux aux = g_malloc(sizeof(struct querie8Aux));
    aux->totalBilled = 0.0f;
    aux->totalUnits  = 0;
    aux->totalSales = 0;

    return aux;
}

Query9Aux initQuery9Aux(int size){
    Query9Aux aux = g_malloc(sizeof(struct querie9Aux));
    aux->clientsN = g_malloc(sizeof(char*)*size);
    aux->clientsP = g_malloc(sizeof(char*)*size);
    aux->totalN  = 0;
    aux->totalP = 0;

    return aux;
}

Info initInfo(char* key, int value){
    Info info = g_malloc(sizeof(struct info));
    info->product_code = strdup(key);

    info->unitsSold = value;
    return info;
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

Money initMoney(char* key, double value){
    Money money = g_malloc(sizeof(struct money));
    money->product_code = strdup(key);

    money->moneySpent = value;
    return money;
}

/* ------------------ */
/* COMPARE DEFINITION */
/* ------------------ */

int compareInfo(gconstpointer a, gconstpointer b){
    Info info1 = (const Info)a;
    Info info2 = (const Info)b;
    return (info2->unitsSold) - (info1->unitsSold);
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

int compareMoney(gconstpointer a, gconstpointer b){
    Money money1 = (const Money)a;
    Money money2 = (const Money)b;
    return (money2->moneySpent) - (money1->moneySpent);
}

/* ---------------- */
/* CLONE DEFINITION */
/* ---------------- */

Info cloneInfo(Info info){
    Info clone = g_malloc(sizeof(struct info));
    clone->product_code = strdup(info->product_code);

    clone->unitsSold = info->unitsSold;
    return clone;
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

Money cloneMoney(Money money){
    Money clone = g_malloc(sizeof(struct money));

    clone->product_code = strdup(money->product_code);
    clone->moneySpent = money->moneySpent;

    return clone;
}

/* --------------- */
/* FREE DEFINITION */
/* --------------- */

void freeQuery8Aux(Query8Aux aux){
    g_free(aux);
}

void freeQuery9Aux(Query9Aux aux){
    if(aux != NULL){
        int i=0;
        while(aux->clientsP[i] != NULL)
            g_free(aux->clientsP[i++]);
        i = 0;
        while(aux->clientsN[i] != NULL)
            g_free(aux->clientsN[i++]);

        if(aux->clientsN != NULL)
            g_free(aux->clientsN);
        if(aux->clientsP != NULL)
            g_free(aux->clientsP);
        g_free(aux);
    }
}

void freeInfo(Info info){
    g_free(info->product_code);
    g_free(info);
}

void freeInfoList(Info* list){
    if(list != NULL){
        int i = 0;
        while(list[i] != NULL){
            freeInfo(list[i++]);
        }
        g_free(list);
    }
}

void freeAux(Aux aux){
    g_free(aux->product_code);
    g_free(aux->totalClients);
    g_free(aux->unitsSold);
    g_free(aux);
}

void freeAuxList(Aux* list){
    if(list != NULL){
        int i = 0;
        while(list[i] != NULL){
            freeAux(list[i++]);
        }
        g_free(list);
    }
}

void freeMoney(Money money)
{
    g_free(money->product_code);
    g_free(money);
}

void freeMoneyList(Money* list){
    if(list != NULL){
        int i = 0;
        while(list[i] != NULL){
            freeMoney(list[i++]);
        }
        g_free(list);
    }
}

/* ----------------- */
/* UPDATE DEFINITION */
/* ----------------- */

void updateQuerie8(Query8Aux aux, double billed, int units, int sales){
    aux->totalBilled += billed;
    aux->totalUnits  += units;
    aux->totalSales += sales;
}

void updateTotalN(Query9Aux aux){
    (aux->totalN)++;
}

void updateTotalP(Query9Aux aux){
    (aux->totalP)++;
}

void updateClientsN(Query9Aux aux, int i, char* key){
    aux->clientsN[i] = strdup(key);
}

void updateClientsP(Query9Aux aux, int i, char* key){
    aux->clientsP[i] = strdup(key);
}

void updateClients(Query9Aux aux, int i, int j){
    aux->clientsN[i] = NULL;
    aux->clientsP[j] = NULL;
}

void updateInfo(Info info, int value){
    (info->unitsSold) += value;
}

void updateAux(Aux aux, int branch, int * value){
    (aux->totalClients[branch])++;
    int i;
    for (i = ZERO; i < MONTHS; i++)
        aux->unitsSold[branch] += value[i];
}

void updateMoney(Money money, double value)
{
    (money->moneySpent) += value;
}

/* -------------- */
/* GET DEFINITION */
/* -------------- */

int getQuery8AuxUnits(Query8Aux aux){
    return aux->totalUnits;
}

double getQuery8AuxBilled(Query8Aux aux){
    return aux->totalBilled;
}

int getQuery8AuxSales(Query8Aux aux){
    return aux->totalSales;
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

int getQuery9TotalN(Query9Aux aux){
    return aux->totalN;
}

int getQuery9TotalP(Query9Aux aux){
    return aux->totalP;
}

char * getQuery9ClientN(Query9Aux aux, int i){
    return aux->clientsN[i];
}

char * getQuery9ClientP(Query9Aux aux, int i){
    return aux->clientsP[i];
}
