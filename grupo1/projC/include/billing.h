#ifndef ___BILLING_H___
#define ___BILLING_H___

typedef struct fatura* Fatura;

typedef struct faturaProduto* FaturaProduto;

Fatura initFatura();

FaturaProduto initFaturaProduto();

int addFaturaProduto(Fatura f, char* code);

void updateFatura(Fatura f, char* code, float tf, int u, char tipo, int filial);

int updateFaturaProduto(FaturaProduto fp, float tf, int u, char tipo, int filial);

FaturaProduto getFaturaProduto(Fatura f, char* product);

float getTotalFaturadoFatura(Fatura f);

float getTotalFaturadoN_FP(FaturaProduto fp);

char* getFirstKey(Fatura f);

void freeFaturaProduto(FaturaProduto fp);

void freeFatura(Fatura f);

#endif