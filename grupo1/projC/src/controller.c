#include "controller.h"
#include "view.h"
#include "sgv.h"

#include <stdio.h>
#include <stdlib.h>

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

void controllerQuerie2(SGV sgv)
{
    char letter = askProductLetter();
    char** result = productsByLetter(sgv, letter);
    listView(result, listSize(result));
    /*querie2View();*/
}

void controllerQuerie3(SGV sgv)
{
    char *product = askProduct();
    int month = askMonth();
    int choice = askQuerie3Choice();
    querie3View(productValuesByMonth(sgv, product, month, choice), choice);
    g_free(product);
}

void controllerQuerie4(SGV sgv)
{
    int choice = askQuerie4Choice();
    char ***products = productsNotBought(sgv, choice);
    if (products == NULL) {
        printf("Informações não existentes.");
    } else {
        querie4View(products, choice);
    }
}

void controllerQuerie5(SGV sgv)
{
    char **clients = query5(sgv);

    listView(clients, listSize(clients));
    /*querie5View(clients);*/
}

void controllerQuerie6(SGV sgv) {
    int* list = productsClientsNotUsed(sgv);
    querie6View(list);
}

void controllerQuerie7(SGV sgv) {

    char* client = askClient();

    int **result = clientShoppingLog(sgv,client);

    tableView(result);
    /*querie7View(result);*/

    g_free(client);
}

void controllerQuerie9(SGV sgv) {

    char* product = askProduct();
    int branch = askBranch();
    int* total_N = malloc(sizeof(int));
    int* total_P = malloc(sizeof(int));
    char*** result = query9(sgv, product, branch, total_N, total_P);

    querie9View(result,total_N, total_P);

    g_free(product);
    g_free(total_N);
    g_free(total_P);
}

void controllerQuerie10(SGV sgv) {
    char* client = askClient();
    int month = askMonth();

    /*Info * result = */
    clientMostBoughtByMonth(sgv, client, month);

    /*querie10View(result);*/

    g_free(client);
}

void menu(SGV sgv)
{
    int querie;
    StartValues sv = NULL;
    cleanConsole();
    while (querie != 0)
    {
        printMenu();
        scanf(" %d", &querie);
        switch (querie)
        {
        case 1:
            controllerQuerie1(sv, sgv);
            break;
        case 2:
            controllerQuerie2(sgv);
            break;
        case 3:
            controllerQuerie3(sgv);
            break;
        case 4:
            /* QUERIE - 4*/
            /* GLOBAL  = 0, separado 1*/
            controllerQuerie4(sgv);
            break;
        case 5:
            controllerQuerie5(sgv);
            break;
        case 6:
            controllerQuerie6(sgv);
            break;
        case 7:
            /*clientShoppingLog(sgv,"F2916");*/
            controllerQuerie7(sgv);
            break;
        case 8:
            query8(sgv);
            break;
        case 9:
            controllerQuerie9(sgv);
            break;
        case 10:
            /*clientMostBoughtByMonth(sgv, "F2916", 1);*/
            controllerQuerie10(sgv);
            break;
        case 11:
            nMostBought(sgv, 5);
            break;
        case 12:
            break;
        default:
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
