#include "info.h"
#include "constants.h"
#include <string.h>

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
