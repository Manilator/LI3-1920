#ifndef ___BILLING_CATALOG_H___
#define ___BILLING_CATALOG_H___

#include "billing.h"
#include "sale.h"

typedef struct billings* Billings;

Billings initBillings();

void addBilling(Billings, Billing, int);

void updateBillings(Billings, Sale);

Billing getBilling(Billings, int);

void destroyBillings(Billings);

#endif
