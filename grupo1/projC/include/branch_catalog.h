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

char** clientsInCommon(Branches, int*);

char ** getProductsBought(Branches, int);

void printBranch1(Branches bs);

#endif
