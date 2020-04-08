#include "branch_catalog.h"
#include "constants.h"

#include <glib.h>
#include <stdio.h>
#include <string.h>

struct branches
{
    GHashTable* branches;
};

Branches initBranches(int branches) {
    Branches new = g_malloc(sizeof(struct branches));
    new->branches = g_hash_table_new_full(g_int_hash, g_int_equal, g_free, (gpointer)freeBranch);
    int branch_number;

    for (branch_number = 1; branch_number <= branches; branch_number++) {
        addBranch(new, initBranch(), branch_number);
    }
    return new;
}

void addBranch(Branches branches, Branch branch, int number) {
    int *nr = g_malloc(sizeof(int));
    *nr = number;
    g_hash_table_insert(branches->branches, nr, branch);
}

void updateBranches(Branches branches, Sale sale) {
    int *branch_number = g_malloc(sizeof(int));
    *branch_number = getBranch(sale);
    Branch exist = (Branch)g_hash_table_lookup(branches->branches,branch_number);
    updateBranch(exist, getClient(sale), getProduct(sale), getUnits(sale), getPromotion(sale), getUnits(sale) * getPrice(sale), getMonth(sale));
    g_free(branch_number);
}

void destroyBranches(Branches fs) {
    g_hash_table_destroy(fs->branches);
    g_free(fs);
}

/* Interseção de 3 arrays */
char** intersect(char *ar1[], char *ar2[], char *ar3[], int n1, int n2, int n3, int *x)
{
    int i = 0, j = 0, k = 0;

    int n;
    if(n1 < n2 && n1 < n3) {
        n = n1;
    } else if (n2 < n3) {
        n = n2;
    } else {
        n = n3;
    }

    char **res;
    res = g_malloc(n * sizeof(char *));
    int count = 0;

    while (i < n1 && j < n2 && k < n3) {

        if (!strcmp(ar1[i],ar2[j]) && !strcmp(ar2[j],ar3[k])) {
            res[count] = strdup(ar1[i]);
            i++;
            j++;
            k++;
            count++;
        }

        else if (strcmp(ar1[i],ar2[j]) < 0)
            i++;

        else if (strcmp(ar2[j],ar3[k]) < 0)
            j++;

        else
            k++;
    }
    res[count] = '\0';
    *x = count;

    return res;
}

/* Encontrar os clientes que compraram nas 3 filiais */
char** clientsInCommon(Branches bs, int *x) {

    int *branch_number = g_malloc(sizeof(int));

    *branch_number = 1;
    Branch b1 = (Branch)g_hash_table_lookup(bs->branches, branch_number);

    *branch_number = 2;
    Branch b2 = (Branch)g_hash_table_lookup(bs->branches, branch_number);

    *branch_number = 3;
    Branch b3 = (Branch)g_hash_table_lookup(bs->branches, branch_number);

    int n1, n2, n3;

    char** codes1 = getClientCodes(b1, &n1);
    char** codes2 = getClientCodes(b2, &n2);
    char** codes3 = getClientCodes(b3, &n3);

    char** codes = intersect(codes1, codes2, codes3, n1, n2, n3, x);

    return codes;
}

char ** getProductsBought(Branches bs, int branch){
    int *_tmp = g_malloc(sizeof(int));
    *_tmp = branch;
    Branch b = (Branch)g_hash_table_lookup(bs->branches, _tmp);
    g_free(_tmp);
    return getProductsInBranch(b);
}

char *** clientsWhoBoughtProduct(Branches bs, char *product_code, int branch, int *totalN, int *totalP){
    int *_tmp = g_malloc(sizeof(int));
    *_tmp = branch;
    Branch b = (Branch)g_hash_table_lookup(bs->branches, _tmp);
    g_free(_tmp);
    return productBoughtBy(b, product_code, totalN, totalP);
}

char ** getClientsUsed(Branches bs, int branch){
    int *_tmp = g_malloc(sizeof(int));
    *_tmp = branch;
    Branch b = (Branch)g_hash_table_lookup(bs->branches, _tmp);
    g_free(_tmp);
    return getClientsInBranch(b);
}

int * clientBranchShopLog(Branches bs, char* client_code, int branch){
    int *_tmp = g_malloc(sizeof(int));
    *_tmp = branch;
    Branch b = (Branch)g_hash_table_lookup(bs->branches, _tmp);
    g_free(_tmp);
    return getClientShopLog(b, client_code);
}

int compareInfo(gconstpointer a, gconstpointer b){
    Info info1 = (const Info)a;
    Info info2 = (const Info)b;
    return (info2->unitsSold) - (info1->unitsSold);
}

void freeInfo(Info info){
    g_free(info->product_code);

}

Info cloneInfo(Info info){
    Info clone = g_malloc(sizeof(struct info));
    clone->product_code = strdup(info->product_code);

    clone->unitsSold = info->unitsSold;
    return clone;
}

Info * getMostBought(Branches bs, char* client_code, int month){
    GHashTable* _mostBought = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, (gpointer)freeInfo);
    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init (&iter, bs->branches);
    while (g_hash_table_iter_next (&iter, &key, &value)){
        getMostBoughtByBranch((Branch)value, client_code, month-ONE, _mostBought);
    }

    GList * _tmpList = g_hash_table_get_values(_mostBought);
    _tmpList = g_list_sort(_tmpList, compareInfo);

    int n_products = g_hash_table_size(_mostBought);
    Info * array = g_malloc(sizeof(Info)*n_products);

    GList * l;
    int k=0;
    for (l = _tmpList; n_products > 0; l = l->next){
        array[k++] = cloneInfo((Info)l->data);
        n_products--;
    }
    array[k] = NULL;
    /*g_hash_table_destroy(_mostBought);*/
    return array;
}

Aux cloneAux(Aux aux){
    Aux clone = g_malloc(sizeof(struct aux));
    clone->totalClients = g_malloc(sizeof(int*)*N_BRANCHES);
    clone->unitsSold = g_malloc(sizeof(int*)*N_BRANCHES);

    clone->product_code = strdup(aux->product_code);
    int i;
    for (i = ZERO; i < N_BRANCHES; i++) {
        clone->unitsSold[i] = aux->unitsSold[i];
        clone->totalClients[i] = aux->totalClients[i];
    }
    return clone;
}

void freeAux(Aux aux){
    g_free(aux->product_code);
    g_free(aux->totalClients);
    g_free(aux->unitsSold);
}

int compareAux(gconstpointer a, gconstpointer b){
    Aux n1 = (const Aux)a;
    Aux n2 = (const Aux)b;
    int total1=0,total2=0;
    int i;
    for (i = 0; i < N_BRANCHES; i++) {
        total1 += n1->unitsSold[i];
        total2 += n2->unitsSold[i];
    }
    return total2 - total1;
}

Aux * getNMostBoughtProducts(Branches bs, int n_products){
    GHashTable * _mostBought = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, (gpointer)freeAux);
    int *i;
    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init (&iter, bs->branches);
    while (g_hash_table_iter_next (&iter, &key, &value)){
        i = ((int*)key);
        updateNMostBought((Branch)value, _mostBought, (*i)-1);
    }

    GList * _tmpList = g_hash_table_get_values(_mostBought);
    _tmpList = g_list_sort(_tmpList, compareAux);

    Aux * array = g_malloc(sizeof(Aux)*n_products);

    GList * l;
    int k=0;
    for (l = _tmpList; n_products > 0; l = l->next){
        array[k++] = cloneAux((Aux)l->data);
        n_products--;
    }
    array[k] = NULL;

    return array;
}

int compareMoney(gconstpointer a, gconstpointer b)
{
    Money money1 = (const Money)a;
    Money money2 = (const Money)b;
    return (money2->moneySpent) - (money1->moneySpent);
}

Money cloneMoney(Money money)
{
    Money clone = g_malloc(sizeof(struct money));

    clone->product_code = strdup(money->product_code);
    clone->moneySpent = money->moneySpent;

    return clone;
}

void freeMoney(Money money)
{
    g_free(money->product_code);
}

Money * query12_aux_catalog(Branches bs, char *client_code, int n)
{
    GHashTable* _maxSpent = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, (gpointer)freeMoney);

    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init (&iter, bs->branches);
    while (g_hash_table_iter_next (&iter, &key, &value)){
        query12_aux((Branch)value, client_code, _maxSpent);
    }

    GList * _tmpList = g_hash_table_get_values(_maxSpent);
    _tmpList = g_list_sort(_tmpList, compareMoney);

    int n_products = n;
    Money *array = g_malloc(sizeof(Money)*n_products);

    GList * l;
    int k = 0;
    for (l = _tmpList; n_products > 0; l = l->next)
    {
        array[k++] = cloneMoney((Money)l->data);
        n_products--;
    }

    array[k] = NULL;

    /*g_hash_table_destroy(_maxSpent);*/

    return array;
}