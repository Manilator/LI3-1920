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
    char **result = productsByLetter(sgv, letter);
    listView(result, listSize(result));
    /*querie2View();*/
}

void controllerQuerie3(SGV sgv)
{
    char *product = askProduct();
    int month = askMonth();
    int choice = askQuerie3Choice();
    double *result = productValuesByMonth(sgv, product, month, choice);
    if (result == NULL)
    {
        cleanConsole();
        boldRed();
        printf("Produto inválido.\n");
        resetColor();
    }
    else
    {
        querie3View(result, choice, product);
    }
    g_free(product);
}

void controllerQuerie4(SGV sgv)
{
    int choice = askQuerie4Choice();
    char ***products = productsNotBought(sgv, choice);
    if (products == NULL)
    {
        printf("Informações não existentes.");
    }
    else
    {
        if (choice == 0)
        {
            querie4View(products, choice, 0, listSize(products[0]));
        }
        else
        {
            int branch = askBranch();
            while (branch > 3 || branch <= 0)
            {
                boldRed();
                printf("Filial %d não existe.\n", branch);
                resetColor();
                branch = askBranch();
            }
            querie4View(products, choice, branch-1, listSize(products[branch-1]));
        }
    }
}

void controllerQuerie5(SGV sgv)
{
    char **clients = query5(sgv);

    listView(clients, listSize(clients));
    /*querie5View(clients);*/
}

void controllerQuerie6(SGV sgv)
{
    int *list = productsClientsNotUsed(sgv);
    querie6View(list);
}

void controllerQuerie7(SGV sgv)
{

    char *client = askClient();

    int **result = clientShoppingLog(sgv, client);

    tableView(result, client);
    /*querie7View(result);*/

    g_free(client);
}

void controllerQuerie8(SGV sgv)
{
    int *month = g_malloc(sizeof(int) * 2);
    month = askMonthInterval();

    Querie8Aux result = query8(sgv, month[0], month[1]);

    if (result != NULL)
    {
        querie8View(result, month[0], month[1]);
    }
    else
    {
        cleanConsole();
        boldRed();
        printf("Intervalo de meses errado.\n");
        resetColor();
    }

}

void controllerQuerie9(SGV sgv)
{

    char *product = askProduct();
    int branch = askBranch();
    while (branch > 3 || branch <= 0)
    {
        boldRed();
        printf("Filial %d não existe.\n", branch);
        resetColor();
        branch = askBranch();
    }

    Querie9Aux result = query9(sgv, product, branch);

    querie9View(result);

    g_free(product);
}

void controllerQuerie10(SGV sgv)
{
    char *client = askClient();
    int month = askMonth();

    Info * result = clientMostBoughtByMonth(sgv, client, month);

    if (result == NULL) {
        cleanConsole();
        boldRed();
        printf("Cliente inválido.\n");
        resetColor();
    } else {
        querie10View(result, client);
    }
    g_free(client);
}

void controllerQuerie11(SGV sgv) {
    int n = askQuerie11N();
    Aux * result = nMostBought(sgv, n);

    querie11View(result, listSize((char**)result));
}

void controllerQuerie12(SGV sgv) {
    char* client = askClient();
    int n = askQuerie11N();

    Money *result = query12(sgv, client, n);

    if (result == NULL) {
        cleanConsole();
        boldRed();
        printf("Cliente inválido.\n");
        resetColor();
    } else {
        querie12View(result, listSize((char**)result), client);
    }
}

void menu(SGV sgv)
{
    int querie;
    int initial = 0;
    StartValues sv = NULL;
    cleanConsole();
    while (querie != 0)
    {
        printMenu();
        scanf(" %d", &querie);
        while (querie != 1 && initial != 1) {
            boldRed();
            printf("Faça a querie 1 primeiro para carregamento dos dados.\n");
            boldCyan();
            scanf(" %d", &querie);
        }
        initial = 1;
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
            controllerQuerie4(sgv);
            break;
        case 5:
            controllerQuerie5(sgv);
            break;
        case 6:
            controllerQuerie6(sgv);
            break;
        case 7:
            controllerQuerie7(sgv);
            break;
        case 8:
            controllerQuerie8(sgv);
            break;
        case 9:
            controllerQuerie9(sgv);
            break;
        case 10:
            controllerQuerie10(sgv);
            break;
        case 11:
            controllerQuerie11(sgv);
            break;
        case 12:
            controllerQuerie12(sgv);
            break;
        default:
            querie = 0;
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
