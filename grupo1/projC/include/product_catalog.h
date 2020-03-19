#ifndef ___PRODUCT_CATALOG_H___
#define ___PRODUCT_CATALOG_H___

#include "product.h"

typedef struct products* Products;

Products initProducts();

int addProduct(Products products,char* product);

int getSizeProducts(Products products);

int existProduct (Products products, Product product);

void destroyProducts(Products products);

#endif
