#ifndef ___VIEW_H___
#define ___VIEW_H___

#include "info.h"

void printMenu();

void printSeparator();

void cleanConsole();

void resetColor();

void boldRed();

void viewPrintStartValues(char *clients_path,
                          char *products_path,
                          char *sales_path,
                          int   valid_clients,
                          int   valid_products,
                          int   valid_sales,
                          int   clients_read,
                          int   products_read,
                          int   sales_read);

char askProductLetter();

char *askProduct();

int askMonth();

char* askClient();

int* askMonthInterval();

int askBranch();

int askQuerie3Choice();

int askQuerie4Choice();

int askQuerie11N();

void listView(char **, int);

void tableView(int**, char*);

void querie1View(char*, char*, char*);

void querie2View(char**);

void querie3View(double *, int, char*);

void querie4View(char ***, int, int, int);

void querie5View(char**);

void querie6View(int*);

void querie7View(int**);

void querie8View(Querie8Aux, int, int);

void querie9View(char*** , int *, int*);

void querie10View(Info *, char*);

void querie11View(Aux * , int);

void querie12View(Money *, int);

#endif
