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
    printf("*  - Exit\n");
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
    resetColor();
    printf("Clients's file path: ");
    scanf("%s", clients_path);
    boldCyan();
}

void askProductsPath(char *products_path)
{
    resetColor();
    printf("Products's file path: ");
    scanf("%s", products_path);
    boldCyan();
}

void askSalesPath(char *sales_path)
{
    resetColor();
    printf("Sales's file path: ");
    scanf("%s", sales_path);
    boldCyan();
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
    resetColor();
    char letter;
    printf("1 - Choose product first letter\n");
    boldCyan();
    scanf(" %c", &letter);
    toupper(letter);
    resetColor();
    return letter;
}

char *askProduct()
{
    char *product = malloc(sizeof(char) * PRODUCT_CODE_SIZE);
    resetColor();
    printf("Qual produto? \n");
    boldCyan();
    scanf(" %s", product);
    resetColor();
    return product;
}

int askMonth()
{
    int month = -1;
    while (month <= 0 || month > 12)
    {
        resetColor();
        printf("Qual mês?: \n");
        boldCyan();
        scanf(" %d", &month);
        resetColor();
    }
    return month;
}

char *askClient()
{
    char *client = malloc(sizeof(char) * CLIENT_CODE_SIZE);
    resetColor();
    printf("Qual cliente? \n");
    boldCyan();
    scanf(" %s", client);
    resetColor();
    return client;
}

int *askMonthInterval()
{
    int *interval = malloc(sizeof(int) * 2);
    resetColor();
    printf("Primeiro mês do intervalo?\n");
    boldCyan();
    scanf(" %d", &interval[0]);
    resetColor();
    printf("Segundo mês do intervalo?\n");
    boldCyan();
    scanf(" %d", &interval[1]);
    resetColor();
    return interval;
}

int askBranch()
{
    int branch = -1;
    while (branch < 1 || branch > 3)
    {
        printf("Qual filial?\n");
        boldCyan();
        scanf(" %d", &branch);
        resetColor();
    }
    return branch;
}

int askQuerie3Choice()
{
    int choice = -1;
    while (choice != 0 && choice != 1)
    {
        printf("0 - Filial a filial\n1 - Global: \n");
        boldCyan();
        scanf(" %d", &choice);
        resetColor();
    }
    return choice;
}

int askQuerie4Choice()
{
    int choice = -1;
    while (choice != 0 && choice != 1)
    {
        resetColor();
        printf("0 - Global\n1 - Filial a Filial: \n");
        boldCyan();
        scanf(" %d", &choice);
        resetColor();
    }
    return choice;
}

int askQuerie11N()
{
    int n = 0;
    while (n <= 0)
    {
        resetColor();
        printf("Quantos produtos pretende ver?\n");
        boldCyan();
        scanf(" %d", &n);
        resetColor();
    }
    return n;
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
    resetColor();
    printf("--------- Página %d de %d ---------\n", page, max);
    boldGreen();
    for (i = page * 10, j = 0; j < ELEMENTS_PER_PAGE && list[i] != 0; i++, j++)
    {
        printf("%s\n", list[i]);
    }
    resetColor();
    printf("--------- Página %d de %d ---------\n", page, max);
    printf("n - Próxima página\np - Página anterior\nc - Escolher página\n");
    boldCyan();
    /* Pagina inicial */

    scanf(" %s", choice);
    resetColor();
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
        boldGreen();
        for (i = page * 10, j = 0; j < ELEMENTS_PER_PAGE && list[i] != 0; i++, j++)
        {
            printf("%s\n", list[i]);
        }
        resetColor();
        printf("--------- Página %d de %d ---------\n", page, max);
        printf("n - Próxima página\np - Página anterior\nc - Escolher página\n");
        boldCyan();
        *choice = 0;
        scanf(" %s", choice);
        resetColor();
    }
    cleanConsole();
}

void tableView(int **list, char *client)
{
    cleanConsole();
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

        printf("--------- Cliente %s\n", client);
        boldGreen();
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
        for (i = 0; i < columns; i++)
        {
            for (j = 0; j < space; j++)
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
        resetColor();
    }
    else
    {
        boldRed();
        printf("Cliente não existe.\n");
    }
    resetColor();
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

void querie3View(double *products, int choice, char *product)
{
    cleanConsole();
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
            printf("------ Filial %d (%s) ------\n", branch, product);
            branch++;
        }
        else if (branch == 1)
        {
            printf("------ Global (%s) ------\n", product);
            branch++;
        }
        boldGreen();
        printf("%s%f\n", _text[j], products[i]);
        resetColor();
        if (j == 3)
        {
            j = -1;
        }
    }
}

void querie4View(char ***products, int choice, int branch, int size)
{
    if (choice == 0)
    {
        listView(products[0], size);
    }
    else
    {
        listView(products[branch], size);
    }
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
    cleanConsole();
    boldGreen();
    printf("Produtos que ninguém comprou: %d\n", list[0]);
    printf("Clientes que não compraram: %d\n", list[1]);
    resetColor();
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

void querie8View(Querie8Aux aux, int first, int second)
{
    cleanConsole();
    resetColor();
    printf("--------- Meses [%d-%d] ---------\n", first, second);
    boldGreen();
    printf("Unidades vendidas: %d\n", getQuerie8AuxUnits(aux));
    printf("Total faturado: %f\n", getQuerie8AuxBilled(aux));
    printf("Registo de Vendas: %d\n", getQuerie8AuxSales(aux));
    resetColor();
    printf("--------- Meses [%d-%d] ---------\n", first, second);
}

void querie9View(char ***array, int *total_N, int *total_P)
{
    cleanConsole();

    if (array == NULL)
    {
        boldRed();
        printf("Produto inválido\n");
    }
    else
    {
        int i;

        resetColor();
        puts("--------- Clientes N: ---------");
        boldGreen();
        for (i = 0; array[0][i] && i < *total_N; i++)
        {
            printf("%s\n", array[0][i]);
        }

        resetColor();
        puts("--------- Clientes P: ---------");
        boldGreen();
        for (i = 0; array[1][i] && i < *total_P; i++)
        {
            printf("%s\n", array[1][i]);
        }

        resetColor();
        puts("--------- TOTAIS: ---------");
        boldGreen();
        printf("N = %d\nP = %d\n", *total_N, *total_P);
    }
    resetColor();
}

void querie10View(Info *info, char *client)
{
    cleanConsole();
    int i = 0;
    printf("--------- Cliente %s\n", client);
    boldGreen();
    for (i = 0; info[i] != NULL; i++)
    {
        printf("Produto: %s | Unidades: %d\n", getInfoProduct(info[i]), getInfoUnitsSold(info[i]));
    }
    resetColor();
}

void querie11View(Aux *result, int n)
{
    cleanConsole();
    int k, j;
    for (k = 0; k < n; k++)
    {
        Aux aux = result[k];
        printf("--------- Produto %s (%dº)\n", getAuxProduct(aux), k + 1);
        boldGreen();
        for (j = 0; j < N_BRANCHES; j++)
        {
            printf("Filial: %d | Total de clientes diferentes: %d | Unidades vendidas: %d\n", (j + 1), getAuxTotalClients(aux,j),getAuxUnitsSold(aux,j));
        }
        resetColor();
    }
}

void querie12View(Money *result, int n)
{
    cleanConsole();
    int k;
    boldGreen();
    for (k = 0; k < n; k++)
    {
        Money money = result[k];
        printf("Produto: %s | Gastou: %f\n", getMoneyProduct(money), getMoneySpent(money));
    }
    resetColor();
}
