#include "view.h"
#include "constants.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void printMessage(char *message)
{
    printf("%s", message);
}

void cleanConsole()
{
    printMessage("\e[1;1H\e[2J");
}

void resetColor()
{
    printMessage("\033[0m");
}

void red()
{
    printMessage("\033[0;31m");
}

void boldRed()
{
    printMessage("\033[1;31m");
}

void green()
{
    printMessage("\033[0;32m");
}

void boldGreen()
{
    printMessage("\033[1;32m");
}

void yellow()
{
    printMessage("\033[0;33m");
}

void boldYellow()
{
    printMessage("\033[1;33m");
}

void blue()
{
    printMessage("\033[0;34m");
}

void boldBlue()
{
    printMessage("\033[1;34m");
}

void magenta()
{
    printMessage("\033[0;35m");
}

void boldMagenta()
{
    printMessage("\033[1;35m");
}

void cyan()
{
    printMessage("\033[1;36m");
}

void boldCyan()
{
    printMessage("\033[1;36m");
}

void printMenu()
{
    printMessage("! --------------- !\n");
    printMessage("1  - Query 1\n");
    printMessage("2  - Query 2\n");
    printMessage("3  - Query 3\n");
    printMessage("4  - Query 4\n");
    printMessage("5  - Query 5\n");
    printMessage("6  - Query 6\n");
    printMessage("7  - Query 7\n");
    printMessage("8  - Query 8\n");
    printMessage("9  - Query 9\n");
    printMessage("10 - Query 10\n");
    printMessage("11 - Query 11\n");
    printMessage("12 - Query 12\n");
    printMessage("13 - Query 13\n");
    printMessage("*  - Exit\n");
    printMessage("! --------------- !\n");
    boldCyan();
}

void printSeparator()
{
    printMessage("===========================\n");
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
    printMessage("Path Clients:%s\n", clients_path);
    printMessage("Path Products:%s\n", products_path);
    printMessage("Path Sales:%s\n", sales_path);
    printMessage("Clientes válidos: %d\n", valid_clients);
    printMessage("Produtos válidos: %d\n", valid_products);
    printMessage("Vendas válidas: %d\n", valid_sales);
    printMessage("Clientes lidos: %d\n", clients_read);
    printMessage("Produtos lidos: %d\n", products_read);
    printMessage("Vendas lidas: %d\n", sales_read);
    resetColor();
    printSeparator();
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
    printMessage("--------- Página %d de %d ---------\n", page, max);
    boldGreen();
    for (i = page * 10, j = 0; j < ELEMENTS_PER_PAGE && list[i] != 0; i++, j++)
    {
        printMessage("%s\n", list[i]);
    }
    resetColor();
    printMessage("--------- Página %d de %d ---------\n", page, max);
    printMessage("n - Próxima página\np - Página anterior\nc - Escolher página\n");
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
        printMessage("--------- Global\n");
    }
    else
    {
        printMessage("--------- Filial %d\n", branch + 1);
    }
    printMessage("--------- Página %d de %d ---------\n", page, max);
    boldGreen();
    for (i = page * 10, j = 0; j < ELEMENTS_PER_PAGE && list[i] != 0; i++, j++)
    {
        printMessage("%s\n", list[i]);
    }
    resetColor();
    printMessage("--------- Página %d de %d ---------\n", page, max);
    printMessage("--------- TOTAL ---------\n");
    printMessage("%d\n", sizes[branch]);
    printMessage("--------- TOTAL ---------\n");
    if (branch == 0 && global == 1)
    {
        printMessage("n - Próxima página\np - Página anterior\nc - Escolher página\n");
    }
    else
    {
        printMessage("n - Próxima página\np - Página anterior\nc - Escolher página\nt - Filial seguinte\n");
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

        printMessage("--------- Cliente %s\n", client);
        boldGreen();
        /* Imprimir meses */
        printMessage("    ");
        printMessage("|");
        for (j = 0; j < columns; j++)
        {
            for (h = 0; h < ((space - 3) / 2); h++)
                printMessage(" ");

            printMessage("%s", _text[j]);

            for (h = 0; h < ((space - 3) / 2); h++)
                printMessage(" ");

            printMessage("|");
        }
        printMessage("\n");
        printMessage("----+");
        for (i = 0; i < columns; i++)
        {
            for (j = 0; j < space; j++)
                printMessage("-");
            printMessage("+");
        }
        printMessage("\n");

        /* Inicio da linha com o n da filial*/
        for (i = 0; i < rows; i++)
        {
            printMessage("%d", i + 1);
            printMessage("   ");
            printMessage("|");
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
                    printMessage(" ");
                printMessage("%d", list[i][j]);
                printMessage("|");
            }
            printMessage("\n");
        }
        resetColor();
    }
    else
    {
        boldRed();
        printMessage("Cliente não existe.\n");
    }
    resetColor();
}

void querie2View(char **list)
{
    int i;
    for (i = 0; list[i] != NULL; i++)
    {
        printMessage("ELEM:%s\n", (char *)list[i]);
    }
    printMessage("Number of products: %d\n", i);
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
            printMessage("------ Filial %d (%s) ------\n", branch, product);
            branch++;
        }
        else if (branch == 1)
        {
            printMessage("------ Global (%s) ------\n", product);
            branch++;
        }
        boldGreen();
        printMessage("%s%f\n", _text[j], products[i]);
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
        printMessage("%s\n", clients[i]);

    printMessage("Clients in common: %d\n", i);
}

void querie6View(int *list)
{
    cleanConsole();
    boldGreen();
    printMessage("Produtos que ninguém comprou: %d\n", list[0]);
    printMessage("Clientes que não compraram: %d\n", list[1]);
    resetColor();
}

void querie7View(int **totals)
{
    int branch = 0;
    int month = 1;

    for (; branch < 3; branch++)
    {
        printMessage("--------- Filial %d ---------\n", branch + 1);

        for (; month < 12; month++)
        {
            printMessage("--- Mês %d ---\n", month + 1);
            printMessage("Total: %d\n", totals[branch][month]);
        }
        month = 0;
    }
}

void querie8View(Query8Aux aux, int first, int second)
{
    cleanConsole();
    resetColor();
    printMessage("--------- Meses [%d-%d] ---------\n", first, second);
    boldGreen();
    printMessage("Unidades vendidas: %d\n", getQuery8AuxUnits(aux));
    printMessage("Total faturado: %f\n", getQuery8AuxBilled(aux));
    printMessage("Registo de Vendas: %d\n", getQuery8AuxSales(aux));
    resetColor();
    printMessage("--------- Meses [%d-%d] ---------\n", first, second);
}

void querie9View(Query9Aux aux, char type, int page)
{
    cleanConsole();

    if (aux == NULL)
    {
        boldRed();
        printMessage("Produto inválido\n");
    }
    else
    {
        int totalN = getQuery9TotalN(aux);
        int totalP = getQuery9TotalP(aux);
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
        printMessage("--------- Produtos %c\n", type);
        printMessage("--------- Página %d de %d ---------\n", page, max);
        boldGreen();
        for (i = page * 10, j = 0; j < ELEMENTS_PER_PAGE && i < size; i++, j++)
        {
            if (type == 'N')
            {
                printMessage("%s\n", getQuery9ClientN(aux, i));
            }
            else
            {
                printMessage("%s\n", getQuery9ClientP(aux, i));
            }
        }
        resetColor();
        printMessage("--------- Página %d de %d ---------\n", page, max);
        printMessage("--------- TOTAL %c: ---------\n", type);
        boldGreen();
        if (type == 'N')
        {
            printMessage("Quantidade: %d\n", totalN);
        }
        else
        {
            printMessage("Quantidade: %d\n", totalP);
        }
        resetColor();
        printMessage("--------- TOTAL %c: ---------\n", type);
        printMessage("n - Próxima página\np - Página anterior\nc - Escolher página\nt - Mudar tipo\n");
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
    printMessage("--------- Cliente (%s)\n", client);
    printMessage("--------- Página %d de %d ---------\n", page, max);
    boldGreen();
    for (i = page * 10, j = 0; j < ELEMENTS_PER_PAGE && i < n; i++, j++)
    {
        printMessage("Produto: %s | Unidades: %d\n", getInfoProduct(info[i]), getInfoUnitsSold(info[i]));
    }
    resetColor();
    printMessage("--------- Página %d de %d ---------\n", page, max);
    printMessage("n - Próxima página\np - Página anterior\nc - Escolher página\n");
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
    printMessage("--------- Página %d de %d ---------\n", page, max);
    boldGreen();
    for (i = page * 2, j = 0; j < 2 && i < n; j++)
    {
        Aux aux = result[i];
        printMessage("--------- Produto %s (%dº)\n", getAuxProduct(aux), i + 1);
        for (h = 0; h < N_BRANCHES; h++)
        {
            printMessage("Filial: %d | Total de clientes diferentes: %d | Unidades vendidas: %d\n", (h + 1), getAuxTotalClients(aux, h), getAuxUnitsSold(aux, h));
        }
        aux = result[i++];
    }
    resetColor();
    printMessage("--------- Página %d de %d ---------\n", page, max);
    printMessage("n - Próxima página\np - Página anterior\nc - Escolher página\n");
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
    printMessage("--------- Cliente (%s)\n", client);
    printMessage("--------- Página %d de %d ---------\n", page, max);
    boldGreen();
    for (i = page * 10, j = 0; j < ELEMENTS_PER_PAGE && i < n; i++, j++)
    {
        Money money = list[i];
        printMessage("Produto: %s | Gastou: %f\n", getMoneyProduct(money), getMoneySpent(money));
    }
    resetColor();
    printMessage("--------- Página %d de %d ---------\n", page, max);
    printMessage("n - Próxima página\np - Página anterior\nc - Escolher página\n");
    boldCyan();
    /* Pagina inicial */
}
