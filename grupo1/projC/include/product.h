#ifndef ___PRODUCT_H___
#define ___PRODUCT_H___


#include <stdbool.h>

typedef struct product* Product;

bool verifyProduct(char*);

Product newProduct(char*);

char* getProductCode(Product);

int equalsProduct(Product, Product);

void destroyProduct(Product);

#endif
