#include "controller.h"
#include "sgv.h"

#include <stdio.h>

void menu(){
    char n;
    while(n != '0'){
        n = getchar();
        switch (n) {
            case '1':
                startSGV();
                break;
        }
    }
    /* Destroy memory */
}

void startController(){
    /*controller->view = initView();*/
    menu();
}
