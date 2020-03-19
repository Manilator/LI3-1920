#ifndef ___BRANCH_CATALOG_H___
#define ___BRANCH_CATALOG_H___


#include "branch.h"
#include "sale.h"

typedef struct filiais* Filiais;

Filiais initFiliais(int filiais);

void addFilial(Filiais filiais, Filial filial, int number);

void updateFiliais(Filiais filiais, Sale sale);

void freeFiliais(Filiais fs);

#endif