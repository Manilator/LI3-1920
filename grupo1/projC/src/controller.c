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
    sgv = startSGV(sgv, sv);
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

void controllerQuerie2(SGV sgv) {
    char letter = askQuerie2Letter();
    querie2View(productsByLetter(sgv,letter));
}

void controllerQuerie3(SGV sgv) {
    char* product = askQuerie3Product();
    int month = askQuerie3Month();
    int choice = askQuerie3Choice();
    querie3View(productValuesByMonth(sgv,product, month, choice), choice);
    g_free(product);
}

void controllerQuerie5(SGV sgv) {
    char** clients = query5(sgv);

    int i;
    puts("Printing codes:");
    for(i = 0; clients[i] != NULL; i++)
        printf("%s\n", clients[i]);

    printf("Clients in common: %d\n", i);
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
            controllerQuerie2(sgv);
            break;
        case '3' :
            controllerQuerie3(sgv);
            break;
        case '4':
            /* QUERIE - 4*/
            /* GLOBAL  = 0, separado 1*/
            productsNotBought(sgv,1);
            break;
        case '5':
            controllerQuerie5(sgv);
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
