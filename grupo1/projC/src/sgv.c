#include "branch_catalog.h"
#include "billing_catalog.h"
#include "client_catalog.h"
#include "product_catalog.h"
#include "sgv.h"
#include "sale.h"
#include "utils.h"
#include "constants.h"

#include <stdlib.h>
#include <stdio.h>
#include <glib.h>
#include <string.h>

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
char ** productsByLetter(SGV sgv, char letter){
    return getProductsByLetter(sgv->product_catalog, letter);
}

/*
 * [QUERIE 3]
*/
double * productValuesByMonth(SGV sgv, char* product_code, int month, int branches){
    double * result = NULL;
    if(existProductCode (sgv->product_catalog,product_code) && month >= 1 && month <= 12 && (branches == 0 || branches == 1)){
        result = getProductValuesByMonthBillingCat(sgv->billings, product_code, month, branches);
    }
    return result;
}

/*
 * [QUERIE 4] - Determinar a lista ordenada dos códigos dos produtos(e o seu número total)que ninguém  comprou,
                podendo  o  utilizador  decidir  igualmente  se  pretende valores totais ou divididos pelas filiais.
*/
char *** productsNotBought(SGV sgv, int isGlobal){
    int i,branch;
    char *** result;
    char ** _productsBought;
    GHashTable * _htProductsBought;
    if(isGlobal == 0){
        result = g_malloc(sizeof(char***));
        _htProductsBought = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, g_free);
        for (branch = 1; branch <= N_BRANCHES; branch++) {
            _productsBought = getProductsBought(sgv->branches, branch);
            for(i=0;_productsBought[i] != NULL;i++){
                if(!g_hash_table_contains(_htProductsBought, _productsBought[i]))
                    g_hash_table_insert(_htProductsBought, _productsBought[i],_productsBought[i]);
            }
            g_free(_productsBought);
        }
        _productsBought = getProductsNotArray(sgv->product_catalog, _htProductsBought);
        result[ZERO] = _productsBought;
        result[ONE] = NULL;
    }
    else{
        result = g_malloc(sizeof(char***)*N_BRANCHES);
        for(branch = 1; branch <= N_BRANCHES; branch++){
            _htProductsBought = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, g_free);
            _productsBought = getProductsBought(sgv->branches, branch);

            for(i=0;_productsBought[i] != NULL;i++){
                if(!g_hash_table_contains(_htProductsBought, _productsBought[i]))
                    g_hash_table_insert(_htProductsBought, _productsBought[i],_productsBought[i]);
            }
            _productsBought = getProductsNotArray(sgv->product_catalog, _htProductsBought);
            result[branch] = _productsBought;
        }
    }
    /*
    PRINT EXAMPLE
    int j;
    for (j = 0;result[3][j] != NULL; j++) {
        printf("%s\n",result[3][j]);
    }
    printf("%d\n",j);*/
    return result;
}

/* QUERIE 6 */
int * productsClientsNotUsed(SGV sgv){
    int i;
    int branch;
    int products_not_used;
    int clients_not_used;
    char ** _productsBought;
    GHashTable * _htProductsBought;

    char ** _clientsUsed;
    GHashTable * _htClientsUsed;

    _htProductsBought = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, g_free);
    for (branch = 1; branch <= N_BRANCHES; branch++) {
        _productsBought = getProductsBought(sgv->branches, branch);
        for(i = 0; _productsBought[i] != NULL; i++){
            if(!g_hash_table_contains(_htProductsBought, _productsBought[i]))
                g_hash_table_insert(_htProductsBought, _productsBought[i],_productsBought[i]);
        }
        g_free(_productsBought);
    }
    products_not_used = getNumberProductsNotUsed(sgv->product_catalog, _htProductsBought);

    _htClientsUsed = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, g_free);
    for (branch = 1; branch <= N_BRANCHES; branch++) {
        _clientsUsed = getClientsUsed(sgv->branches, branch);
        for(i = 0; _clientsUsed[i] != NULL; i++){
            if(!g_hash_table_contains(_htClientsUsed, _clientsUsed[i]))
                g_hash_table_insert(_htClientsUsed, _clientsUsed[i],_clientsUsed[i]);
        }
        g_free(_clientsUsed);
    }
    clients_not_used = getNumberClientsNotUsed(sgv->client_catalog, _htClientsUsed);

    int * result = g_malloc(sizeof(int));
    result[ZERO] = products_not_used;
    result[ONE] = clients_not_used;
    return result;
}

/* QUERIE 7 */
int ** clientShoppingLog(SGV sgv, char* client_code){
    int ** result = NULL;
    if(existClientCode (sgv->client_catalog,client_code)){
        int branch;
        result = g_malloc(sizeof(int*)*N_BRANCHES);

        for (branch=ONE; branch <= N_BRANCHES; branch++) {
            result[branch-ONE] = clientBranchShopLog(sgv->branches, client_code, branch);
        }
    }
    return result;
}
/* qsort int comparison function */
int int_cmp(const void *a, const void *b)
{
    const int *ia = (const int *)a;
    const int *ib = (const int *)b;
    return *ib - *ia;
	/* integer comparison: returns negative if b > a
	and positive if a > b */
}


/* QUERIE 10 */
Info * clientMostBoughtByMonth(SGV sgv, char* client_code, int month){
    Info * result = NULL;
    if(existClientCode (sgv->client_catalog,client_code) && month >= ZERO && month <= MONTHS){
        result = getMostBought(sgv->branches, client_code, month);
        int i;
        for (i = 0; result[i]!= NULL; i++) {
            Info info = (Info)result[i];
            printf("Product: %s | Units: %d\n", info->product_code, info->unitsSold);
        }
    }
    return result;
}

/* QUERIE 11 */
Aux * nMostBought(SGV sgv, int n_products){
    Aux * result = getNMostBoughtProducts(sgv->branches, n_products);
    /*int k,j;
    for (k = 0; k < n_products; k++) {
        Aux aux = result[k];
        printf("%s\n",(char*)aux->product_code);
        for (j = 0; j < N_BRANCHES; j++) {
            printf("Branch:%d | Total different Clients:%d | UnitsSold:%d\n", (j+1), aux->totalClients[j], aux->unitsSold[j]);
        }
    }*/
    return result;
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
char** query5(SGV sgv)
{
    int *n = g_malloc(sizeof(int));
    char** codes = clientsInCommon(sgv->branches, n);
    g_free(n);
    return codes;
}


/* QUERY 9 */

/* Result[0]: codigos N, Result[1]: codigos P */
/* Sugestao para a view: mostrar ambos os arrays na mesma pagina lado a lado */

/*void query9(SGV sgv)*/
char *** query9(SGV sgv, char *product_code, int branch, int *totalN, int *totalP)
{
    char *** result = NULL;
    if(existProductCode (sgv->product_catalog,product_code) && branch >= 1 && branch <=3)
    {
        *totalN = 0;
        *totalP = 0;
        result = clientsWhoBoughtProduct(sgv->branches, product_code, branch, totalN, totalP);
    }

    /*char ***teste = clientsWhoBoughtProduct(sgv->branches, "AF1184", 1, totalN, totalP);*/
    /*
    int i;

    puts("--------- CODIGOS N: ---------");
    for(i = 0; teste[0][i] && i < *totalN; i++)
    {
        printf("%s\n", teste[0][i]);
    }

    puts("--------- CODIGOS P: ---------");
    for(i = 0; teste[1][i] && i < *totalP; i++)
    {
        printf("%s\n", teste[1][i]);
    }

    puts("--------- TOTAIS: ---------");
    printf("N = %d\nP = %d\n", *totalN, *totalP);
    */

    /*g_free(totalN);
    g_free(totalP);*/

    return result;
}

/* QUERY 8 */
void query8(SGV sgv)
{
    int *totalUnits = g_malloc(sizeof(int));
    int *totalSales = g_malloc(sizeof(int));
    double *totalBilled = g_malloc(sizeof(double));

    int valid = getTotalsFromBillingMonthInterval(sgv->billings, 1, 12, totalUnits, totalBilled, totalSales);
    printf("valid: %d\nUnits: %d\nBilled: %f\nSales: %d\n", valid, *totalUnits, *totalBilled, *totalSales);

    free(totalUnits);
    free(totalBilled);
    free(totalSales);
}

int listSize(char** list) {
    int i = 0;
    for(; list[i] != 0; i++);
    return i;
}

Money * query12(SGV sgv, char *client_code, int n)
{
    Money * result = NULL;
    if (existClientCode (sgv->client_catalog, client_code) && n > 0)
    {
        result = clientSpentMostOn(sgv->branches, client_code, n);

        int k;
        for (k = 0; k < n; k++)
        {
            Money money = result[k];
            printf("product:%s, spent:%f\n",(char*)money->product_code, (double)money->moneySpent);
        }
    }
    return result;
}