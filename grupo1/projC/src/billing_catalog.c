#include "billing_catalog.h"
#include "constants.h"

#include <glib.h>
#include <string.h>
#include <stdio.h>



struct billings
{
    GHashTable* billings; /**< Número do mês e a sua estrutura atribuída Billing */
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

void insertBillingProduct(Billings bs,int month, char* product_code){
    int* key = g_malloc(sizeof(int));
    *key = month;
    Billing r = (Billing)g_hash_table_lookup(bs->billings, key);

    addBillingProduct(r, product_code);
    g_free(key);
}

void destroyBillings(Billings bs) {
    g_hash_table_destroy(bs->billings);
    g_free(bs);
}

/* QUERIE 3 */
double * getProductValuesByMonthBillingCat(Billings bs, char* product_code, int month, int isGlobal){
    double * _arrayResult;
    double * _arrayFinal;
    int branch,i=0;
    int elem_per_branch = 4;

    int* key = g_malloc(sizeof(int));
    *key = month;
    Billing r = (Billing)g_hash_table_lookup(bs->billings, key);
    g_free(key);

    if(isGlobal){
        _arrayFinal = g_malloc(sizeof(double)*elem_per_branch);
        for(i=0;i<elem_per_branch;i++)
            _arrayFinal[i]=0;
        for (branch = 0; branch < N_BRANCHES; branch++) {
            _arrayResult = getProductValuesByMonthBilling(r, product_code, branch);
            for(i=0;i<elem_per_branch;i++){
                _arrayFinal[i]+=_arrayResult[i];
            }
            g_free(_arrayResult);
        }
    }
    else{
        _arrayFinal = g_malloc(sizeof(double)*N_BRANCHES*elem_per_branch);

        for (branch = 0; branch < N_BRANCHES; branch++) {
            _arrayResult = getProductValuesByMonthBilling(r, product_code, branch);
            memcpy(_arrayFinal +(branch*elem_per_branch), _arrayResult, elem_per_branch * sizeof(double));
            g_free(_arrayResult);
        }
    }
    return _arrayFinal;
}

/* QUERY 8 */
Query8Aux getTotalsFromBillingMonthInterval(Billings bs, int monthI, int monthF)
{
    Query8Aux aux = initQuery8Aux();

    int i;
    Billing b;
    for (i = monthI; i <= monthF; i++)
    {
        int *key = g_malloc(sizeof(int));
        *key = i;

        b = (Billing)g_hash_table_lookup(bs->billings,key);
        updateTotalsFromBilling(b, aux);

        g_free(key);
    }

    return aux;
}
