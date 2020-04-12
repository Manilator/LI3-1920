/**
@file billing_catalog.h
\brief Módulo de tratamentos do catálogo de faturação
*/
#ifndef ___BILLING_CATALOG_H___
#define ___BILLING_CATALOG_H___

#include "billing.h"
#include "sale.h"

typedef struct billings* Billings;

/**
@brief Inicialização da estrutura BillingProduct.
@return Billings um BillingProduct inicializado.
*/
Billings initBillings();

/**
@brief Devolve um array de valores
@param bs
@param product_code Código de produto
@param month Número do mês
@param isGlobal Número usado para representar se é uma buscar global ou por filial
@return double* devolve um BillingProduct inicializado.
*/
double * getProductValuesByMonthBillingCat(Billings, char*, int, int);

/**
@brief Adiciona uma estrutura Billing á hashtable da estrutura Billings num certo mês
@param billings Estrutura Billings
@param billing Estrutura Billing
@param month Número do mês
*/
void addBilling(Billings, Billing, int);

/**
@brief Atualização dos valores da estrutura Billings
@param bs Estrutura Billings
@param sale Estrutura Sale
*/
void updateBillings(Billings, Sale);

/**
@brief Insere uma estrutura BillingProduct dentro de uma estrutura Billing
@param bs Estrutura Billings
@param month Número do mês
@param product_code Código de produto
*/
void insertBillingProduct(Billings, int, char*);

/**
@brief Liberta memória da estrutura Billings dada
@param bs Estrutura Billings
*/
void destroyBillings(Billings);

/**
@brief Devolve uma estrutura auxiliar Query8Aux com os valores de entre dois meses dados
@param monthI Número de um mês
@param monthF Número de um mês posterior ou igual a monthI
@return Query8Aux Uma estrutura Query8Aux
*/
Query8Aux getTotalsFromBillingMonthInterval(Billings, int, int);

#endif
