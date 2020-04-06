#ifndef ___BRANCH_H___
#define ___BRANCH_H___


typedef struct branch* Branch;

typedef struct relationWithClient* RelationWithClient;

typedef struct relationWithProduct* RelationWithProduct;

typedef struct infoClient* InfoClient;

typedef struct infoProduct* InfoProduct;

Branch initBranch();

RelationWithClient initRelationWithClient();

RelationWithProduct initRelationWithProduct();

InfoClient initInfoClient();

InfoProduct initInfoProduct();

void addRelationWithClient(Branch, char*, RelationWithClient);

void addRelationWithProduct(Branch, char*, RelationWithProduct);

void addInfoClient(RelationWithClient, char*, InfoClient);

void addInfoProduct(RelationWithProduct, char*, InfoProduct);

void updateBranch(Branch, char*, char*, int, char, double, int);

void updateRelationWithProduct(RelationWithProduct, char*, int, double, int);

void updateRelationWithClient(RelationWithClient, char*, int, char);

void updateInfoClient(InfoClient, int, char);

void updateInfoProduct(InfoProduct, int, double, int);

void freeBranch(Branch);

void freeRelationWithClient(RelationWithClient);

void freeRelationWithProduct(RelationWithProduct);

void freeInfoClient(InfoClient);

void freeInfoProduct(InfoProduct);

char** getClientCodes(Branch, int*);

char ** getProductsInBranch(Branch);

char *** productBoughtBy(Branch, char*, int*, int*);

char ** getClientsInBranch(Branch);

int * getClientShopLog(Branch, char*);

#endif
