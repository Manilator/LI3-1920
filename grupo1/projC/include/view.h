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

void listView(char **list, int size);

void tableView(int** list, char* client);

void querie1View(char* clients_path, char* products_path, char* sales_path);

void querie2View(char**);

void querie3View(double * products, int choice, char* product);

void querie4View(char ***products, int choice, int branch, int size);

void querie5View(char** clients);

void querie6View(int* list);

void querie7View(int** totals);

void querie8View(int totalUnits, int totalSales, double totalBilled, int first, int second);

void querie9View(char*** array, int *total_N, int* total_P);

void querie10View(Info *info, char* client);

void querie11View(Aux * result, int n);

void querie12View(Money *result, int n);

#endif
