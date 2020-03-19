#include "branch.h"

#include <glib.h>
#include <stdio.h>
#include <string.h>

struct filial
{
    GHashTable* produtosClientes;
    GHashTable* clientesProdutos;
};


struct relacaoComCliente
{
    GHashTable* infoClientes;
    int totalVendidos; /* Quantidade de produto que este cliente comprou */
};


struct relacaoComProduto
{
    GHashTable* infoProdutos;
    float totalFaturado[12];
};

struct infoCliente
{
    int unidadesN;
    int unidadesP;
};

struct infoProduto
{
    int quantidades[12];
    float totalFaturado[12];
};

Filial initFilial() {
    Filial new = g_malloc(sizeof(struct filial));
    new->produtosClientes = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, (gpointer)freeRelacaoComCliente);
    new->clientesProdutos = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, (gpointer)freeRelacaoComProduto);

    return new;
}

RelacaoComCliente initRelacaoComCliente() {
    RelacaoComCliente new = g_malloc(sizeof(struct relacaoComCliente));
    new->totalVendidos = 0;
    new->infoClientes = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, (gpointer)freeInfoCliente);

    return new;
}

RelacaoComProduto initRelacaoComProduto() {
    RelacaoComProduto new = g_malloc(sizeof(struct relacaoComProduto));
    int i;
    for(i = 0; i < 12; i++) {
        new->totalFaturado[i] = 0;
    }
    new->infoProdutos = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, (gpointer)freeInfoProduto);

    return new;
}

InfoCliente initInfoCliente() {
    InfoCliente new = g_malloc(sizeof(struct infoCliente));
    new->unidadesN = 0;
    new->unidadesP = 0;
    return new;
}

InfoProduto initInfoProduto() {
    InfoProduto new = g_malloc(sizeof(struct infoProduto));
    int i;
    for(i = 0; i < 12; i++) {
        new->quantidades[i] = 0;
        new->totalFaturado[i] = 0;
    }
    return new;
}

void addRelacaoComCliente(Filial f, char* product, RelacaoComCliente rcc) {
    g_hash_table_insert(f->produtosClientes, product, rcc);
}

void addRelacaoComProduto(Filial f, char* client, RelacaoComProduto rcp) {
    g_hash_table_insert(f->clientesProdutos, client, rcp);
}

void addInfoCliente(RelacaoComCliente rcc, char* client, InfoCliente ic) {
    g_hash_table_insert(rcc->infoClientes, client, ic);
}

void addInfoProduto(RelacaoComProduto rcp, char* product, InfoProduto ip) {
    g_hash_table_insert(rcp->infoProdutos, product, ip);
}

void updateFilial(Filial f, char* client_code, char* product_code, int units, char promotion, float faturado, int month) {
    RelacaoComCliente rcc = g_hash_table_lookup(f->produtosClientes, client_code);
    RelacaoComProduto rcp = g_hash_table_lookup(f->clientesProdutos, product_code);
    if (rcc == NULL) {
        char* _code_client = strdup(client_code);

        strtok(_code_client, "\r\n");
        g_hash_table_insert(f->produtosClientes, _code_client, initRelacaoComCliente());
        rcc = g_hash_table_lookup(f->produtosClientes, _code_client);
    }
    if (rcp == NULL) {
        char* _code_product = strdup(product_code);

        strtok(_code_product, "\r\n");
        g_hash_table_insert(f->clientesProdutos, _code_product, initRelacaoComProduto());
        rcp = g_hash_table_lookup(f->clientesProdutos, _code_product);
    }
    updateRelacaoComCliente(rcc, client_code, units, promotion);
    updateRelacaoComProduto(rcp, product_code, units, faturado, month);
}

void updateRelacaoComProduto(RelacaoComProduto rcp, char* product, int qnt, float faturado, int mes) {
    rcp->totalFaturado[mes-1] += faturado;
    InfoProduto ip = g_hash_table_lookup(rcp->infoProdutos, product);
    if (ip == NULL) {
        char* _code_product = strdup(product);

        strtok(_code_product, "\r\n");
        g_hash_table_insert(rcp->infoProdutos, _code_product, initInfoProduto());
        ip = g_hash_table_lookup(rcp->infoProdutos, _code_product);
    }
    updateInfoProduto(ip,qnt,faturado,mes);
}

void updateRelacaoComCliente(RelacaoComCliente rcc, char* client, int units, char promotion) {
    rcc->totalVendidos += units;
    InfoCliente ic = g_hash_table_lookup(rcc->infoClientes,client);
    if (ic == NULL) {
        char* _code_client = strdup(client);

        strtok(_code_client, "\r\n");
        g_hash_table_insert(rcc->infoClientes, _code_client, initInfoCliente());
        ic = g_hash_table_lookup(rcc->infoClientes,_code_client);
    }
    updateInfoCliente(ic,units,promotion);
}

void updateInfoCliente(InfoCliente ic, int units, char promotion) {
    if (promotion == 'P') {
        ic->unidadesP += units;
    } else if (promotion == 'N') {
        ic->unidadesN += units;
    }
}

void updateInfoProduto(InfoProduto ip, int quantidade, float faturado, int mes) {
    ip->quantidades[mes-1] += quantidade;
    ip->totalFaturado[mes-1] += faturado;
}

void freeFilial(Filial f) {
    g_hash_table_destroy(f->produtosClientes);
    g_hash_table_destroy(f->clientesProdutos);
    g_free(f);
}

void freeRelacaoComCliente(RelacaoComCliente rc) {
    g_hash_table_destroy(rc->infoClientes);
    g_free(rc);
}

void freeRelacaoComProduto(RelacaoComProduto rp) {
    g_hash_table_destroy(rp->infoProdutos);
    g_free(rp);
}

void freeInfoCliente(InfoCliente ic) {
    g_free(ic);
}

void freeInfoProduto(InfoProduto ip) {
    g_free(ip);
}
