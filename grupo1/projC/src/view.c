#include "view.h"
#include "constants.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    printf("1  - Query 1\n");
    printf("2  - Query 2\n");
    printf("3  - Query 3\n");
    printf("4  - Query 4\n");
    printf("5  - Query 5\n");
    printf("6  - Query 6\n");
    printf("7  - Query 7\n");
    printf("8  - Query 8\n");
    printf("9  - Query 9\n");
    printf("10 - Query 10\n");
    printf("11 - Query 11\n");
    printf("12 - Query 12\n");
    printf("13 - Query 13\n");
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
    resetColor();
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

void printMessage(char *message)
{
    printf("%s", message);
}

void listView(char **list, int size, int page)
{
    int max = size / ELEMENTS_PER_PAGE;
    int i;
    int j = 0;
    /*char *choice = malloc(sizeof(char) * 32);*/

    if (page > max || page < 0)
    {
        page = 0;
    }

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

    /*scanf(" %s", choice);*/
    resetColor();
}

void querie4View(char ***products, int global, int branch, int *sizes, int page)
{
    int max = sizes[branch] / ELEMENTS_PER_PAGE;
    int i;
    int j = 0;
    char *choice = malloc(sizeof(char) * 32);

    /* Página inicial */
    cleanConsole();
    resetColor();
    char **list = products[branch];
    if (branch == 0 && global == 1)
    {
        printf("--------- Global\n");
    }
    else
    {
        printf("--------- Filial %d\n", branch + 1);
    }
    printf("--------- Página %d de %d ---------\n", page, max);
    boldGreen();
    for (i = page * 10, j = 0; j < ELEMENTS_PER_PAGE && list[i] != 0; i++, j++)
    {
        printf("%s\n", list[i]);
    }
    resetColor();
    printf("--------- Página %d de %d ---------\n", page, max);
    printf("--------- TOTAL ---------\n");
    printf("%d\n", sizes[branch]);
    printf("--------- TOTAL ---------\n");
    if (branch == 0 && global == 1)
    {
        printf("n - Próxima página\np - Página anterior\nc - Escolher página\n");
    }
    else
    {
        printf("n - Próxima página\np - Página anterior\nc - Escolher página\nt - Filial seguinte\n");
    }
    /*boldCyan();*/
    /* Pagina inicial */
    g_free(choice);
    resetColor();
    /*cleanConsole();*/
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
        length = N_BRANCHES + 1;
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

void querie8View(Query8Aux aux, int first, int second)
{
    cleanConsole();
    resetColor();
    printf("--------- Meses [%d-%d] ---------\n", first, second);
    boldGreen();
    printf("Unidades vendidas: %d\n", getQuery8AuxUnits(aux));
    printf("Total faturado: %f\n", getQuery8AuxBilled(aux));
    printf("Registo de Vendas: %d\n", getQuery8AuxSales(aux));
    resetColor();
    printf("--------- Meses [%d-%d] ---------\n", first, second);
}

void querie9View(Query9Aux aux, char type, int page)
{
    cleanConsole();

    if (aux == NULL)
    {
        boldRed();
        printf("Produto inválido\n");
    }
    else
    {
        int totalN = getQuerie9TotalN(aux);
        int totalP = getQuerie9TotalP(aux);
        int size = 0;
        if (type == 'N')
        {
            size = totalN;
        }
        else
        {
            size = totalP;
        }
        int max = size / ELEMENTS_PER_PAGE;
        int i;
        int j = 0;

        /* Página inicial */
        cleanConsole();
        resetColor();
        printf("--------- Produtos %c\n", type);
        printf("--------- Página %d de %d ---------\n", page, max);
        boldGreen();
        for (i = page * 10, j = 0; j < ELEMENTS_PER_PAGE && i < size; i++, j++)
        {
            if (type == 'N')
            {
                printf("%s\n", getQuerie9ClientN(aux, i));
            }
            else
            {
                printf("%s\n", getQuerie9ClientP(aux, i));
            }
        }
        resetColor();
        printf("--------- Página %d de %d ---------\n", page, max);
        printf("--------- TOTAL %c: ---------\n", type);
        boldGreen();
        if (type == 'N')
        {
            printf("Quantidade: %d\n", totalN);
        }
        else
        {
            printf("Quantidade: %d\n", totalP);
        }
        resetColor();
        printf("--------- TOTAL %c: ---------\n", type);
        printf("n - Próxima página\np - Página anterior\nc - Escolher página\nt - Mudar tipo\n");
        boldCyan();
        /* Pagina inicial */
    }

    resetColor();
}

void querie10View(Info *info, int n, char *client, int page)
{
    int max = n / ELEMENTS_PER_PAGE;
    int i;
    int j = 0;

    /* Página inicial */
    cleanConsole();
    resetColor();
    printf("--------- Cliente (%s)\n", client);
    printf("--------- Página %d de %d ---------\n", page, max);
    boldGreen();
    for (i = page * 10, j = 0; j < ELEMENTS_PER_PAGE && i < n; i++, j++)
    {
        printf("Produto: %s | Unidades: %d\n", getInfoProduct(info[i]), getInfoUnitsSold(info[i]));
    }
    resetColor();
    printf("--------- Página %d de %d ---------\n", page, max);
    printf("n - Próxima página\np - Página anterior\nc - Escolher página\n");
    boldCyan();
    /* Pagina inicial */
    resetColor();
}

void querie11View(Aux *result, int n, int page)
{
    int max;
    if (n % 2 != 0)
    {
        max = n / 2;
    }
    else
    {
        max = n / 2 - 1;
    }
    int i = 0;
    int j = 0;
    int h = 0;

    /* Página inicial */
    cleanConsole();
    resetColor();
    printf("--------- Página %d de %d ---------\n", page, max);
    boldGreen();
    for (i = page * 2, j = 0; j < 2 && i < n; j++)
    {
        Aux aux = result[i];
        printf("--------- Produto %s (%dº)\n", getAuxProduct(aux), i + 1);
        for (h = 0; h < N_BRANCHES; h++)
        {
            printf("Filial: %d | Total de clientes diferentes: %d | Unidades vendidas: %d\n", (h + 1), getAuxTotalClients(aux, h), getAuxUnitsSold(aux, h));
        }
        aux = result[i++];
    }
    resetColor();
    printf("--------- Página %d de %d ---------\n", page, max);
    printf("n - Próxima página\np - Página anterior\nc - Escolher página\n");
    boldCyan();
    /* Pagina inicial */
   resetColor();
}

void querie12View(Money *list, int n, char *client, int page)
{
    int max = n / ELEMENTS_PER_PAGE;
    int i;
    int j = 0;

    /* Página inicial */
    cleanConsole();
    resetColor();
    printf("--------- Cliente (%s)\n", client);
    printf("--------- Página %d de %d ---------\n", page, max);
    boldGreen();
    for (i = page * 10, j = 0; j < ELEMENTS_PER_PAGE && i < n; i++, j++)
    {
        Money money = list[i];
        printf("Produto: %s | Gastou: %f\n", getMoneyProduct(money), getMoneySpent(money));
    }
    resetColor();
    printf("--------- Página %d de %d ---------\n", page, max);
    printf("n - Próxima página\np - Página anterior\nc - Escolher página\n");
    boldCyan();
    /* Pagina inicial */
}
