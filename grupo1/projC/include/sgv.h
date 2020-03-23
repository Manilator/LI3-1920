#ifndef ___SGV__H___
#define ___SGV__H___

typedef struct sgv* SGV;

typedef struct startValues* StartValues;

SGV startSGV(StartValues sv);

SGV initSGV();

StartValues initStartValues();

char* getClientsPath(StartValues sv);

char* getProductsPath(StartValues sv);

char* getSalesPath(StartValues sv);

int getValidClients(StartValues sv);

int getValidProducts(StartValues sv);

int getValidSales(StartValues sv);

int getReadClients (StartValues sv);

int getReadProducts (StartValues sv);

int getReadSales (StartValues sv);

void query5_aux(SGV sgv);

#endif
