#include "controller.h"
#include "view.h"
#include "sgv.h"


#include <stdio.h>

void menu(SGV sgv)
{
    char querie;
    char clients_path[1024];
    char products_path[1024];
    char sales_path[1024];
    StartValues sv;
    cleanConsole();
    while (querie != '0')
    {
        printMenu();
        scanf(" %c", &querie);
        switch (querie)
        {
        case '1' :
            querie1View(clients_path, products_path, sales_path);
            sv = initStartValues(clients_path, products_path, sales_path);
            sgv = startSGV(sv);
            cleanConsole();
            viewPrintStartValues(getClientsPath(sv),
                                 getProductsPath(sv),
                                 getSalesPath(sv),
                                 getValidClients(sv),
                                 getValidProducts(sv),
                                 getValidSales(sv),
                                 getReadClients(sv),
                                 getReadProducts(sv),
                                 getReadSales(sv));
            break;
        case '2' :
            /*productsByLetter(sgv,'A');*/
            break;
        }
    }
    /* Destroy memory */
}

void startController()
{
    /*controller->view = initView();*/
    SGV sgv = initSGV();
    menu(sgv);
}
