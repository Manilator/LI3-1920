#include "controller.h"
#include "view.h"
#include "sgv.h"


#include <stdio.h>

void menu(SGV sgv)
{
    char n;
    StartValues sv;

    sv = initStartValues();
    sgv = startSGV(sv);
    viewPrintStartValues(getClientsPath(sv),
                        getProductsPath(sv),
                        getSalesPath(sv),
                        getValidClients(sv),
                        getValidProducts(sv),
                        getValidSales(sv),
                        getReadClients(sv),
                        getReadProducts(sv),
                        getReadSales(sv));
    query5_aux(sgv);
    
    /* Destroy memory */
}

void startController()
{
    /*controller->view = initView();*/
    SGV sgv = initSGV();
    menu(sgv);
}
