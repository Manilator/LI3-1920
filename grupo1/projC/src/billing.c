#include "billing.h"
#include "constants.h"

#include <glib.h>
#include <stdio.h>
#include <string.h>


struct billing
{
    int n_sales; /**< Número de Vendas */
    double totalBilled; /**< Total faturado */
    int unitiesP; /**< Unidades P vendidas */
    int unitiesN; /**< Unidades N vendidas */
    int branches[N_BRANCHES]; /**< Faturação dividida por filiais */
    GHashTable* billingsProduct; /**< Faturação dividida por produtos */
};

struct billingProduct
{
    double totalBilledN; /**< Total faturado no tipo N*/
    double totalBilledP; /**< Total faturado no tipo P*/
    int unitiesP; /**< Unidades P vendidas */
    int unitiesN; /**< Unidades N vendidas */
    int branchesQnt[N_BRANCHES][N_TYPES]; /**< Quantdade dividida por filiais e tipo de promoção */
    double brachesBilled[N_BRANCHES][N_TYPES]; /**< Faturação dividida por filiais e tipo de promoção */
};

Billing initBilling() {
    Billing new = g_malloc(sizeof(struct billing));
    new->n_sales = 0;
    new->totalBilled = 0.0;
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

int addBillingProduct(Billing billing, char* code) {
    BillingProduct new = initBillingProduct();
    char* _code = strdup(code);

    strtok(_code, "\r\n");

    if (!g_hash_table_contains(billing->billingsProduct,_code)) {
        g_hash_table_insert(billing->billingsProduct, (char*)_code, (gpointer)new);
        return 1;
    }
    g_free(_code);
    return 0;
}

void updateBilling(Billing billing, char* code, double totalBilled, int unities, char promotion_type, int branch) {

    billing->n_sales++;
    billing->totalBilled += totalBilled;
    if(promotion_type == 'N') {
        billing->unitiesN += unities;
    } else if (promotion_type == 'P') {
        billing->unitiesP += unities;
    }
    billing->branches[branch-1] += unities;
    BillingProduct bp = (BillingProduct)g_hash_table_lookup(billing->billingsProduct, code);
    updateBillingProduct(bp, totalBilled, unities, promotion_type, branch);
}

int updateBillingProduct(BillingProduct billingProduct, double totalBilled, int unities, char promotion_type, int branch) {
    int r = 0;
    if (promotion_type == 'N') {
        billingProduct->totalBilledN += totalBilled;
        billingProduct->unitiesN += unities;
        billingProduct->brachesBilled[branch-1][N] += totalBilled;
        billingProduct->branchesQnt[branch-1][N] += unities;
        r = 1;
    } else if (promotion_type == 'P') {
        billingProduct->totalBilledP += totalBilled;
        billingProduct->unitiesP += unities;
        billingProduct->brachesBilled[branch-1][P] += totalBilled;
        billingProduct->branchesQnt[branch-1][P] += unities;
        r = 1;
    }
    return r;
}

double getTotalBilledBilling(Billing billing) {
    return billing->totalBilled;
}

BillingProduct getBillingProduct(Billing billing, char* product_code) {
    return g_hash_table_lookup(billing->billingsProduct, product_code);
}

double getTotalBilledN_BP(BillingProduct billingProduct) {
    return billingProduct->totalBilledN;
}

/* QUERIE 3 */
double * getProductValuesByMonthBilling(Billing billing, char* product_code, int branch){
    BillingProduct bp = (BillingProduct)g_hash_table_lookup(billing->billingsProduct, product_code);
    int elem_per_branch = 4;
    double * _arrayResult = g_malloc(sizeof(double)*elem_per_branch);
    _arrayResult[--elem_per_branch] = bp->brachesBilled[branch][P];
    _arrayResult[--elem_per_branch] = bp->brachesBilled[branch][N];
    _arrayResult[--elem_per_branch] = bp->branchesQnt[branch][P];
    _arrayResult[--elem_per_branch] = bp->branchesQnt[branch][N];

    return _arrayResult;
}

char* getFirstKey(Billing billing) {
    guint *size = g_malloc(sizeof(guint));
    *size = 10;
    return (char *)g_hash_table_get_keys_as_array(billing->billingsProduct,size)[1];
}

void freeBillingProduct(BillingProduct billingProduct) {
    g_free(billingProduct);
}

void freeBilling(Billing billing) {
    g_hash_table_destroy(billing->billingsProduct);
    g_free(billing);
}

/* QUERY 8 */
void updateTotalsFromBilling(Billing billing, Query8Aux aux)
{
    int branchesTotal=0,i;
    for (i = 0; i < N_BRANCHES; i++)
        branchesTotal += billing->branches[i];

    updateQuerie8(aux, billing->totalBilled, branchesTotal, billing->n_sales);
}
