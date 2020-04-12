#include "branch_catalog.h"
#include "billing_catalog.h"
#include "sgv.h"
#include "sale.h"
#include "utils.h"
#include "constants.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct sgv{
    Clients client_catalog; /**< Cátalogo de clientes */
    Products product_catalog; /**< Cátalogo de produto */
    Billings billings; /**< Cátalogo de faturação */
    Branches branches; /**< Cátalogo de filiais */
};

struct startValues{
    GString * path_clients; /**< Path de ficheiro de clientes */
    GString * path_products; /**< Path de ficheiro de clientes */
    GString * path_sales; /**< Path de ficheiro de clientes */
    gint valid_clients; /**< Número de clientes válidos */
    gint read_clients; /**< Número de clientes lidos */
    gint valid_products; /**< Número de produtos válidos */
    gint read_products; /**< Número de produtos lidos */
    gint valid_sales; /**< Número de vendas válidas */
    gint read_sales; /**< Número de vendas lidas */
};

StartValues initStartValues(){
    StartValues startValues = g_malloc(sizeof(struct startValues));

    startValues->path_clients = NULL;
    startValues->path_products = NULL;
    startValues->path_sales = NULL;
    startValues->valid_clients = 0;
    startValues->read_clients = 0;
    startValues->valid_products = 0;
    startValues->read_products = 0;
    startValues->valid_sales = 0;
    startValues->read_sales = 0;
    return startValues;
}

void setPathsSV(StartValues startValues, char * clients_path, char * products_path, char * sales_path){
    startValues->path_clients = g_string_new(clients_path);
    startValues->path_products = g_string_new(products_path);
    startValues->path_sales = g_string_new(sales_path);
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
    char * _fileline = g_malloc(sizeof(char)*1024); /*Variável onde é guardada cada linha lida*/
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
    char * _fileline = g_malloc(sizeof(char)*1024); /*Variável onde é guardada cada linha lida*/
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
    char * _fileline = g_malloc(sizeof(char)*1024); /*Variável onde é guardada cada linha lida*/
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
    if(sv->path_clients != NULL)
        g_string_free(sv->path_clients,TRUE);
    if(sv->path_products != NULL)
        g_string_free(sv->path_products,TRUE);
    if(sv->path_sales != NULL)
        g_string_free(sv->path_sales,TRUE);
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
 * [QUERY 2] - Returns all of the product codes started by "letter"
*/
char ** getProductsStartedByLetter(SGV sgv, char letter){
    return getProductsByLetter(sgv->product_catalog, letter);
}

/*
 * [QUERY 3]
*/
double * getProductSalesAndProfit(SGV sgv, char * product_code, int month, int branches){
    double * result = NULL;
    if(existProductCode (sgv->product_catalog,product_code) && month >= 1 && month <= 12 && (branches == 0 || branches == 1)){
        result = getProductValuesByMonthBillingCat(sgv->billings, product_code, month, branches);
    }
    return result;
}

/*
 * [QUERY 4] - Determinar a lista ordenada dos códigos dos produtos(e o seu número total)que ninguém  comprou,
                podendo  o  utilizador  decidir  igualmente  se  pretende valores totais ou divididos pelas filiais.
*/
char *** getProductsNeverBought(SGV sgv, int isGlobal){
    int i,branch;
    char *** result;
    char ** _productsBought;
    GHashTable * _htProductsBought;
    if(isGlobal == 0){
        result = g_malloc(sizeof(char **)*2);
        _htProductsBought = g_hash_table_new(g_str_hash, g_str_equal);
        for (branch = 1; branch <= N_BRANCHES; branch++) {

            _productsBought = getProductsBought(sgv->branches, branch);

            for(i=0;_productsBought[i] != NULL;i++){
                if(!g_hash_table_contains(_htProductsBought, _productsBought[i]))
                    g_hash_table_insert(_htProductsBought,_productsBought[i],_productsBought[i]);
            }

            g_free(_productsBought);
        }
        result[ZERO] = getProductsNotArray(sgv->product_catalog, _htProductsBought);
        result[ONE] = NULL;
        g_hash_table_destroy(_htProductsBought);
    }
    else{
        int j=0;
        result = g_malloc(sizeof(char **)*(N_BRANCHES+1));
        for(branch = 1; branch <= N_BRANCHES; branch++){
            _htProductsBought = g_hash_table_new(g_str_hash, g_str_equal);
            _productsBought = getProductsBought(sgv->branches, branch);
            for(i=0;_productsBought[i] != NULL;i++){
                if(!g_hash_table_contains(_htProductsBought, _productsBought[i]))
                    g_hash_table_insert(_htProductsBought, _productsBought[i],_productsBought[i]);
            }
            result[j++] = getProductsNotArray(sgv->product_catalog, _htProductsBought);
            g_hash_table_destroy(_htProductsBought);
            g_free(_productsBought);
        }
        result[j] = NULL;
    }
    return result;
}

/* [QUERY 5] */
char ** getClientsOfAllBranches(SGV sgv){
    char ** codes = clientsInCommon(sgv->branches, sgv->client_catalog);
    return codes;
}

/* [QUERY 6] */
int * getClientsAndProductsNeverBoughtCount(SGV sgv){
    int i;
    int branch;
    int products_not_used;
    int clients_not_used;
    char ** _productsBought;
    GHashTable * _htProductsBought;

    char ** _clientsUsed;
    GHashTable * _htClientsUsed;

    _htProductsBought = g_hash_table_new(g_str_hash, g_str_equal);
    for (branch = 1; branch <= N_BRANCHES; branch++) {
        _productsBought = getProductsBought(sgv->branches, branch);
        for(i = 0; _productsBought[i] != NULL; i++){
            if(!g_hash_table_contains(_htProductsBought, _productsBought[i]))
                g_hash_table_insert(_htProductsBought, _productsBought[i],_productsBought[i]);
        }
        g_free(_productsBought);
    }
    products_not_used = getNumberProductsNotUsed(sgv->product_catalog, _htProductsBought);

    _htClientsUsed = g_hash_table_new(g_str_hash, g_str_equal);
    for (branch = 1; branch <= N_BRANCHES; branch++) {
        _clientsUsed = getClientsUsed(sgv->branches, branch);
        for(i = 0; _clientsUsed[i] != NULL; i++){
            if(!g_hash_table_contains(_htClientsUsed, _clientsUsed[i]))
                g_hash_table_insert(_htClientsUsed, _clientsUsed[i],_clientsUsed[i]);
        }
        g_free(_clientsUsed);
    }
    clients_not_used = getNumberClientsNotUsed(sgv->client_catalog, _htClientsUsed);
    g_hash_table_destroy(_htProductsBought);
    g_hash_table_destroy(_htClientsUsed);
    int * result = g_malloc(sizeof(int)*2);
    result[ZERO] = products_not_used;
    result[ONE] = clients_not_used;
    return result;
}

/* QUERY 7 */
int ** getProductsBoughtByClient(SGV sgv, char * client_code){
    int ** result = NULL;
    if(existClientCode (sgv->client_catalog,client_code)){
        int branch;
        result = g_malloc(sizeof(int*)*(N_BRANCHES+1));

        for (branch=ONE; branch <= N_BRANCHES; branch++) {
            result[branch-ONE] = clientBranchShopLog(sgv->branches, client_code, branch);
        }
        result[branch-ONE] = NULL;
    }
    return result;
}

/* [QUERY 8] */
Query8Aux getSalesAndProfit(SGV sgv, int monthI, int monthF)
{
    if(monthI > 0 && monthF < 13 && monthF >= monthI)
        return getTotalsFromBillingMonthInterval(sgv->billings, monthI, monthF);
    else
        return NULL;
}

/* [QUERY 9] */
Query9Aux getProductBuyers(SGV sgv, char *product_code, int branch)
{
    Query9Aux result = NULL;
    if(existProductCode (sgv->product_catalog,product_code) && branch >= 1 && branch <= N_BRANCHES)
    {
        result = clientsWhoBoughtProduct(sgv->branches, product_code, branch);
    }
    return result;
}

/* [QUERY 10] */
Info * getClientsFavoriteProducts(SGV sgv, char * client_code, int month){
    Info * result = NULL;
    if(existClientCode (sgv->client_catalog,client_code) && month >= ZERO && month <= MONTHS){
        result = getMostBought(sgv->branches, client_code, month);
    }
    return result;
}

/* [QUERY 11] */
Aux * getTopSoldProducts(SGV sgv, int n_products){
    return getNMostBoughtProducts(sgv->branches, n_products);
}

/* [QUERY 12] */
Money * getClientTopProfitProducts(SGV sgv, char *client_code, int n)
{
    Money * result = NULL;
    if (existClientCode (sgv->client_catalog, client_code) && n > 0)
    {
        result = clientSpentMostOn(sgv->branches, client_code, n);
    }
    return result;
}

char * getClientsPath(StartValues sv) {
    return (sv->path_clients)->str;
}

char * getProductsPath(StartValues sv) {
    return (sv->path_products)->str;
}

char * getSalesPath(StartValues sv) {
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


int listSize(char ** list) {
    int i = 0;
    for(; list[i] != 0; i++);
    return i;
}


void freeStringList(char ** list){
    int i = 0;
    while(list[i] != NULL){
        g_free(list[i++]);
    }
    g_free(list);
}

void freeStringMatrix(char *** matrix){
    int i = 0;
    while(matrix[i] != NULL){
        g_free(matrix[i++]);
    }
    g_free(matrix);
}

void freeIntMatrix(int ** matrix){
    int i = 0;
    while(matrix[i] != NULL){
        g_free(matrix[i++]);
    }
    g_free(matrix);
}
