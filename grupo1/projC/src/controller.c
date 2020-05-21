#include "controller.h"
#include "constants.h"
#include "view.h"
#include "sgv.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void askClientsPath(char *clients_path)
{
    resetColor();
    printMessage("Clients's file path: ");
    scanf("%s", clients_path);
    boldCyan();
}

void askProductsPath(char *products_path)
{
    resetColor();
    printMessage("Products's file path: ");
    scanf("%s", products_path);
    boldCyan();
}

void askSalesPath(char *sales_path)
{
    resetColor();
    printMessage("Sales's file path: ");
    scanf("%s", sales_path);
    boldCyan();
}

char askProductLetter()
{
    resetColor();
    char letter = 0;
    while ((letter < 'A' || letter > 'Z') && (letter < 'a' || letter > 'z'))
    {
        printMessage("Qual a letra?\n");
        boldCyan();
        scanf(" %c", &letter);
        resetColor();
    }
    return toupper(letter);
}

char askPromotion()
{
    char type = 'A';
    while (type != 'N' && type != 'P')
    {
        resetColor();
        printMessage("Qual tipo de produtos vendidos pretende ver? (N ou P)\n");
        boldCyan();
        scanf(" %c", &type);
        toupper(type);
        resetColor();
    }
    return type;
}

char *askProduct()
{
    char *product = malloc(sizeof(char) * PRODUCT_CODE_SIZE);
    resetColor();
    printMessage("Qual produto? \n");
    boldCyan();
    scanf(" %s", product);
    resetColor();
    return product;
}

int askMonth()
{
    char *choice = malloc(sizeof(char) * 32);
    int month = -1;
    while (month <= 0 || month > 12)
    {
        resetColor();
        printMessage("Qual mês?: \n");
        boldCyan();
        scanf(" %s", choice);
        month = atoi(choice);
        resetColor();
    }
    g_free(choice);
    return month;
}

char *askClient()
{
    char *client = malloc(sizeof(char) * CLIENT_CODE_SIZE);
    resetColor();
    printMessage("Qual cliente?\n");
    boldCyan();
    scanf(" %s", client);
    resetColor();
    return client;
}

int *askMonthInterval()
{
    char *choice = malloc(sizeof(char) * 32);
    int *interval = malloc(sizeof(int) * 2);
    resetColor();
    printMessage("Primeiro mês do intervalo?\n");
    boldCyan();
    scanf(" %s", choice);
    interval[0] = atoi(choice);
    resetColor();
    printMessage("Segundo mês do intervalo?\n");
    boldCyan();
    scanf(" %s", choice);
    interval[1] = atoi(choice);
    resetColor();
    g_free(choice);
    return interval;
}

int askBranch()
{
    char *choice = malloc(sizeof(char) * 32);
    int branch = -1;
    while (branch < ONE || branch > N_BRANCHES)
    {
        printMessage("Qual filial?\n");
        boldCyan();
        scanf(" %s", choice);
        branch = atoi(choice);
        resetColor();
    }
    g_free(choice);
    return branch;
}

void askQuery1Paths(char *clients_path, char *products_path, char *sales_path)
{
    resetColor();
    char choice = '0';
    printMessage("1 - Choose files path\nOther value - Default paths\n");
    boldCyan();
    scanf(" %c", &choice);
    switch (choice)
    {
    case '1':
        askClientsPath(clients_path);
        askProductsPath(products_path);
        askSalesPath(sales_path);
        break;

    default:
        strcpy(clients_path, CLIENTS_PATH);
        strcpy(products_path, PRODUCTS_PATH);
        strcpy(sales_path, SALES_PATH);
        break;
    }
    resetColor();
}

int askQuery3Choice()
{
    char *choice = malloc(sizeof(char) * 32);
    int escolha = -1;
    while (escolha != 0 && escolha != 1)
    {
        printMessage("0 - Filial a filial\n1 - Global: \n");
        boldCyan();
        scanf(" %s", choice);
        escolha = atoi(choice);
        resetColor();
    }
    g_free(choice);
    return escolha;
}

int askQuery4Choice()
{
    char *choice = malloc(sizeof(char) * 32);
    int escolha = -1;
    while (escolha != 0 && escolha != 1)
    {
        resetColor();
        printMessage("0 - Global\n1 - Filial a Filial: \n");
        boldCyan();
        scanf(" %s", choice);
        escolha = atoi(choice);
        resetColor();
    }
    g_free(choice);
    return escolha;
}

int askQuery11N()
{
    int n = 0;
    char *choice = malloc(sizeof(char) * 32);
    while (n <= 0)
    {
        resetColor();
        printMessage("Quantos produtos pretende ver?\n");
        boldCyan();
        scanf(" %s", choice);
        n = atoi(choice);
        resetColor();
    }
    g_free(choice);
    return n;
}

void controllerQuery1(StartValues sv, SGV sgv)
{
    char *clients_path = g_malloc(sizeof(char) * 1024);
    char *products_path = g_malloc(sizeof(char) * 1024);
    char *sales_path = g_malloc(sizeof(char) * 1024);
    askQuery1Paths(clients_path, products_path, sales_path);

    setPathsSV(sv, clients_path, products_path, sales_path);
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

void controllerQuery2(SGV sgv)
{
    char *choice = malloc(sizeof(char) * 32);
    char letter = askProductLetter();
    char **result = getProductsStartedByLetter(sgv, letter);
    int page = 0;
    int max, size;

    for (; page >= 0 && choice[0] != '0';)
    {
        size = listSize(result);
        listView(result, size, page);

        max = size / ELEMENTS_PER_PAGE;
        scanf(" %s", choice);

        if (choice[0] == 'p' && page > 0)
        {
            page--;
        }
        else if (choice[0] == 'n' && page < max)
        {
            page++;
        }
        else if (choice[0] == 'c')
        {
            printMessage("Número da página:\n");
            scanf(" %s", choice);
            while (atoi(choice) > max || page < 0 || atoi(choice) < 0)
            {
                printMessage("Página não existe. Insira novo número:\n");
                scanf(" %s", choice);
            }
            page = atoi(choice);
            choice[0] = 0;
        }
    }

    cleanConsole();
    freeStringList(result);
    free(choice);
}

void controllerQuery3(SGV sgv)
{
    char *product = askProduct();
    int month = askMonth();
    int choice = askQuery3Choice();
    double *result = getProductSalesAndProfit(sgv, product, month, choice);
    if (result == NULL)
    {
        cleanConsole();
        boldRed();
        printMessage("Produto inválido.\n");
        resetColor();
    }
    else
    {
        querie3View(result, choice, product);
    }
    free(product);
    free(result);
}

void controllerQuery4(SGV sgv)
{
    char *choice = malloc(sizeof(char) * 32);
    int escolha = askQuery4Choice();
    char ***products = getProductsNeverBought(sgv, escolha);
    int sizes[N_BRANCHES];
    int max;
    int page = 0;
    int branch = 0;
    int global;
    if (products == NULL)
    {
        printMessage("Informações não existentes.");
    }
    else
    {
        int i = 0;
        if (escolha == 0)
        {
            global = 1;
            sizes[0] = listSize(products[0]);
        }
        else
        {
            global = 0;
            for (; i < N_BRANCHES; i++)
            {
                sizes[i] = listSize(products[i]);
            }
        }
        max = sizes[0] / ELEMENTS_PER_PAGE;
        for (; page >= 0 && choice[0] != '0';)
        {
            querie4View(products, global, branch, sizes, page);
            scanf(" %s", choice);

            if (choice[0] == 'p' && page > 0)
            {
                page--;
            }
            else if (choice[0] == 'n' && page < max)
            {
                page++;
            }
            else if (choice[0] == 'c')
            {
                printMessage("Número da página:\n");
                scanf(" %s", choice);
                while (atoi(choice) > max || page < 0 || atoi(choice) < 0)
                {
                    printMessage("Página não existe. Insira novo número:\n");
                    scanf(" %s", choice);
                }
                page = atoi(choice);
                choice[0] = 0;
            }
            else if (choice[0] == 't')
            {
                if (branch == N_BRANCHES - 1)
                {
                    branch = 0;
                    max = sizes[branch] / ELEMENTS_PER_PAGE;
                    page = 0;
                }
                else
                {
                    branch++;
                    max = sizes[branch] / ELEMENTS_PER_PAGE;
                    page = 0;
                }
            }
        }
    }
    cleanConsole();
    free(choice);
    freeStringMatrix(products);
}

void controllerQuery5(SGV sgv)
{
    char *choice = malloc(sizeof(char) * 32);
    char **clients = getClientsOfAllBranches(sgv);
    int page = 0;
    int max, size;

    for (; page >= 0 && choice[0] != '0';)
    {
        size = listSize(clients);
        listView(clients, size, page);

        max = size / ELEMENTS_PER_PAGE;
        scanf(" %s", choice);

        if (choice[0] == 'p' && page > 0)
        {
            page--;
        }
        else if (choice[0] == 'n' && page < max)
        {
            page++;
        }
        else if (choice[0] == 'c')
        {
            printMessage("Número da página:\n");
            scanf(" %s", choice);
            while (atoi(choice) > max || page < 0 || atoi(choice) < 0)
            {
                printMessage("Página não existe. Insira novo número:\n");
                scanf(" %s", choice);
            }
            page = atoi(choice);
            choice[0] = 0;
        }
    }

    cleanConsole();
    free(choice);
    free(clients);
}

void controllerQuery6(SGV sgv)
{
    int *list = getClientsAndProductsNeverBoughtCount(sgv);
    querie6View(list);
    free(list);
}

void controllerQuery7(SGV sgv)
{

    char *client = askClient();

    int **result = getProductsBoughtByClient(sgv, client);

    tableView(result, client);

    freeIntMatrix(result);
    free(client);
}

void controllerQuery8(SGV sgv)
{
    int *month = g_malloc(sizeof(int) * 2);
    month = askMonthInterval();

    Query8Aux result = getSalesAndProfit(sgv, month[0], month[1]);

    if (result != NULL)
    {
        querie8View(result, month[0], month[1]);
    }
    else
    {
        cleanConsole();
        boldRed();
        printMessage("Intervalo de meses errado.\n");
        resetColor();
    }
    free(month);
    freeQuery8Aux(result);
}

void controllerQuery9(SGV sgv)
{
    char *choice = malloc(sizeof(char) * 32);
    char *product = askProduct();
    int branch = askBranch();
    char type = askPromotion();
    Query9Aux result = getProductBuyers(sgv, product, branch);
    int max;
    int page = 0;
    if (result == NULL)
    {
        cleanConsole();
        boldRed();
        printMessage("Informações não existentes.\n");
        resetColor();
    }
    else
    {
        int size;
        for (; page >= 0 && choice[0] != '0';)
        {
            int totalN = getQuery9TotalN(result);
            int totalP = getQuery9TotalP(result);
            if (type == 'N')
            {
                size = totalN;
            }
            else
            {
                size = totalP;
            }
            max = size / ELEMENTS_PER_PAGE;
            querie9View(result, type, page);
            scanf(" %s", choice);

            if (choice[0] == 'p' && page > 0)
            {
                page--;
            }
            else if (choice[0] == 'n' && page < max)
            {
                page++;
            }
            else if (choice[0] == 'c')
            {
                printMessage("Número da página:\n");
                scanf(" %s", choice);
                while (atoi(choice) > max || page < 0 || atoi(choice) < 0)
                {
                    printMessage("Página não existe. Insira novo número:\n");
                    scanf(" %s", choice);
                }
                page = atoi(choice);
                choice[0] = 0;
            }
            else if (choice[0] == 't')
            {
                if (type == 'N')
                {
                    type = 'P';
                }
                else
                {
                    type = 'N';
                }
            }
        }
        cleanConsole();
    }
    free(choice);
    free(product);
    freeQuery9Aux(result);
}

void controllerQuery10(SGV sgv)
{
    char *client = askClient();
    int month = askMonth();
    Info *result = getClientsFavoriteProducts(sgv, client, month);
    char *choice = malloc(sizeof(char) * 32);
    int max;
    int page = 0;
    int size;

    if (result == NULL)
    {
        cleanConsole();
        boldRed();
        printMessage("Cliente inválido.\n");
        resetColor();
    }
    else
    {
        for (; page >= 0 && choice[0] != '0';)
        {
            size = listSize((char **)result);
            querie10View(result, size, client, page);

            max = size / ELEMENTS_PER_PAGE;
            scanf(" %s", choice);

            if (choice[0] == 'p' && page > 0)
            {
                page--;
            }
            else if (choice[0] == 'n' && page < max)
            {
                page++;
            }
            else if (choice[0] == 'c')
            {
                printMessage("Número da página:\n");
                scanf(" %s", choice);
                while (atoi(choice) > max || page < 0 || atoi(choice) < 0)
                {
                    printMessage("Página não existe. Insira novo número:\n");
                    scanf(" %s", choice);
                }
                page = atoi(choice);
                choice[0] = 0;
            }
        }
        cleanConsole();
    }
    free(client);
    free(choice);
    freeInfoList(result);
}

void controllerQuery11(SGV sgv)
{

    int n = askQuery11N();
    Aux *result = getTopSoldProducts(sgv, n);
    char *choice = malloc(sizeof(char) * 32);
    int max;
    int page = 0;
    int size;
    size = listSize((char **)result);

    for (; page >= 0 && choice[0] != '0';)
    {
        querie11View(result, size, page);

        if (size % 2 != 0) {
            max = size / 2;
        } else {
             max = n / 2 - 1;
        }
        scanf(" %s", choice);

        if (choice[0] == 'p' && page > 0)
        {
            page--;
        }
        else if (choice[0] == 'n' && page < max)
        {
            page++;
        }
        else if (choice[0] == 'c')
        {
            printMessage("Número da página:\n");
            scanf(" %s", choice);
            while (atoi(choice) > max || page < 0 || atoi(choice) < 0)
            {
                printMessage("Página não existe. Insira novo número:\n");
                scanf(" %s", choice);
            }
            page = atoi(choice);
            choice[0] = 0;
        }
    }
    free(choice);
    freeAuxList(result);
    cleanConsole();
}

void controllerQuery12(SGV sgv)
{
    char *client = askClient();
    int n = askQuery11N();
    char *choice = malloc(sizeof(char) * 32);
    Money *result = getClientTopProfitProducts(sgv, client, n);
    int max;
    int page = 0;
    int size;

    if (result == NULL)
    {
        cleanConsole();
        boldRed();
        printMessage("Cliente inválido.\n");
        resetColor();
    }
    else
    {

        size = listSize((char **)result);

        for (; page >= 0 && choice[0] != '0';)
        {
            querie12View(result, size, client, page);

            max = size / ELEMENTS_PER_PAGE;
            scanf(" %s", choice);

            if (choice[0] == 'p' && page > 0)
            {
                page--;
            }
            else if (choice[0] == 'n' && page < max)
            {
                page++;
            }
            else if (choice[0] == 'c')
            {
                printMessage("Número da página:\n");
                scanf(" %s", choice);
                while (atoi(choice) > max || page < 0 || atoi(choice) < 0)
                {
                    printMessage("Página não existe. Insira novo número:\n");
                    scanf(" %s", choice);
                }
                page = atoi(choice);
            }
        }
        cleanConsole();
        resetColor();
    }
    free(choice);
    free(client);
    freeMoneyList(result);
}

void controllerQuery13(StartValues sv) {
    cleanConsole();
    viewPrintStartValues(getClientsPath(sv),
                         getProductsPath(sv),
                         getSalesPath(sv),
                         getValidClients(sv),
                         getValidProducts(sv),
                         getValidSales(sv),
                         getReadClients(sv),
                         getReadProducts(sv),
                         getReadSales(sv));
}

void menu(SGV sgv)
{
    char *choice = malloc(sizeof(char) * 32);
    int querie = -1;
    int initial = 0;
    StartValues sv = initStartValues();
    cleanConsole();
    while (querie != 0)
    {
        printMenu();
        scanf(" %s", choice);
        querie = atoi(choice);
        while (querie != 1 && initial != 1 && querie != 0 && querie <= 13)
        {
            boldRed();
            printMessage("Faça a querie 1 primeiro para carregamento dos dados.\n");
            boldCyan();
            scanf(" %s", choice);
            querie = atoi(choice);
        }
        switch (querie)
        {
        case 1:
            if(initial == 1) {
                boldRed();
                printMessage("A libertar dados antigos...\n");
                resetColor();
                destroyStartValues(sv);
                destroySGV(sgv);
                sgv = initSGV();
                sv = initStartValues();

            }
            controllerQuery1(sv, sgv);
            initial = 1;
            break;
        case 2:
            controllerQuery2(sgv);
            break;
        case 3:
            controllerQuery3(sgv);
            break;
        case 4:
            controllerQuery4(sgv);
            break;
        case 5:
            controllerQuery5(sgv);
            break;
        case 6:
            controllerQuery6(sgv);
            break;
        case 7:
            controllerQuery7(sgv);
            break;
        case 8:
            controllerQuery8(sgv);
            break;
        case 9:
            controllerQuery9(sgv);
            break;
        case 10:
            controllerQuery10(sgv);
            break;
        case 11:
            controllerQuery11(sgv);
            break;
        case 12:
            controllerQuery12(sgv);
            break;
        case 13:
            controllerQuery13(sv);
            break;
        default:
            querie = 0;
            break;
        }
    }
    g_free(choice);
    if (sgv != NULL){
        boldRed();
        printMessage("A libertar dados antigos...\n");
        resetColor();
        destroySGV(sgv);
    }

    if (sv != NULL)
        destroyStartValues(sv);
}

void startController()
{
    /*controller->view = initView();*/
    SGV sgv = initSGV();
    menu(sgv);
}
