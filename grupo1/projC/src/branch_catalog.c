#include "branch_catalog.h"


#include <stdio.h> /* temporario */
#include <glib.h>

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

void addBranch(Branches branches, Branch filial, int number) {
    int *nr = g_malloc(sizeof(int));
    *nr = number;
    g_hash_table_insert(branches->branches, nr, filial);
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

/* interseçao de 3 arrays */
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
    res = malloc(n * sizeof(char *));
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

/* para testar que funciona */
char** teste(int *x) {
    char* codes1[] = {"AA1006", "AA1011", "AA1017", "AA1038", "AA1041", "AA1045", "AA1063", "AA1064", "AA1071", "AA1073", "AA1078"};
    char* codes2[] = {"AA1011", "AA1017", "AA1032", "AA1038", "AA1045", "AA1055", "AA1063", "AA1064", "AA1071"};
    char* codes3[] = {"AA1006", "AA1011", "AA1017", "AA1032", "AA1041", "AA1045", "AA1055", "AA1063", "AA1064", "AA1071", "AA1073", "AA1075"};
    int n1 = sizeof(codes1)/sizeof(codes1[0]);
    int n2 = sizeof(codes2)/sizeof(codes2[0]);
    int n3 = sizeof(codes3)/sizeof(codes3[0]);
    char **res = intersect(codes1, codes2, codes3, n1, n2, n3, x);
    return res;
}

void printBranch1(Branches bs) {

    int *branch_number = g_malloc(sizeof(int));
    *branch_number = 1;
    Branch b1 = (Branch)g_hash_table_lookup(bs->branches, branch_number);

    int n1;
    char** codes = getClientCodes(b1, &n1);
    printf("n1 = %d\n", n1);
/*    while (*codes++)
        printf ("%s\n", *codes);
*/
}

/* depois mudar nome*/
char** query5(Branches bs, int *x) {

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

/* auxiliar para imprimir os codigos de cliente de uma branch especifica
esta funcao pega numa branch 
*/
void printClientsBranch(Branches bs, int *branch_number) {

    Branch b = (Branch)g_hash_table_lookup(bs->branches, branch_number);
    int *inutil;
    char** codes = getClientCodes(b, inutil);
    while (*++codes)
        printf ("%s\n", *codes);
}