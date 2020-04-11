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
@brief Adiciona um produto ao catálogo de produto
@param products Catálogo de produtos ao qual vai ser adicionado o novo produto
@param product Cliente a ser adicionado ao catálogo de produtos
@return int Verificação da inserção
*/
int addProduct(Products, char*);

/**
@brief Calcula o número de produtos que existe no catálogo
@param products Catálogo de produtos
@return int Número de produtos existentes no catálogo
*/
int getSizeProducts(Products);

/**
@brief Verifica se existe um produto no catálogo
@param products Catálogo de produtos
@param product Cliente a ser consultado
@return int Verificação da procura
*/
int existProduct (Products, Product);

/**
@brief Destroi o catálogo de produtos
@param products Catálogo de produtos
*/
void destroyProducts(Products);

/**
@brief Devolve os códigos de produtos que não foram comprados
@param product_catalog Catálogo de produtos
@param products_bought Hashtable com códigos de produto
@return char** Array com códigos de produtos 
*/
char ** getProductsNotArray(Products, GHashTable*);

/**
@brief Devolve número de código de produtos não utilizados
@param product_catalog Catálogo de produtos
@param products_bought Hashtable com códigos de produto
@return int Número de código de produtos não utilizados
*/
int getNumberProductsNotUsed(Products, GHashTable *);

/**
@brief Verifica se existe um código de produto no catálogo
@param products Catálogo de produtos
@param product_code Código de produto
@return int Verificação da procura
*/
int existProductCode (Products, char*);

#endif
