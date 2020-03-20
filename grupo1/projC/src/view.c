#include "view.h"

#include <stdio.h>


void viewPrintStartValues(char *clients_path,
                          char *products_path,
                          char *sales_path,
                          int   valid_clients,
                          int   valid_products,
                          int   valid_sales,
                          int   clients_read,
                          int   products_read,
                          int   sales_read)
{
    printf("Path Clients:%s\n", clients_path);
    printf("Path Products:%s\n", products_path);
    printf("Path Sales:%s\n", sales_path);
    printf("Clientes válidos: %d\n", valid_clients);
    printf("Produtos válidos: %d\n", valid_products);
    printf("Vendas válidas: %d\n", valid_sales);
    printf("Clientes lidos: %d\n", clients_read);
    printf("Produtos lidos: %d\n", products_read);
    printf("Vendas lidos: %d\n", sales_read);
}
