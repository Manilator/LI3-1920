#include "args.h"
#include "view.h"
#include "sgv.h"
#include "constants.h"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/* Testar com argumentos */

void argsQuery1(StartValues sv, SGV sgv)
{
    sv = initStartValues(CLIENTS_PATH, PRODUCTS_PATH, SALES_PATH);
    sgv = startSGV(sgv, sv);
    viewPrintStartValues(CLIENTS_PATH,
                         PRODUCTS_PATH,
                         SALES_PATH,
                         getValidClients(sv),
                         getValidProducts(sv),
                         getValidSales(sv),
                         getReadClients(sv),
                         getReadProducts(sv),
                         getReadSales(sv));
}

void argsQuery2(StartValues sv, SGV sgv, int n, char *args[])
{
    /* args[0]: product first letter */
    if (n == 1 && isalpha(args[0][0]) && args[0][1] == '\0')
    {
        argsQuery1(sv, sgv);
        char** result = productsByLetter(sgv, args[0][0]);
        listView(result, listSize(result));
    }
    else
    {
        puts("--- Wrong Input ---\n  ./SGV 2 [Char]");
    }
}
/*
void argsQuery3(StartValues sv, SGV sgv, int n, char *args[])
{
    /*
    args[0]: produto
    args[1]: mes
    args[2]: 0 ou 1
    
    if ()
    {}
    else
    {
        puts("");
    }
}
*/
/*
void argsQuery4(StartValues sv, SGV sgv, int n, char *args[])
{
    /*
    args[0]: 0 ou 1
    
    if ()
    {}
    else
    {
        puts("");
    }
}

void argsQuery5(StartValues sv, SGV sgv, int n, char *args[])
{
    /*
    args[0]: nada

    if ()
    {}
    else
    {
        puts("");
    }
}

void argsQuery6(StartValues sv, SGV sgv, int n, char *args[])
{
    /*
    args[0]: nada
    
    if ()
    {}
    else
    {
        puts("");
    }
}

void argsQuery7(StartValues sv, SGV sgv, int n, char *args[])
{
    /*
    args[0]: cliente
    
    if ()
    {}
    else
    {
        puts("");
    }
}

void argsQuery8(StartValues sv, SGV sgv, int n, char *args[])
{
    /*
    args[0]: mes
    args[1]: mes
    
    if ()
    {}
    else
    {
        puts("");
    }
}

void argsQuery9(StartValues sv, SGV sgv, int n, char *args[])
{
    /*
    args[0]: produto
    args[1]: filial
    
    if ()
    {}
    else
    {
        puts("");
    }
}

void argsQuery10(StartValues sv, SGV sgv, int n, char *args[])
{
    /*
    args[0]: cliente
    args[1]: mes
    
    if ()
    {}
    else
    {
        puts("");
    }
}

void argsQuery11(StartValues sv, SGV sgv, int n, char *args[])
{
    /*
    args[0]: ?
    
    if ()
    {}
    else
    {
        puts("");
    }
}

void argsQuery12(StartValues sv, SGV sgv, int n, char *args[])
{
    /*
    args[0]: ?
    
    if ()
    {}
    else
    {
        puts("");
    }
}
*/
void input(SGV sgv, int n, char *args[], int query)
{
    StartValues sv = NULL;
    switch (query)
    {
        case 2:
            argsQuery2(sv, sgv, n, args);
            break;
        /*
        case 3:
            argsQuery3(sv, sgv, n, args);
            break;
        case 4:
            argsQuery4(sv, sgv, n, args);
            break;
        case 5:
            argsQuery5(sv, sgv, n, args);
            break;
        case 6:
            argsQuery6(sv, sgv, n, args);
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
            break;*/
        default:
            break;
    }
    /* Destroy memory */
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

