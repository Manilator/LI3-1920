#ifndef ___PRODUCT_CATALOG_H___
#define ___PRODUCT_CATALOG_H___

#include "product.h"
#include <glib.h>

typedef struct products* Products;

Products initProducts();

char ** getProductsByLetter(Products, char);

int addProduct(Products, char*);

int getSizeProducts(Products);

int existProduct (Products, Product);

void destroyProducts(Products);

char ** getProductsNotArray(Products, GHashTable*);

int getNumberProductsNotUsed(Products, GHashTable *);

#endif
