#ifndef ___BRANCH_CATALOG_H___
#define ___BRANCH_CATALOG_H___


#include "branch.h"
#include "sale.h"

typedef struct branches* Branches;

Branches initBranches(int);

void addBranch(Branches, Branch, int);

void updateBranches(Branches, Sale);

void destroyBranches(Branches);

char** intersect(char**, char**, char**, int, int, int, int*);

char ** clientsInCommon(Branches, Clients);

char ** getProductsBought(Branches, int);

Querie9Aux clientsWhoBoughtProduct(Branches, char*, int);

char ** getClientsUsed(Branches, int);

int * clientBranchShopLog(Branches, char*, int);

Info * getMostBought(Branches, char*, int);

Aux * getNMostBoughtProducts(Branches, int);

Money * clientSpentMostOn(Branches, char*, int);

#endif
