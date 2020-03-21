#include "view.h"
#include "constants.h"

#include <stdio.h>
#include <string.h>

void cleanConsole() {
    printf("\e[1;1H\e[2J");
}

void printMenu() {
    printf("! --------------- !\n");
    printf("1 - Querie 1\n");
    printf("2 - Querie 2\n");
    printf("3 - Querie 3\n");
    printf("4 - Querie 4\n");
    printf("5 - Querie 5\n");
    printf("6 - Querie 6\n");
    printf("7 - Querie 7\n");
    printf("8 - Querie 8\n");
    printf("9 - Querie 9\n");
    printf("10 - Querie 10\n");
    printf("11 - Querie 11\n");
    printf("12 - Querie 12\n");
    printf("! --------------- !\n");
}

void printSeparator() {
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
    printf("Path Clients:%s\n", clients_path);
    printf("Path Products:%s\n", products_path);
    printf("Path Sales:%s\n", sales_path);
    printf("Clientes válidos: %d\n", valid_clients);
    printf("Produtos válidos: %d\n", valid_products);
    printf("Vendas válidas: %d\n", valid_sales);
    printf("Clientes lidos: %d\n", clients_read);
    printf("Produtos lidos: %d\n", products_read);
    printf("Vendas lidos: %d\n", sales_read);
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

void querie1View(char* clients_path, char* products_path, char* sales_path)
{
    char choice = '0';
    printf("1 - Choose files path\nOther value - Default paths\n");
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
    
}