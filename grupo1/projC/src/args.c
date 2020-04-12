#include "args.h"
#include "sgv.h"
#include "constants.h"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <string.h>

#define LOAD "Load Files"
#define ANSWER "Answer Query"
#define FREE "Free Structs"
#define DB  "Free Database"

clock_t start, end;
double cpu_time_used;

void printElapsedTime(char * action_name){
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("CPU Time used to %s:%f\n", action_name, cpu_time_used );
}

/* Testar com argumentos */

void argsCustomQuery1(StartValues sv, SGV sgv, int n, char *args[]){
    if (n == 0 || n == 3)
    {
        start = clock();
        char *clients_path = g_malloc(sizeof(char) * 1024);
        char *products_path = g_malloc(sizeof(char) * 1024);
        char *sales_path = g_malloc(sizeof(char) * 1024);
        if(n==0){
            strcpy(clients_path, CLIENTS_PATH);
            strcpy(products_path, PRODUCTS_PATH);
            strcpy(sales_path, SALES_PATH);
        }
        else{
            strcpy(clients_path, args[0]);
            strcpy(products_path, args[1]);
            strcpy(sales_path, args[2]);
        }
        setPathsSV(sv, clients_path, products_path, sales_path);
        end = clock();
        printElapsedTime(LOAD);

        start = clock();
        sgv = startSGV(sgv, sv);
        end = clock();
        printElapsedTime(ANSWER);


        start = clock();
        destroySGV(sgv);
        destroyStartValues(sv);
        g_free(clients_path);
        g_free(products_path);
        g_free(sales_path);
        end = clock();
        printElapsedTime(FREE);
    }
    else
    {
        puts("--- Wrong Input ---\n  ./SGV 1 (Path Clientes) (Path Produtos) (Path Vendas)");
    }

}

void argsQuery1(StartValues sv, SGV sgv)
{
    char *clients_path = g_malloc(sizeof(char) * 1024);
    char *products_path = g_malloc(sizeof(char) * 1024);
    char *sales_path = g_malloc(sizeof(char) * 1024);
    strcpy(clients_path, CLIENTS_PATH);
    strcpy(products_path, PRODUCTS_PATH);
    strcpy(sales_path, SALES_PATH);
    setPathsSV(sv, clients_path, products_path, sales_path);
    sgv = startSGV(sgv, sv);

    g_free(clients_path);
    g_free(products_path);
    g_free(sales_path);
}

void argsQuery2(StartValues sv, SGV sgv, int n, char *args[])
{
    /* args[0]: product first letter */
    if (n == 1 && isalpha(args[0][0]) && args[0][1] == '\0')
    {
        start = clock();
        argsQuery1(sv, sgv);
        end = clock();
        printElapsedTime(LOAD);

        /*------------------------------------------------*/
        start = clock();
        char** result = getProductsStartedByLetter(sgv, args[0][0]);
        end = clock();
        printElapsedTime(ANSWER);

        /*------------------------------------------------*/
        start = clock();
        freeStringList(result);
        end = clock();
        printElapsedTime(FREE);

        start = clock();
        destroySGV(sgv);
        destroyStartValues(sv);
        end = clock();
        printElapsedTime(DB);
    }
    else
    {
        puts("--- Wrong Input ---\n  ./SGV 2 [Letra]");
    }
}

int isNumber(char * str){
    int i=0,r=1;
    while(str[i] != '\0')
        if(!isdigit(str[i++]))
            r = 0;
    return r;
}

void argsQuery3(StartValues sv, SGV sgv, int n, char *args[])
{
/*
    args[0]: produto
    args[1]: mes
    args[2]: 0 ou 1*/

    if (n == 3 && isNumber(args[1]) && isdigit(args[2][0]) && args[2][1] == '\0')
    {
        start = clock();
        argsQuery1(sv, sgv);
        end = clock();
        printElapsedTime(LOAD);

        /*------------------------------------------------*/
        start = clock();
        double * result = getProductSalesAndProfit(sgv, args[0], atoi(args[1]), atoi(args[2]));
        end = clock();
        printElapsedTime(ANSWER);

        /*------------------------------------------------*/
        start = clock();
        g_free(result);
        end = clock();
        printElapsedTime(FREE);

        start = clock();
        destroySGV(sgv);
        destroyStartValues(sv);
        end = clock();
        printElapsedTime(DB);
    }
    else
    {
        puts("--- Wrong Input ---\n  ./SGV 3 [Código de Produto] [Mês] [Global/Filial]");
    }
}

void argsQuery4(StartValues sv, SGV sgv, int n, char *args[])
{

    /* args[0]: 0 ou 1 */

    if (n == 1 && isdigit(args[0][0]) && args[0][1] == '\0')
    {
        start = clock();
        argsQuery1(sv, sgv);
        end = clock();
        printElapsedTime(LOAD);

        /*------------------------------------------------*/
        start = clock();
        char *** result = getProductsNeverBought(sgv, atoi(args[0]));
        end = clock();
        printElapsedTime(ANSWER);

        /*------------------------------------------------*/
        start = clock();
        freeStringMatrix(result);
        end = clock();
        printElapsedTime(FREE);

        start = clock();
        destroySGV(sgv);
        destroyStartValues(sv);
        end = clock();
        printElapsedTime(DB);
    }
    else
    {
        puts("--- Wrong Input ---\n  ./SGV 4 [Global/Filial]");
    }
}

void argsQuery5(StartValues sv, SGV sgv, int n)
{

    /*args[0]: nada*/

    if (n == 0)
    {
        start = clock();
        argsQuery1(sv, sgv);
        end = clock();
        printElapsedTime(LOAD);

        /*------------------------------------------------*/
        start = clock();
        char** result = getClientsOfAllBranches(sgv);
        end = clock();
        printElapsedTime(ANSWER);

        /*------------------------------------------------*/
        start = clock();
        g_free(result);
        end = clock();
        printElapsedTime(FREE);

        start = clock();
        destroySGV(sgv);
        destroyStartValues(sv);
        end = clock();
        printElapsedTime(DB);
    }
    else
    {
        puts("--- Wrong Input ---\n  ./SGV 5");
    }
}

void argsQuery6(StartValues sv, SGV sgv, int n)
{

    /*args[0]: nada*/

    if (n == 0)
    {
        start = clock();
        argsQuery1(sv, sgv);
        end = clock();
        printElapsedTime(LOAD);

        /*------------------------------------------------*/
        start = clock();
        int * result = getClientsAndProductsNeverBoughtCount(sgv);
        end = clock();
        printElapsedTime(ANSWER);

        /*------------------------------------------------*/
        start = clock();
        g_free(result);
        end = clock();
        printElapsedTime(FREE);

        start = clock();
        destroySGV(sgv);
        destroyStartValues(sv);
        end = clock();
        printElapsedTime(DB);
    }
    else
    {
        puts("--- Wrong Input ---\n  ./SGV 6");
    }
}

void argsQuery7(StartValues sv, SGV sgv, int n, char *args[])
{

    /*args[0]: cliente*/

    if (n == 1)
    {
        start = clock();
        argsQuery1(sv, sgv);
        end = clock();
        printElapsedTime(LOAD);

        /*------------------------------------------------*/
        start = clock();
        int ** result = getProductsBoughtByClient(sgv, args[0]);
        end = clock();
        printElapsedTime(ANSWER);

        /*------------------------------------------------*/
        start = clock();
        freeIntMatrix(result);
        end = clock();
        printElapsedTime(FREE);

        start = clock();
        destroySGV(sgv);
        destroyStartValues(sv);
        end = clock();
        printElapsedTime(DB);
    }
    else
    {
        puts("--- Wrong Input ---\n  ./SGV 7 [Código de Cliente]");
    }
}

void argsQuery8(StartValues sv, SGV sgv, int n, char *args[])
{
/*
    args[0]: mes
    args[1]: mes*/

    if (n == 2 && isNumber(args[0]) && isNumber(args[1]))
    {
        start = clock();
        argsQuery1(sv, sgv);
        end = clock();
        printElapsedTime(LOAD);

        start = clock();
        Query8Aux result = getSalesAndProfit(sgv, atoi(args[0]), atoi(args[1]));
        end = clock();
        printElapsedTime(ANSWER);

        start = clock();
        freeQuery8Aux(result);
        end = clock();
        printElapsedTime(FREE);

        start = clock();
        destroySGV(sgv);
        destroyStartValues(sv);
        end = clock();
        printElapsedTime(DB);
    }
    else
    {
        puts("--- Wrong Input ---\n  ./SGV 8 [Initial Month] [Final Month]");
    }
}

void argsQuery9(StartValues sv, SGV sgv, int n, char *args[])
{
/*
    args[0]: produto
    args[1]: filial*/

    if (n == 2 && isNumber(args[1]))
    {
        start = clock();
        argsQuery1(sv, sgv);
        end = clock();
        printElapsedTime(LOAD);

        start = clock();
        Query9Aux result = getProductBuyers(sgv, args[0], atoi(args[1]));
        end = clock();
        printElapsedTime(ANSWER);


        start = clock();
        freeQuery9Aux(result);
        end = clock();
        printElapsedTime(FREE);

        start = clock();
        destroySGV(sgv);
        destroyStartValues(sv);
        end = clock();
        printElapsedTime(DB);
    }
    else
    {
        puts("--- Wrong Input ---\n  ./SGV 9 [Código Produto] [Filial]");
    }
}

void argsQuery10(StartValues sv, SGV sgv, int n, char *args[])
{
/*
    args[0]: cliente
    args[1]: mes*/

    if (n == 2 && isNumber(args[1]))
    {
        start = clock();
        argsQuery1(sv, sgv);
        end = clock();
        printElapsedTime(LOAD);

        start = clock();
        Info * result = getClientsFavoriteProducts(sgv, args[0], atoi(args[1]));
        end = clock();
        printElapsedTime(ANSWER);


        start = clock();
        freeInfoList(result);
        end = clock();
        printElapsedTime(FREE);

        start = clock();
        destroySGV(sgv);
        destroyStartValues(sv);
        end = clock();
        printElapsedTime(DB);
    }
    else
    {
        puts("--- Wrong Input ---\n  ./SGV 10 [Código de Cliente] [Mês]");
    }
}

void argsQuery11(StartValues sv, SGV sgv, int n, char *args[])
{

    /*args[0]: numero de produtos*/

    if (n == 1 && isNumber(args[0]))
    {
        start = clock();
        argsQuery1(sv, sgv);
        end = clock();
        printElapsedTime(LOAD);

        start = clock();
        Aux * result = getTopSoldProducts(sgv, atoi(args[0]));
        end = clock();
        printElapsedTime(ANSWER);


        start = clock();
        freeAuxList(result);
        end = clock();
        printElapsedTime(FREE);

        start = clock();
        destroySGV(sgv);
        destroyStartValues(sv);
        end = clock();
        printElapsedTime(DB);
    }
    else
    {
        puts("--- Wrong Input ---\n  ./SGV 11 [Number of Products]");
    }
}

void argsQuery12(StartValues sv, SGV sgv, int n, char *args[])
{

    /*args[0]: cliente code
      args[1]: month*/

    if (n == 2 && isNumber(args[1]))
    {
        start = clock();
        argsQuery1(sv, sgv);
        end = clock();
        printElapsedTime(LOAD);

        start = clock();
        Money * result = getClientTopProfitProducts(sgv, args[0], atoi(args[1]));
        end = clock();
        printElapsedTime(ANSWER);

        start = clock();
        freeMoneyList(result);
        end = clock();
        printElapsedTime(FREE);

        start = clock();
        destroySGV(sgv);
        destroyStartValues(sv);
        end = clock();
        printElapsedTime(DB);
    }
    else
    {
        puts("--- Wrong Input ---\n  ./SGV 12 [Client Code] [Number of Products]");
    }
}

void input(SGV sgv, int n, char *args[], int query)
{
    StartValues sv = initStartValues();
    switch (query)
    {
        case 1:
            argsCustomQuery1(sv, sgv, n, args);
            break;
        case 2:
            argsQuery2(sv, sgv, n, args);
            break;
        case 3:
            argsQuery3(sv, sgv, n, args);
            break;
        case 4:
            argsQuery4(sv, sgv, n, args);
            break;
        case 5:
            argsQuery5(sv, sgv, n);
            break;
        case 6:
            argsQuery6(sv, sgv, n);
            break;
        case 7:
            argsQuery7(sv, sgv, n, args);
            break;
        case 8:
            argsQuery8(sv, sgv, n, args);
            break;
        case 9:
            argsQuery9(sv, sgv, n, args);
            break;
        case 10:
            argsQuery10(sv, sgv, n, args);
            break;
        case 11:
            argsQuery11(sv, sgv, n, args);
            break;
        case 12:
            argsQuery12(sv, sgv, n, args);
            break;
        default:
            break;
    }
}


void startInput(int n, char *args[])
{
    int query = atoi(args[0]);
    if (query >= 1 && query <= 12)
    {
        SGV sgv = initSGV();
        input(sgv, n-1, args+1, query);
    }
    else
    {
        puts("Query must be a number.");
        printf("%d\n", query);
    }
}
