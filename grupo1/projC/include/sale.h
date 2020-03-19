#ifndef ___SALE_H___
#define ___SALE_H___

#include "product_catalog.h"
#include "client_catalog.h"

typedef struct sale* Sale;

Sale isValidSale(char*, Clients, Products);

char* getProduct(Sale);

char* getClient(Sale);

double getPrice(Sale);

int getUnits(Sale);

char getPromotion(Sale);

int getMonth(Sale);

int getBranch(Sale);

void destroySale(Sale);

#endif
