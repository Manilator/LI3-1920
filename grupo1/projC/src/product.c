#include "product.h"

#include <stdlib.h>
#include <stdio.h>

struct product
{
    char first_letter; /**< Primeira letra no código de produto */
    char second_letter; /**< Segunda letra no código de produto */
    int number; /**< Número presente no código de produto */
};

char* getProductCode(Product product) {
    char* code = malloc(sizeof(char)*8);
    sprintf(code, "%c%c%d",product->first_letter,product->second_letter,product->number);
    return code;
}

bool verifyProduct(char *product) {
    int number = atoi(product+2);
    char first_letter = product[0];
    char second_letter = product[1];
    if( (number >= 1000 && number <= 9999) &&
            (first_letter >= 'A' && first_letter <= 'Z') &&
                (second_letter >= 'A' && second_letter <= 'Z')) {
                    return true;
                }
    return false;
}

Product newProduct(char* product) {
    Product new = malloc(sizeof(struct product));
    new->first_letter = product[0];
    new->second_letter = product[1];
    new->number = atoi(product+2);
    return new;
}

int equalsProduct(Product a, Product b) {
    return (a->first_letter == b->first_letter &&
            a->second_letter == b->second_letter &&
            a->number == b->number);
}

void destroyProduct(Product product) {
    free(product);
}
