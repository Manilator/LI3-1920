#include "branch_catalog.h"
#include "billing_catalog.h"
#include "client_catalog.h"
#include "product_catalog.h"
#include "sgv.h"
#include "sale.h"
#include "utils.h"

#include <stdio.h>
#include <glib.h>

int parseClients(char* filename, Clients clients)
{
    FILE* file_pointer = fopen(filename,"r");
    /*int total_read = 0;*/
    char* _fileline = g_malloc(sizeof(char)*1024); /*Variável onde é guardada cada linha lida*/
    printf("%s: \n",filename);
    while(fgets(_fileline, 1024, file_pointer) != NULL)
    {
        if(addClient(clients,_fileline))
        {
            /* is okay*/
        }
        g_free(_fileline);
        _fileline = g_malloc(sizeof(char)*1024);
    }
    g_free(_fileline);
    fclose(file_pointer);
    return getSizeClients(clients);
}


int parseProducts(char* filename, Products products, Faturas fs)
{
    FILE* file_pointer = fopen(filename,"r");
    /*int total_read = 0;*/
    char* _fileline = g_malloc(sizeof(char)*1024); /*Variável onde é guardada cada linha lida*/
    printf("%s: \n",filename);
    while(fgets(_fileline, 1024, file_pointer) != NULL)
    {
        /*_fileline = cleanString(_fileline);*/
        if(addProduct(products,_fileline))
        {
            /* is okay*/
            int month;
            for (month = 1; month < 13; month++) {
                addFaturaProduto(getFatura(fs, month), _fileline);
            }
            /*printf("Teste: %f\n", getTotalFaturadoN_FP(getFaturaProduto(getFatura(fs,0), _fileline)));*/
            /*printf("First Key: %s\n", getFirstKey(getFatura(fs,0)));*/


        }
        g_free(_fileline);
        _fileline = g_malloc(sizeof(char)*1024);
    }
    g_free(_fileline);
    fclose(file_pointer);
    return getSizeProducts(products);
}

int parseSales(char* filename, Filiais branches, Faturas faturas, Clients clients, Products products)
{
    FILE* file_pointer = fopen(filename,"r");
    int valid_sales = 0;
    int total_read = 0;
    char* _fileline = g_malloc(sizeof(char)*1024); /*Variável onde é guardada cada linha lida*/
    printf("%s: \n",filename);
    while(fgets(_fileline, 1024, file_pointer) != NULL)
    {
        Sale _new;
        /*Validar a venda*/
        if ((_new = isValidSale(_fileline, clients, products))) {

            /* Atualizar as Filiais e Faturação */
            /* Atualizar fatura usando a sale */
            updateFaturas(faturas, _new);
            /* Atualizar Filial usando a sale */
            updateFiliais(branches, _new);

            ++valid_sales;
            destroySale(_new);
        }
        ++total_read;
        g_free(_fileline);
        _fileline = g_malloc(sizeof(char)*1024);
    }
    g_free(_fileline);
    fclose(file_pointer);
    printf("Válidos: %d\n", valid_sales);
    return total_read;
}
/*printf("TOTAL:%f\n",getTotalFaturadoFatura(getFatura(faturas,2)));*/

int coolfunc()
{
    Clients clients = initClients();
    Products products = initProducts();
    /*Sales sales = initSales();*/
    Filiais branches = initFiliais(3);
    Faturas faturas = initFaturas();

    int total_clients = parseClients("data/Clientes.txt", clients);
    int total_products = parseProducts("data/Produtos.txt",products,faturas);
    int total_sales = parseSales("data/Vendas_1M.txt",branches, faturas, clients, products);

    printf("Clients: %d\n", total_clients);
    destroyClients(clients);
    printf("Products: %d\n", total_products);
    destroyProducts(products);
    printf("Sales: %d\n", total_sales);
    freeFiliais(branches);
    freeFaturas(faturas);
    return 0;
}
