/**
@file product_catalog.h
\brief Módulo de tratamentos do catálogo de produtos
*/

#ifndef ___PRODUCT_CATALOG_H___
#define ___PRODUCT_CATALOG_H___

#include "product.h"
#include <glib.h>

typedef struct products* Products;

/**
@brief Inicia a estrutura de catálogo de produtos
@return Products estrutura inicializada
*/
Products initProducts();

/**
@brief Recolhe todos os produtos que comecem por uma certa letra
@param products_catalog Catálogo de produtos
@param letter Letra pelo qual os produtos começam
@return char** Array com todos os códigos de produtos começados pela letra dada
*/
char ** getProductsByLetter(Products, char);

/**
@brief 
@param 
@return 
*/
int addProduct(Products, char*);

/**
@brief 
@param 
@return 
*/
int getSizeProducts(Products);

/**
@brief 
@param 
@return 
*/
int existProduct (Products, Product);

/**
@brief 
@param 
@return 
*/
void destroyProducts(Products);

/**
@brief 
@param 
@return 
*/
char ** getProductsNotArray(Products, GHashTable*);

/**
@brief 
@param 
@return 
*/
int getNumberProductsNotUsed(Products, GHashTable *);

/**
@brief 
@param 
@return 
*/
int existProductCode (Products, char*);

#endif
