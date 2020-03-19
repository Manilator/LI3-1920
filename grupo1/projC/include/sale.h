#ifndef ___SALE_H___
#define ___SALE_H___

#include "product_catalog.h"
#include "client_catalog.h"

typedef struct sale* Sale;

Sale isValidSale(char* sale, Clients client_catalogue, Products product_catalogue);

char* getProduct(Sale sale);

char* getClient(Sale sale);

double getPrice(Sale sale);

int getUnits(Sale sale);

char getPromotion(Sale sale);

int getMonth(Sale sale);

int getBranch(Sale sale);

void destroySale(Sale sale);

#endif