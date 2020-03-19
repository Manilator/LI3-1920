#ifndef ___BILLING_CATALOG_H___
#define ___BILLING_CATALOG_H___

#include "billing.h"
#include "sale.h"

typedef struct faturas* Faturas;

Faturas initFaturas();

void addFatura(Faturas faturas, Fatura fatura, int month);

void updateFaturas(Faturas fs, Sale sale);

Fatura getFatura(Faturas f, int month);

void freeFaturas(Faturas f);

#endif
