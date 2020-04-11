/**
@file billing.h
\brief Módulo de tratamento de faturas.
*/
#ifndef ___BILLING_H___
#define ___BILLING_H___

#include "info.h"

typedef struct billing* Billing;

typedef struct billingProduct* BillingProduct;

/**
@brief Inicialização da estrutura Billing.
@return Billing devolve um Billing inicializado.
*/
Billing initBilling();

/**
@brief Inicialização da estrutura BillingProduct.
@return BillingProduct devolve um BillingProduct inicializado.
*/
BillingProduct initBillingProduct();

/**
@brief De um array de inteiros, mostra ao utilizador o conteúdo numa tabela
@param billing estrutura Billing
@param product_code Código do produto ao qual as faturas estão relacionadas
@param branch numero da filial escolhida
@return double* devolve uma lista de valores com quantidades e faturação numa dada filial
 */
double * getProductValuesByMonthBilling(Billing, char*, int);

/**
@brief
@param billing
@param code
@return int
*/
int addBillingProduct(Billing, char*);

/**
@brief
@param billing
@param code
@param totalBilled
@param unities
@param promotion_type
@param branch
*/
void updateBilling(Billing, char*, double, int, char, int);

/**
@brief Inicialização da estrutura BillingProduct.
@param billingProduct
@param totalBilled
@param unities
@param promotion_type
@param branch
@return int
*/
int updateBillingProduct(BillingProduct , double, int, char, int);

/**
@brief
@param billing
@param product_code
@return BillingProduct devolve um BillingProduct de um certo código de produto.
*/
BillingProduct getBillingProduct(Billing, char*);

/**
@brief
@param billing
@return double
*/
double getTotalBilledBilling(Billing);

/**
@brief
@param billingProduct estrutura BillingProduct
@return double
*/
double getTotalBilledN_BP(BillingProduct);

/**
@brief
@param billing
@return char*
*/
char* getFirstKey(Billing);

/**
@brief
@param billing
@param aux
*/
void updateTotalsFromBilling(Billing, Querie8Aux);

/**
@brief Libertação da estrutura BillingProduct.
@param billingProduct estrutura BillingProduct.
*/
void freeBillingProduct(BillingProduct);

/**
@brief Libertação da estrutura Billing.
@param billing estrutura Billing.
*/
void freeBilling(Billing);

#endif
