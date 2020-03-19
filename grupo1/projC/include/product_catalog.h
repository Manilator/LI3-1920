#ifndef ___PRODUCT_CATALOG_H___
#define ___PRODUCT_CATALOG_H___

#include "product.h"

typedef struct products* Products;

Products initProducts();

int addProduct(Products, char*);

int getSizeProducts(Products);

int existProduct (Products, Product);

void destroyProducts(Products);

#endif
