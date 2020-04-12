#include "sale.h"

#include <string.h>
#include <stdlib.h>

#include <stdio.h>

struct sale
{
    char *  product; /**< Código de produto */
    char *  client; /**< Código de cliente */
    double  price; /**< Preço do produto */
    int     units; /**< Número de unidades vendidas */
    char    promotion; /**< Tipo de promoção N ou P */
    int     month; /**< Número do mês */
    int     branch; /**< Número da filial */
};


Sale isValidSale(char* sale, Clients client_catalogue, Products product_catalogue) {
    Sale new = malloc(sizeof(struct sale));
    char* _temp = strdup(sale);
    char* _fields[100];
    char *_token;
    const char s[2] = " ";
    int i = 0;


    _token = strtok(_temp, s);

    while (_token != NULL) {
        _fields[i] = _token;
        ++i;
        _token = strtok(NULL,s);
    }
    new->product = strdup(_fields[0]);
    new->client  = strdup(_fields[4]);
    new->price      = atof( _fields[1]);
    new->units      = atoi( _fields[2]);
    new->promotion  =       _fields[3][0];
    new->month      = atoi( _fields[5]);
    new->branch     = atoi( _fields[6]);
    free(_temp);
    free(_token);

    if (verifyClient(new->client)                           &&
        verifyProduct(new->product)                         &&
        (new->price <= 999.99    && new->price >= 0)               &&
        (new->units <= 200       && new->units >= 0)                  &&
        (new->promotion == 'N'   || new->promotion == 'P')    &&
        (new->month < 13         && new->month > 0)                   &&
        (new->branch < 4         && new->branch > 0))                 {

        Client _client = newClient(new->client);
        Product _product = newProduct(new->product);

            if ( existClient(client_catalogue, _client) && existProduct(product_catalogue, _product))
            {
                destroyClient(_client);
                destroyProduct(_product);
                return new ;
            }

        destroyClient(_client);
        destroyProduct(_product);
        }
    destroySale(new);
    return NULL;
}

char* getProduct(Sale sale) {
    return sale->product;
}

char* getClient(Sale sale) {
    return sale->client;
}

double getPrice(Sale sale) {
    return sale->price;
}

int getUnits(Sale sale) {
    return sale->units;
}

char getPromotion(Sale sale) {
    return sale->promotion;
}

int getMonth(Sale sale) {
    return sale->month;
}

int getBranch(Sale sale) {
    return sale->branch;
}


void destroySale(Sale sale) {
    free(sale->product);
    free(sale->client);
    free(sale);
}
