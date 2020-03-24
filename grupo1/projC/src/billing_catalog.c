#include "billing_catalog.h"
#include "constants.h"

#include <glib.h>
#include <string.h>
#include <stdio.h>


struct billings
{
    GHashTable* billings;
};

Billings initBillings() {
    Billings new = g_malloc(sizeof(struct billings));
    new->billings = g_hash_table_new_full(g_int_hash, g_int_equal, g_free, (gpointer)freeBilling);
    int month;

    for (month = 1; month < 13; month++) {
        addBilling(new, initBilling(), month);
    }

    return new;
}

void addBilling(Billings billings, Billing billing, int month) {
    int *mes = g_malloc(sizeof(int));
    *mes = month;
    g_hash_table_insert(billings->billings, mes, billing);
}

void updateBillings(Billings bs, Sale sale) {
    int *mes = g_malloc(sizeof(int));
    *mes = getMonth(sale);
    Billing exist = (Billing)g_hash_table_lookup(bs->billings,mes);
    updateBilling(exist, getProduct(sale), getPrice(sale) * getUnits(sale), getUnits(sale), getPromotion(sale), getBranch(sale));
    g_free(mes);
    /*g_hash_table_replace(fs->billings,mes,exist);*/
}

/* QUERIE 3 */
float * getProductValuesByMonthBillingCat(Billings bs, char* product_code, int month, int isGlobal){
    float * _arrayResult;
    float * _arrayFinal;
    int branch,i=0;
    int elem_per_branch = 4;

    int* key = g_malloc(sizeof(int));
    *key = month;
    Billing r = (Billing)g_hash_table_lookup(bs->billings, key);
    g_free(key);

    if(isGlobal){
        _arrayFinal = g_malloc(sizeof(float)*elem_per_branch);
        for(i=0;i<elem_per_branch;i++)
            _arrayFinal[i]=0;
        for (branch = 0; branch < N_BRANCHES; branch++) {
            _arrayResult = getProductValuesByMonthBilling(r, product_code, branch);
            for(i=0;i<elem_per_branch;i++){
                _arrayFinal[i]+=_arrayResult[i];
            }
            g_free(_arrayResult);
        }/*
        i=0;
        printf("N - Qnt: %.f\n", _arrayFinal[i++]);
        printf("P - Qnt: %.f\n", _arrayFinal[i++]);

        printf("N - Bil: %.2f\n", _arrayFinal[i++]);
        printf("P - Bil: %.2f\n", _arrayFinal[i++]);*/
    }
    else{
        _arrayFinal = g_malloc(sizeof(float)*N_BRANCHES*elem_per_branch);

        for (branch = 0; branch < N_BRANCHES; branch++) {
            _arrayResult = getProductValuesByMonthBilling(r, product_code, branch);
            memcpy(_arrayFinal +(branch*elem_per_branch), _arrayResult, elem_per_branch * sizeof(float));
            g_free(_arrayResult);
        }
    }
    return _arrayFinal;
        /*
        _arrayFinal[N_BRANCHES*elem_per_branch] = -1.0;

        printf("SEPARETED\n");
        while(_arrayFinal[i] != -1.0)
            printf("%f\n",_arrayFinal[i++]);
        i = 0;
        for (branch = 0; branch < N_BRANCHES; branch++) {
            printf("N - Qnt: %.f\n", _arrayFinal[i++]);
            printf("P - Qnt: %.f\n", _arrayFinal[i++]);

            printf("N - Bil: %.2f\n", _arrayFinal[i++]);
            printf("P - Bil: %.2f\n", _arrayFinal[i++]);
            printf("---------------\n");
        }*/
}


Billing getBilling(Billings bs, int month) {
    int* key = g_malloc(sizeof(int));
    *key = month;
    Billing r = (Billing)g_hash_table_lookup(bs->billings, key);
    g_free(key);
    return r;
}

void destroyBillings(Billings bs) {
    g_hash_table_destroy(bs->billings);
    g_free(bs);
}
