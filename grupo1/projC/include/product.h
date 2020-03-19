#ifndef ___PRODUCT_H___
#define ___PRODUCT_H___


#include <stdbool.h>

typedef struct product* Product;

bool verifyProduct(char *product);

Product newProduct(char* product);

char* getProductCode(Product product);

int equalsProduct(Product a, Product b);

void destroyProduct(Product product);

#endif