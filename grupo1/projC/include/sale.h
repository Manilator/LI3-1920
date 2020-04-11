/**
@file sale.h
\brief Módulo de tratamentos de vendas
*/
#ifndef ___SALE_H___
#define ___SALE_H___

#include "product_catalog.h"
#include "client_catalog.h"

typedef struct sale* Sale;

/**
@brief Devolve uma Sale ou NULL consoante a validade da venda
@param sale Código de venda
@param client_catalogue Estrutura Clients
@param product_catalogue Products
@return Sale Estrutura Sale
 */
Sale isValidSale(char*, Clients, Products);

/**
@brief Devolve o código de produto que foi vendido
@param sale Estrutura Sale
@return char* Código de produto
 */
char* getProduct(Sale);

/**
@brief Devolve o código de cliente que efetuou a compra
@param sale Estrutura Sale
@return char* Código de cliente
 */
char* getClient(Sale);

/**
@brief Devolve o valor atribuido ao produto na compra
@param sale Estrutura Sale
@return double Valor atribuido ao produto na compra
 */
double getPrice(Sale);

/**
@brief Devolve o número de unidades compradas/vendidas
@param sale Estrutura Sale
@return int Número de unidades compradas/vendidas
 */
int getUnits(Sale);

/**
@brief Devolve o tipo de promoção da compra
@param sale Estrutura Sale
@return char Tipo de promoção da compra N ou P
 */
char getPromotion(Sale);

/**
@brief Devolve o número do mês da compra
@param sale Estrutura Sale
@return int Número do mês da compra
 */
int getMonth(Sale);

/**
@brief Devolve o número da filial
@param sale Estrutura Sale
@return int Número da filial
 */
int getBranch(Sale);

/**
@brief Libertar memória na estrutura Sale
@param sale Estrutura Sale
 */
void destroySale(Sale);

#endif
