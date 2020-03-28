#ifndef ___SGV__H___
#define ___SGV__H___

#include <glib.h>

typedef struct sgv* SGV;

typedef struct startValues* StartValues;

SGV startSGV(SGV, StartValues);

SGV initSGV();

StartValues initStartValues(char* clients_path, char* products_path, char* sales_path);

char ** productsByLetter(SGV, char);

float * productValuesByMonth(SGV, char* , int, int);

char *** productsNotBought(SGV, int);

char* getClientsPath(StartValues);

char* getProductsPath(StartValues);

char* getSalesPath(StartValues);

int getValidClients(StartValues);

int getValidProducts(StartValues);

int getValidSales(StartValues);

int getReadClients (StartValues);

int getReadProducts (StartValues);

int getReadSales (StartValues);

char** query5(SGV sgv);

#endif
