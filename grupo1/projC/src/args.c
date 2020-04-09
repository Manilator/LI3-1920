#include "args.h"
#include "sgv.h"
#include "constants.h"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

#define LOAD "Load Files"
#define ANSWER "Answer Query"
#define FREE "Free Structs"

clock_t start, end;
double cpu_time_used;

void printElapsedTime(char * action_name){
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("CPU Time used to %s:%f\n", action_name, cpu_time_used );
}

/* Testar com argumentos */

void argsQuery1(StartValues sv, SGV sgv)
{
    sv = initStartValues(CLIENTS_PATH, PRODUCTS_PATH, SALES_PATH);
    sgv = startSGV(sgv, sv);
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
        char** result = productsByLetter(sgv, args[0][0]);
        end = clock();
        printElapsedTime(ANSWER);

        /*------------------------------------------------*/
        start = clock();
        freeStringList(result);
        end = clock();
        printElapsedTime(FREE);
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
        double * result = productValuesByMonth(sgv, args[0], atoi(args[1]), atoi(args[2]));
        end = clock();
        printElapsedTime(ANSWER);

        /*------------------------------------------------*/
        start = clock();
        g_free(result);
        end = clock();
        printElapsedTime(FREE);
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
        char *** result = productsNotBought(sgv, atoi(args[0]));
        end = clock();
        printElapsedTime(ANSWER);

        /*------------------------------------------------*/
        start = clock();
        freeStringMatrix(result);
        end = clock();
        printElapsedTime(FREE);
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
        char** result = query5(sgv);
        end = clock();
        printElapsedTime(ANSWER);

        /*------------------------------------------------*/
        start = clock();
        freeStringList(result);
        end = clock();
        printElapsedTime(FREE);
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
        int * result = productsClientsNotUsed(sgv);
        end = clock();
        printElapsedTime(ANSWER);

        /*------------------------------------------------*/
        start = clock();
        g_free(result);
        end = clock();
        printElapsedTime(FREE);
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
        int ** result = clientShoppingLog(sgv, args[0]);
        end = clock();
        printElapsedTime(ANSWER);

        /*------------------------------------------------*/
        start = clock();
        freeIntMatrix(result);
        end = clock();
        printElapsedTime(FREE);
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
        Querie8Aux result = query8(sgv, atoi(args[0]), atoi(args[1]));
        end = clock();
        printElapsedTime(ANSWER);

        start = clock();
        freeQuerie8Aux(result);
        end = clock();
        printElapsedTime(FREE);
    }
    else
    {
        puts("--- Wrong Input ---\n  ./SGV 8 [Initial Month] [Final Month]");
    }
}
/*
void argsQuery9(StartValues sv, SGV sgv, int n, char *args[])
{

    args[0]: produto
    args[1]: filial

    if (n == 2 && isNumber(args[1]))
    {
        start = clock();
        argsQuery1(sv, sgv);
        end = clock();
        printElapsedTime(LOAD);

        start = clock();
        int ** result = clientShoppingLog(sgv, args[0]);
        end = clock();
        printElapsedTime(ANSWER);


        start = clock();
        freeIntMatrix(result);
        end = clock();
        printElapsedTime(FREE);
    }
    else
    {
        puts("--- Wrong Input ---\n  ./SGV 6");
    }
}*/

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
        Info * result = clientMostBoughtByMonth(sgv, args[0], atoi(args[1]));
        end = clock();
        printElapsedTime(ANSWER);


        start = clock();
        freeInfoList(result);
        end = clock();
        printElapsedTime(FREE);
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
        Aux * result = nMostBought(sgv, atoi(args[0]));
        end = clock();
        printElapsedTime(ANSWER);


        start = clock();
        freeAuxList(result);
        end = clock();
        printElapsedTime(FREE);
    }
    else
    {
        puts("--- Wrong Input ---\n  ./SGV 11 [Numero de Produtos]");
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
        Money * result = query12(sgv, args[0], atoi(args[1]));
        end = clock();
        printElapsedTime(ANSWER);


        start = clock();
        freeMoneyList(result);
        end = clock();
        printElapsedTime(FREE);
    }
    else
    {
        puts("--- Wrong Input ---\n  ./SGV 12 [Client Code] [Month]");
    }
}

void input(SGV sgv, int n, char *args[], int query)
{
    StartValues sv = NULL;
    switch (query)
    {
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
            /*
        case 9:
            argsQuery9(sv, sgv, n, args);
            break;*/
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
    if (query == 1)
    {
        StartValues sv = NULL;
        SGV sgv = initSGV();
        argsQuery1(sv, sgv);
    }
    else if (query >= 2 && query <= 12)
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
