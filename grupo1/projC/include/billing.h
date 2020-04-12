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
@brief Adiciona a estrutura BillingProduct á hashtable billingsProduct
@param billing Estrutura Billing
@param code Código de produto
@return int Resultado binário para detetar erros
*/
int addBillingProduct(Billing, char*);

/**
@brief Atualiza os valores da estrutura Billing
@param billing Estrutura Billing
@param code Código de produto
@param totalBilled Valor faturado
@param unities Unidades vendidas
@param promotion_type Tipo de promoção
@param branch Filial
*/
void updateBilling(Billing, char*, double, int, char, int);

/**
@brief Atualiza os valores da estrutura BillingProduct.
@param billingProduct Estrutura BillingProduct
@param totalBilled Valor faturado
@param unities Unidades vendidas
@param promotion_type Tipo de promoção
@param branch Filial
@return int Resultado binário para detetar erros
*/
int updateBillingProduct(BillingProduct , double, int, char, int);

/**
@brief Devolve BillingProduct de um certo código de produto
@param billing Estrutura Billing
@param product_code Código de produto
@return BillingProduct Estrutura BillingProduct
*/
BillingProduct getBillingProduct(Billing, char*);

/**
@brief Devolve o total faturado no total
@param billing Estrutura Billing
@return double Valor faturado
*/
double getTotalBilledBilling(Billing);

/**
@brief Devolve o valor faturado com o Tipo P
@param billingProduct Estrutura BillingProduct
@return double Valor faturado
*/
double getTotalBilledN_BP(BillingProduct);

/**
@brief Devolve um código de produto
@param billing Estrutura Billing
@return char* Código de produto
*/
char* getFirstKey(Billing);

/**
@brief Atualiza a estrutura Query8Aux com os valores de unidades de todas as filiais
@param billing Estrutura Billing
@param aux Estrutura Query8Aux
*/
void updateTotalsFromBilling(Billing, Query8Aux);

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
