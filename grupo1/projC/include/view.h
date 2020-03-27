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

#endif
