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

void querie1View(char* clients_path, char* products_path, char* sales_path);

#endif
