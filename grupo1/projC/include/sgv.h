#ifndef ___SGV__H___
#define ___SGV__H___

#include <glib.h>

typedef struct sgv* SGV;

typedef struct startValues* StartValues;

SGV startSGV(StartValues sv);

SGV initSGV();

StartValues initStartValues(char* clients_path, char* products_path, char* sales_path);

GSList * productsByLetter(SGV, char);

void productValuesByMonth(SGV, char* , int, int);

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
