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
@brief Inicialização da estrutura BillingProduct.
@param
@return double* devolve um BillingProduct inicializado.
*/
double * getProductValuesByMonthBillingCat(Billings, char*, int, int);

/**
@brief Inicialização da estrutura BillingProduct.
@param
@param
@param
*/
void addBilling(Billings, Billing, int);

/**
@brief Inicialização da estrutura BillingProduct.
@param
@param
*/
void updateBillings(Billings, Sale);

/**
@brief Inicialização da estrutura BillingProduct.
@param
@param
@param
*/
void insertBillingProduct(Billings, int, char*);

/**
@brief Inicialização da estrutura BillingProduct.
@param
*/
void destroyBillings(Billings);

/**
@brief Inicialização da estrutura BillingProduct.
@param
@param
@param
@return Devolve um BillingProduct inicializado.
*/
Querie8Aux getTotalsFromBillingMonthInterval(Billings, int, int);

#endif
