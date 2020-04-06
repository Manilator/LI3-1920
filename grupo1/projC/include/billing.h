#ifndef ___BILLING_H___
#define ___BILLING_H___

typedef struct billing* Billing;

typedef struct billingProduct* BillingProduct;

Billing initBilling();

BillingProduct initBillingProduct();

double * getProductValuesByMonthBilling(Billing, char*, int);

int addBillingProduct(Billing, char*);

void updateBilling(Billing, char*, double, int, char, int);

int updateBillingProduct(BillingProduct , double, int, char, int);

BillingProduct getBillingProduct(Billing, char*);

double getTotalBilledBilling(Billing);

double getTotalBilledN_BP(BillingProduct);

char* getFirstKey(Billing);

void freeBillingProduct(BillingProduct);

void freeBilling(Billing);

void getTotalsFromBilling(Billing, int*, double*, int*);

#endif
