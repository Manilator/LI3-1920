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

char askQuerie2Letter();

void querie2View(char**);

void querie1View(char* clients_path, char* products_path, char* sales_path);

char* askQuerie3Product();

int askQuerie3Month();

int askQuerie3Choice();

void querie3View(float * products, int choice);

int askQuerie4Choice();

char* askQuerie7Client();

int* askQuerie8Interval();

char *askQuerie9Product();

int askQuerie9Branch();

char* askQuerie10Client();

int askQuerie10Month();

char* askQuerie12Client();

void querie4View(char ***products, int choice);

void querie5View(char** clients);

void querie6View(int* list);

#endif
