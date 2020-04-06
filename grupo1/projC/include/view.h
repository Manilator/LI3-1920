#ifndef ___VIEW_H___
#define ___VIEW_H___

void printMenu();

void printSeparator();

void cleanConsole();

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

void querie1View(char* clients_path, char* products_path, char* sales_path);

void querie2View(char**);

void querie3View(float * products, int choice);

void querie4View(char ***products, int choice);

void querie5View(char** clients);

void querie6View(int* list);

#endif
