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

StartValues initStartValues(char* clients_path, char* products_path, char* sales_path){
    StartValues startValues = g_malloc(sizeof(struct startValues));

    startValues->path_clients = g_string_new(clients_path);
    startValues->path_products = g_string_new(products_path);
    startValues->path_sales = g_string_new(sales_path);
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
                insertBillingProduct(bs, month, _fileline);
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

SGV startSGV(SGV sgv, StartValues sv)
{
    parseClients(sgv->client_catalog, sv);
    parseProducts(sgv->product_catalog, sgv->billings, sv);
    parseSales(sgv, sv);
    return sgv;
}

/*
 * [QUERIE 2] - Returns all of the product codes started by "letter"
*/
GSList * productsByLetter(SGV sgv, char letter){
    return getProductsByLetter(sgv->product_catalog, letter);
    /*printf("ELEM:");
    GSList * new = getProductsByLetter(sgv->product_catalog, letter);
    int i,len;
    len = (int)(g_slist_length(new));
    for (i = 0; i < len; i++) {
        printf("ELEM:%s\n",(char*)(new->data));
        new = g_slist_next(new);
    }
    printf("%d\n", len);
    return NULL;*/
}

/*
 * [QUERIE 3]
*/
float * productValuesByMonth(SGV sgv, char* product_code, int month, int branches){
    return getProductValuesByMonthBillingCat(sgv->billings, product_code, month, branches);
}

char* getClientsPath(StartValues sv) {
    return (sv->path_clients)->str;
}

char* getProductsPath(StartValues sv) {
    return (sv->path_products)->str;
}

char* getSalesPath(StartValues sv) {
    return (sv->path_sales)->str;
}

int getValidClients(StartValues sv) {
    return sv->valid_clients;
}

int getValidProducts(StartValues sv) {
    return sv->valid_products;
}

int getValidSales(StartValues sv) {
    return sv->valid_sales;
}

int getReadClients (StartValues sv) {
    return sv->read_clients;
}

int getReadProducts (StartValues sv) {
    return sv->read_products;
}

int getReadSales (StartValues sv) {
    return sv->read_sales;
}

/* QUERY 5 */
void query5(SGV sgv)
{
    /*
    int *n = g_malloc(sizeof(int));
    char** codes = clientsInCommon(sgv->branches, n);

    int i;
    puts("Printing codes:");
    for(i = 0; i < *n; i++)
        printf("%s\n", codes[i]);
    puts("End of codes.");

    printf("Clients in common: %d\n", *n);
    */
    printBranch1(sgv->branches);
}
