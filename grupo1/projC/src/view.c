#include "view.h"
#include "constants.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void cleanConsole()
{
    printf("\e[1;1H\e[2J");
}

void resetColor()
{
    printf("\033[0m");
}

void red()
{
    printf("\033[0;31m");
}

void boldRed()
{
    printf("\033[1;31m");
}

void green()
{
    printf("\033[0;32m");
}

void boldGreen()
{
    printf("\033[1;32m");
}

void yellow()
{
    printf("\033[0;33m");
}

void boldYellow()
{
    printf("\033[1;33m");
}

void blue()
{
    printf("\033[0;34m");
}

void boldBlue()
{
    printf("\033[1;34m");
}

void magenta()
{
    printf("\033[0;35m");
}

void boldMagenta()
{
    printf("\033[1;35m");
}

void cyan()
{
    printf("\033[1;36m");
}

void boldCyan()
{
    printf("\033[1;36m");
}

void printMenu()
{
    printf("! --------------- !\n");
    printf("1  - Querie 1\n");
    printf("2  - Querie 2\n");
    printf("3  - Querie 3\n");
    printf("4  - Querie 4\n");
    printf("5  - Querie 5\n");
    printf("6  - Querie 6\n");
    printf("7  - Querie 7\n");
    printf("8  - Querie 8\n");
    printf("9  - Querie 9\n");
    printf("10 - Querie 10\n");
    printf("11 - Querie 11\n");
    printf("12 - Querie 12\n");
    printf("0  - Exit\n");
    printf("! --------------- !\n");
    boldCyan();
}

void printSeparator()
{
    printf("===========================\n");
}

void viewPrintStartValues(char *clients_path,
                          char *products_path,
                          char *sales_path,
                          int valid_clients,
                          int valid_products,
                          int valid_sales,
                          int clients_read,
                          int products_read,
                          int sales_read)
{
    printSeparator();
    boldGreen();
    printf("Path Clients:%s\n", clients_path);
    printf("Path Products:%s\n", products_path);
    printf("Path Sales:%s\n", sales_path);
    printf("Clientes válidos: %d\n", valid_clients);
    printf("Produtos válidos: %d\n", valid_products);
    printf("Vendas válidas: %d\n", valid_sales);
    printf("Clientes lidos: %d\n", clients_read);
    printf("Produtos lidos: %d\n", products_read);
    printf("Vendas lidas: %d\n", sales_read);
    resetColor();
    printSeparator();
}

void askClientsPath(char *clients_path)
{
    printf("Clients's file path: ");
    scanf("%s", clients_path);
}

void askProductsPath(char *products_path)
{
    printf("Products's file path: ");
    scanf("%s", products_path);
}

void askSalesPath(char *sales_path)
{
    printf("Sales's file path: ");
    scanf("%s", sales_path);
}

void querie1View(char *clients_path, char *products_path, char *sales_path)
{
    resetColor();
    char choice = '0';
    printf("1 - Choose files path\nOther value - Default paths\n");
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

char askQuerie2Letter()
{
    char letter;
    printf("1 - Choose product first letter\n");
    scanf(" %c", &letter);
    toupper(letter);
    return letter;
}

void querie2View(char **list)
{
    int i;
    for (i = 0; list[i] != NULL; i++)
    {
        printf("ELEM:%s\n", (char *)list[i]);
    }
    printf("Number of products: %d\n", i);
}

char *askQuerie3Product()
{
    char *product = malloc(sizeof(char) * PRODUCT_CODE_SIZE);
    printf("Qual produto? \n");
    scanf(" %s", product);
    return product;
}

int askQuerie3Month()
{
    int month = -1;
    printf("Qual mê?: \n");
    scanf(" %d", &month);
    return month;
}

int askQuerie3Choice()
{
    int choice = -1;
    printf("0 - Filial a filial\n1 - Global: \n");
    scanf(" %d", &choice);
    return choice;
}

void querie3View(float *products, int choice)
{
    int i, j, branch;
    int length;
    char *_text[4] = {"Total Vendas N: ", "Total Vendas P: ", "Total Faturado N: ", "Total Faturado P: "};
    if (choice == 1)
    {
        length = 4;
    }
    else
    {
        length = 12;
    }
    for (i = 0, j = 0, branch = 1; i < length; i++, j++)
    {
        if (j == 0 && length == 12)
        {
            printf("------ Filial %d ------\n", branch);
            branch++;
        }
        printf("%s%f\n", _text[j], products[i]);
        if (j == 3)
        {
            j = -1;
        }
    }
    printf("Number of products: %d\n", i);
}

int askQuerie4Choice()
{
    int choice = -1;
    printf("0 - Global\n1 - Filial a Filial: \n");
    scanf(" %d", &choice);
    return choice;
}

char* askQuerie7Client()
{
    char *client = malloc(sizeof(char) * CLIENT_CODE_SIZE);
    printf("Qual cliente? \n");
    scanf(" %s", client);
    return client;
}

int* askQuerie8Interval()
{
    int* interval = malloc(sizeof(int) * 2);
    printf("Primeiro mês do intervalo?");
    scanf(" %d", &interval[0]);
    printf("Segundo mês do intervalo?");
    scanf(" %d", &interval[1]);
    return interval;
}

char *askQuerie9Product()
{
    char *product = malloc(sizeof(char) * PRODUCT_CODE_SIZE);
    printf("Qual produto? \n");
    scanf(" %s", product);
    return product;
}

int askQuerie9Branch()
{
    int branch = -1;
    printf("Qual filial?\n");
    scanf(" %d", &branch);
    return branch;
}

char* askQuerie10Client()
{
    char *client = malloc(sizeof(char) * CLIENT_CODE_SIZE);
    printf("Qual cliente? \n");
    scanf(" %s", client);
    return client;
}

int askQuerie10Month()
{
    int month = -1;
    printf("Qual mẽs?\n");
    scanf(" %d", &month);
    return month;
}

char* askQuerie12Client()
{
    char *client = malloc(sizeof(char) * CLIENT_CODE_SIZE);
    printf("Qual cliente? \n");
    scanf(" %s", client);
    return client;
}

void querie4View(char ***products, int choice)
{
    int j, i, c, max;
    if (choice == 0) {
        i = 0;
        max = 1;
    } else {
        i = 1;
        max = 4;
    }
    for (; i < max; i++)
    {
        for (j = 0; products[i][j] != NULL; j++)
        {
            /*Fazer print em páginas*/
            /*printf("%s\n",products[i][j]);*/
        }
        printf("%d\n", j);
        for (c = 0; c < j; c++)
        {
            free(products[i][j]);
        }
    }
    /*
    for (c = 0; c < i; c++)
    {
        free(products[c]);
    }
    */
}

void querie5View(char** clients) {
    int i;
    puts("Printing codes:");
    for (i = 0; clients[i] != NULL; i++)
        printf("%s\n", clients[i]);

    printf("Clients in common: %d\n", i);
}

void querie6View(int* list) {
    printf("Products nobody bought: %d\n",list[0]);
    printf("Clients not used: %d\n",list[1]);
}
