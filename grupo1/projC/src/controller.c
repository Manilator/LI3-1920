#include "controller.h"
#include "view.h"
#include "sgv.h"


#include <stdio.h>

void menu(SGV sgv)
{
    char n = ' ';
    StartValues sv;
    while (n != '0')
    {
        n = getchar();
        switch (n)
        {
            case '1':
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
            break;
            case '5':
                query5(sgv);
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
