#include "controller.h"
#include "view.h"
#include "sgv.h"

#include <stdio.h>


void controllerQuerie1(StartValues sv, SGV sgv)
{   
    char *clients_path = g_malloc(sizeof(char) * 1024);
    char *products_path = g_malloc(sizeof(char) * 1024);
    char *sales_path = g_malloc(sizeof(char) * 1024);
    querie1View(clients_path, products_path, sales_path);
    sv = initStartValues(clients_path, products_path, sales_path);
    sgv = startSGV(sv);
    cleanConsole();
    viewPrintStartValues(clients_path,
                         products_path,
                         sales_path,
                         getValidClients(sv),
                         getValidProducts(sv),
                         getValidSales(sv),
                         getReadClients(sv),
                         getReadProducts(sv),
                         getReadSales(sv));
    g_free(clients_path);
    g_free(products_path);
    g_free(sales_path);
}


void menu(SGV sgv)
{
    char querie;
    StartValues sv;
    cleanConsole();
    while (querie != '0')
    {
        printMenu();
        scanf(" %c", &querie);
        switch (querie)
        {
        case '1':
            controllerQuerie1(sv, sgv);
            break;
        case '2':
            /*productsByLetter(sgv,'A');*/
            break;
        case '3' :
            /* SGV / CODIGO PRODUTO / MES / É GLOBAL OU NAO? */
            /*productValuesByMonth(sgv,"AF1184", 12, 1);*/
            break;
        }
    }
    /* Destroy memory */
}

void startController()
{
    /*controller->view = initView();*/
    SGV sgv = initSGV();
    menu(sgv);
}
