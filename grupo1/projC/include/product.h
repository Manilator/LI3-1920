/**
@file product.h
\brief Módulo de tratamentos de produto
*/
#ifndef ___PRODUCT_H___
#define ___PRODUCT_H___


#include <stdbool.h>

typedef struct product* Product;

/**
@brief Devolve um bool consoante o código de produto ser válido ou não
@param product Código de produto
@return bool Resultado da verificação
 */
bool verifyProduct(char*);

/**
@brief Devolve um estrutura Product inicializada com um código de produto
@param product Código de produto
@return Product Estrutura Product
 */
Product newProduct(char*);

/**
@brief Devolve o código de produto presente na estrutura product
@param Estrutura Product
@return char* Código de produto
 */
char* getProductCode(Product);

/**
@brief Verifica a igualdade entre duas estruturas Product dadas
@param a Estrutura Product
@param b Estrutura Product
@return int Número 0 ou 1
 */
int equalsProduct(Product, Product);

/**
@brief Libertar a memória na estrutura Product dada
@param product Estrutura Product
 */
void destroyProduct(Product);

#endif
