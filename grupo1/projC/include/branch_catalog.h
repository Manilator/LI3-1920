#ifndef ___BRANCH_CATALOG_H___
#define ___BRANCH_CATALOG_H___


#include "branch.h"
#include "sale.h"

typedef struct branches* Branches;

Branches initBranches(int);

void addBranch(Branches, Branch, int);

void updateBranches(Branches, Sale);

void destroyBranches(Branches);

/*Branch getBranchByNumber(Branches, int*);*/

char** query5(Branches, int*);

char** teste(int*);

char** intersect(char**, char**, char**, int, int, int, int*);

void printBranch1(Branches);

void printClientsBranch(Branches, int*);

#endif
