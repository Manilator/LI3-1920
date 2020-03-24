#ifndef ___BILLING_H___
#define ___BILLING_H___

typedef struct billing* Billing;

typedef struct billingProduct* BillingProduct;

Billing initBilling();

BillingProduct initBillingProduct();

int addBillingProduct(Billing, char*);

void updateBilling(Billing, char*, float, int, char, int);

int updateBillingProduct(BillingProduct , float, int, char, int);

BillingProduct getBillingProduct(Billing, char*);

float getTotalBilledBilling(Billing);

float getTotalBilledN_BP(BillingProduct);

char* getFirstKey(Billing);

void freeBillingProduct(BillingProduct);

void freeBilling(Billing);

#endif
