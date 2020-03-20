#include "branch_catalog.h"
#include "billing_catalog.h"
#include "client_catalog.h"
#include "product_catalog.h"
#include "sgv.h"
#include "sale.h"
#include "utils.h"

#include <stdio.h>
#include <glib.h>

struct sgv{
    Clients client_catalog;
    Products product_catalog;
    Billings billings;
    Branches branches;
};

struct startValues{
    GString * path_clients;
    GString * path_products;
    GString * path_sales;
    gint valid_clients;
    gint read_clients;
    gint valid_products;
    gint read_products;
    gint valid_sales;
    gint read_sales;
};

typedef struct startValues * StartValues;

StartValues initStartValues(){
    StartValues startValues = g_malloc(sizeof(struct startValues));

    startValues->path_clients = g_string_new("data/Clientes.txt");
    startValues->path_products = g_string_new("data/Produtos.txt");
    startValues->path_sales = g_string_new("data/Vendas_1M.txt");
    startValues->valid_clients = 0;
    startValues->read_clients = 0;
    startValues->valid_products = 0;
    startValues->read_products = 0;
    startValues->valid_sales = 0;
    startValues->read_sales = 0;
    return startValues;
}

SGV initSGV(){
    SGV sgv = g_malloc(sizeof(struct sgv));

    sgv->client_catalog = initClients();
    sgv->product_catalog = initProducts();
    sgv->billings = initBillings();
    sgv->branches = initBranches(3);

    return sgv;
}

int parseClients(Clients clients, StartValues startValues)
{
    FILE* file_pointer = fopen((startValues->path_clients)->str,"r");
    char* _fileline = g_malloc(sizeof(char)*1024); /*Variável onde é guardada cada linha lida*/
    while(fgets(_fileline, 1024, file_pointer) != NULL)
    {
        if(addClient(clients,_fileline))
        {
            /* is okay*/
            startValues->valid_clients++;
        }
        startValues->read_clients++;
        g_free(_fileline);
        _fileline = g_malloc(sizeof(char)*1024);
    }
    g_free(_fileline);
    fclose(file_pointer);
    return 1;
}


int parseProducts(Products products, Billings bs, StartValues startValues)
{
    FILE* file_pointer = fopen((startValues->path_products)->str,"r");
    char* _fileline = g_malloc(sizeof(char)*1024); /*Variável onde é guardada cada linha lida*/
    while(fgets(_fileline, 1024, file_pointer) != NULL)
    {
        if(addProduct(products,_fileline))
        {
            /* is okay*/
            int month;
            for (month = 1; month < 13; month++) {
                addBillingProduct(getBilling(bs, month), _fileline);
            }
            startValues->valid_products++;
        }
        startValues->read_products++;
        g_free(_fileline);
        _fileline = g_malloc(sizeof(char)*1024);
    }
    g_free(_fileline);
    fclose(file_pointer);
    return 1;
}

int parseSales(SGV sgv, StartValues startValues)
{
    FILE* file_pointer = fopen((startValues->path_sales)->str,"r");
    char* _fileline = g_malloc(sizeof(char)*1024); /*Variável onde é guardada cada linha lida*/
    while(fgets(_fileline, 1024, file_pointer) != NULL)
    {
        Sale _new;
        /*Validar a venda*/
        if ((_new = isValidSale(_fileline, sgv->client_catalog, sgv->product_catalog))) {

            /* Update Billing and Branches */
            /* Updating billing using a sale */
            updateBillings(sgv->billings, _new);
            /* Updating branch using a sale */
            updateBranches(sgv->branches, _new);

            startValues->valid_sales++;
            destroySale(_new);
        }
        startValues->read_sales++;
        g_free(_fileline);
        _fileline = g_malloc(sizeof(char)*1024);
    }
    g_free(_fileline);
    fclose(file_pointer);
    return 1;
}

void destroySGV(SGV sgv){
    destroyClients(sgv->client_catalog);
    destroyProducts(sgv->product_catalog);
    destroyBranches(sgv->branches);
    destroyBillings(sgv->billings);
    g_free(sgv);
}

void destroyStartValues(StartValues sv){
    g_free(sv->path_clients);
    g_free(sv->path_products);
    g_free(sv->path_sales);
    g_free(sv);
}
void printStartValues(StartValues sv){
    printf("Path Clients:%s\n",(sv->path_clients)->str);
    printf("Path Products:%s\n",(sv->path_products)->str);
    printf("Path Sales:%s\n",(sv->path_sales)->str);
    printf("Clientes válidos: %d\n", sv->valid_clients);
    printf("Produtos válidos: %d\n", sv->valid_products);
    printf("Vendas válidas: %d\n", sv->valid_sales);
    printf("Clientes lidos: %d\n", sv->read_clients);
    printf("Produtos lidos: %d\n", sv->read_products);
    printf("Vendas lidos: %d\n", sv->read_sales);
}
int startSGV()
{
    StartValues startValues = initStartValues();
    SGV sgv = initSGV();

    parseClients(sgv->client_catalog, startValues);
    parseProducts(sgv->product_catalog, sgv->billings, startValues);
    parseSales(sgv, startValues);
    return 0;
}
