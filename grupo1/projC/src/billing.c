#include "billing.h"
#include "constants.h"

#include <glib.h>
#include <stdio.h>
#include <string.h>


struct billing
{
    float totalBilled;
    int unitiesP;
    int unitiesN;
    int branches[N_BRANCHES];
    GHashTable* billingsProduct;
};

struct billingProduct
{
    float totalBilledN;
    float totalBilledP;
    int unitiesP;
    int unitiesN;
    int branchesQnt[N_BRANCHES][N_TYPES];
    float brachesBilled[N_BRANCHES][N_TYPES];
};

Billing initBilling() {
    Billing new = g_malloc(sizeof(struct billing));
    new->totalBilled = 0;
    new->unitiesP = 0;
    new->unitiesN = 0;
    int i;
    for(i = 0; i < N_BRANCHES; i++) {
        new->branches[i] = 0;
    }
     new->billingsProduct = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, (gpointer)freeBillingProduct);
     return new;
}

BillingProduct initBillingProduct() {
    BillingProduct new = g_malloc(sizeof(struct billingProduct));
    new->totalBilledN = 0;
    new->totalBilledP = 0;
    new->unitiesP = 0;
    new->unitiesN = 0;
    int i, j;
    for(i = 0; i < N_BRANCHES; i++) {
        for(j = 0; j < N_TYPES; j++) {
            new->branchesQnt[i][j] = 0;
            new->brachesBilled[i][j] = 0;
        }
    }
    return new;
}
/*
Billing cloneBilling(Billing b) {
    Billing new = g_malloc(sizeof(struct billing));
    new->totalBilled = b->totalBilled;
    new->unitiesP = b->unitiesP;
    new->unitiesN = b->unitiesN;

    memcpy(new->branches, b->branches, N_BRANCHES * sizeof(int));
    new->billingsProduct = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, (gpointer)freeBillingProduct);
    memcpy(new->billingProduct, b->billingProduct, g_hash_table_size(b->billingProduct) * sizeof(struct billingProduct));
    return new;
}
*/

int addBillingProduct(Billing b, char* code) {
    BillingProduct new = initBillingProduct();
    char* _code = strdup(code);

    strtok(_code, "\r\n");

    if (!g_hash_table_contains(b->billingsProduct,_code)) {
        g_hash_table_insert(b->billingsProduct, (char*)_code, (gpointer)new);
        return 1;
    }
    g_free(_code);
    return 0;
}

void updateBilling(Billing b, char* code, float totalBilled, int unities, char promotion_type, int branch) {

    b->totalBilled += totalBilled;
    if(promotion_type == 'N') {
        b->unitiesN += unities;
    } else if (promotion_type == 'P') {
        b->unitiesP += unities;
    }
    b->branches[branch-1] += unities;
    BillingProduct bp = (BillingProduct)g_hash_table_lookup(b->billingsProduct, code);
    updateBillingProduct(bp, totalBilled, unities, promotion_type, branch);
}

int updateBillingProduct(BillingProduct bp, float totalBilled, int unities, char promotion_type, int branch) {
    int r = 0;
    if (promotion_type == 'N') {
        bp->totalBilledN += totalBilled;
        bp->unitiesN += unities;
        bp->brachesBilled[branch-1][N] += totalBilled;
        bp->branchesQnt[branch-1][N] += unities;
        r = 1;
    } else if (promotion_type == 'P') {
        bp->totalBilledP += totalBilled;
        bp->unitiesP += unities;
        bp->brachesBilled[branch-1][P] += totalBilled;
        bp->branchesQnt[branch-1][P] += unities;
        r = 1;
    }
    return r;
}

float getTotalBilledBilling(Billing b) {
    return b->totalBilled;
}

BillingProduct getBillingProduct(Billing b, char* product_code) {
    return g_hash_table_lookup(b->billingsProduct, product_code);
}

float getTotalBilledN_BP(BillingProduct bp) {
    return bp->totalBilledN;
}

/* QUERIE 3 */
float * getProductValuesByMonthBilling(Billing b, char* product_code, int branch){
    BillingProduct bp = (BillingProduct)g_hash_table_lookup(b->billingsProduct, product_code);
    int elem_per_branch = 4;
    float * _arrayResult = g_malloc(sizeof(float)*elem_per_branch);
    _arrayResult[--elem_per_branch] = bp->brachesBilled[branch][P];
    _arrayResult[--elem_per_branch] = bp->brachesBilled[branch][N];
    _arrayResult[--elem_per_branch] = bp->branchesQnt[branch][P];
    _arrayResult[--elem_per_branch] = bp->branchesQnt[branch][N];

    return _arrayResult;
}

char* getFirstKey(Billing b) {
    guint *size = g_malloc(sizeof(guint));
    *size = 10;
    return (char *)g_hash_table_get_keys_as_array(b->billingsProduct,size)[1];
}

void freeBillingProduct(BillingProduct bp) {
    g_free(bp);
}

void freeBilling(Billing b) {
    g_hash_table_destroy(b->billingsProduct);
    g_free(b);
}
