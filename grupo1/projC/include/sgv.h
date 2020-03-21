#ifndef ___SGV__H___
#define ___SGV__H___

#include <glib.h>

typedef struct sgv* SGV;

typedef struct startValues* StartValues;

SGV startSGV(StartValues sv);

SGV initSGV();

StartValues initStartValues();

GSList * productsByLetter(SGV, char);

char* getClientsPath(StartValues);

char* getProductsPath(StartValues);

char* getSalesPath(StartValues);

int getValidClients(StartValues);

int getValidProducts(StartValues);

int getValidSales(StartValues);

int getReadClients (StartValues);

int getReadProducts (StartValues);

int getReadSales (StartValues);

#endif
