#ifndef ___BILLING_CATALOG_H___
#define ___BILLING_CATALOG_H___

#include "billing.h"
#include "sale.h"

typedef struct billings* Billings;

Billings initBillings();

float * getProductValuesByMonthBillingCat(Billings, char*, int, int);

void addBilling(Billings, Billing, int);

void updateBillings(Billings, Sale);

void insertBillingProduct(Billings, int, char*);

void destroyBillings(Billings);

#endif
