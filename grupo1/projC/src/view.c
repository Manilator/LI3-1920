#include "view.h"
#include "constants.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

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

char askProductLetter()
{
    char letter;
    printf("1 - Choose product first letter\n");
    scanf(" %c", &letter);
    toupper(letter);
    return letter;
}

char *askProduct()
{
    char *product = malloc(sizeof(char) * PRODUCT_CODE_SIZE);
    printf("Qual produto? \n");
    scanf(" %s", product);
    return product;
}

int askMonth()
{
    int month = -1;
    printf("Qual mês?: \n");
    scanf(" %d", &month);
    return month;
}

char *askClient()
{
    char *client = malloc(sizeof(char) * CLIENT_CODE_SIZE);
    printf("Qual cliente? \n");
    scanf(" %s", client);
    return client;
}

int *askMonthInterval()
{
    int *interval = malloc(sizeof(int) * 2);
    printf("Primeiro mês do intervalo?");
    scanf(" %d", &interval[0]);
    printf("Segundo mês do intervalo?");
    scanf(" %d", &interval[1]);
    return interval;
}

int askBranch()
{
    int branch = -1;
    printf("Qual filial?\n");
    scanf(" %d", &branch);
    return branch;
}

int askQuerie3Choice()
{
    int choice = -1;
    printf("0 - Filial a filial\n1 - Global: \n");
    scanf(" %d", &choice);
    return choice;
}

int askQuerie4Choice()
{
    int choice = -1;
    printf("0 - Global\n1 - Filial a Filial: \n");
    scanf(" %d", &choice);
    return choice;
}

void listView(char **list, int size)
{
    int page = 0;
    int max = size / ELEMENTS_PER_PAGE;
    int i;
    int j = 0;
    char *choice = malloc(sizeof(char) * 32);

    /* Página inicial */
    cleanConsole();
    printf("--------- Página %d de %d ---------\n", page, max);
    for (i = page * 10, j = 0; j < ELEMENTS_PER_PAGE && list[i] != 0; i++, j++)
    {
        printf("%s\n", list[i]);
    }
    printf("--------- Página %d de %d ---------\n", page, max);
    printf("n - Próxima página\np - Página anterior\nc - Escolher página\n");
    /* Pagina inicial */

    scanf(" %s", choice);
    for (; page <= max && page >= 0 && choice[0] != '0';)
    {
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
            printf("Número da página:\n");
            scanf(" %s", choice);
            while (atoi(choice) > max || page < 0)
            {
                printf("Página não existe. Insira novo número:\n");
                scanf(" %s", choice);
            }
            page = atoi(choice);
        }
        cleanConsole();
        printf("--------- Página %d de %d ---------\n", page, max);
        for (i = page * 10, j = 0; j < ELEMENTS_PER_PAGE && list[i] != 0; i++, j++)
        {
            printf("%s\n", list[i]);
        }
        printf("--------- Página %d de %d ---------\n", page, max);
        printf("n - Próxima página\np - Página anterior\nc - Escolher página\n");
        *choice = 0;
        scanf(" %s", choice);
    }
    cleanConsole();
}

void tableView(int **list)
{
    if (list != NULL)
    {

        int columns = MONTHS;
        int rows = N_BRANCHES;
        int space = 0;
        int ss = 0;
        char *_text[12] = {"Jan", "Fev", "Mar", "Abr", "Mai", "Jun", "Jul", "Ago", "Set", "Out", "Nov", "Dez"};

        int i, j, h;

        /* Calcular o maior valor da lista */
        for (i = 0; i < 3; i++)
        {
            for (j = 0; j < 12; j++)
            {
                if (floor(log10(abs(list[i][j]))) + 1 > space)
                {
                    space = floor(log10(abs(list[i][j]))) + 1;
                }
            }
        }

        /* Determinar espaço das colunas */
        if (space <= 3)
        {
            space = 5;
        }
        else
        {
            if (space % 2 == 0)
            {
                space++;
            }
        }
        /* Imprimir meses */
        printf("    ");
        printf("|");
        for (j = 0; j < columns; j++)
        {
            for (h = 0; h < ((space - 3) / 2); h++)
                printf(" ");

            printf("%s", _text[j]);

            for (h = 0; h < ((space - 3) / 2); h++)
                printf(" ");

            printf("|");
        }
        printf("\n");
        printf("----+");
        for (i = 0; i < columns; i++) {
            for(j = 0; j < space; j++)
                printf("-");
            printf("+");
        }
        printf("\n");

        /* Inicio da linha com o n da filial*/
        for (i = 0; i < rows; i++)
        {
            printf("%d", i + 1);
            printf("   ");
            printf("|");
            for (j = 0; j < columns; j++)
            {
                if (list[i][j] == 0)
                {
                    ss = 2;
                }
                else
                {
                    ss = floor(log10(abs(list[i][j]))) + 2;
                }
                for (h = 0; h <= (space - ss); h++)
                    printf(" ");
                printf("%d", list[i][j]);
                printf("|");
            }
            printf("\n");
        }
    } else {
        printf("Cliente não existe.\n");
    }
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

void querie3View(double *products, int choice)
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
    /*printf("Number of products: %d\n", i);*/
}

void querie4View(char ***products, int choice)
{
    int j, i, c, max;
    if (choice == 0)
    {
        i = 0;
        max = 1;
    }
    else
    {
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

void querie5View(char **clients)
{
    int i;
    puts("Printing codes:");
    for (i = 0; clients[i] != NULL; i++)
        printf("%s\n", clients[i]);

    printf("Clients in common: %d\n", i);
}

void querie6View(int *list)
{
    printf("Products nobody bought: %d\n", list[0]);
    printf("Clients not used: %d\n", list[1]);
}

void querie7View(int **totals)
{
    int branch = 0;
    int month = 1;

    for (; branch < 3; branch++)
    {
        printf("--------- Filial %d ---------\n", branch + 1);

        for (; month < 12; month++)
        {
            printf("--- Mês %d ---\n", month + 1);
            printf("Total: %d\n", totals[branch][month]);
        }
        month = 0;
    }
}

void querie9View(char ***array, int *total_N, int *total_P)
{

    if (array == NULL)
    {
        printf("Valores inválidos\n");
    }
    else
    {
        int i;

        puts("--------- CODIGOS N: ---------");
        for (i = 0; array[0][i] && i < *total_N; i++)
        {
            printf("%s\n", array[0][i]);
        }

        puts("--------- CODIGOS P: ---------");
        for (i = 0; array[1][i] && i < *total_P; i++)
        {
            printf("%s\n", array[1][i]);
        }

        puts("--------- TOTAIS: ---------");
        printf("N = %d\nP = %d\n", *total_N, *total_P);
    }
}

void querie10View(char **products)
{
    int i = 0;

    if (products == NULL)
    {
        printf("Cliente inválido ou não realizou nenhuma compra.\n");
    }
    else
    {
        for (i = 0; products[i] != NULL; i++)
        {
            printf("%s\n", products[i]);
        }
    }
}
