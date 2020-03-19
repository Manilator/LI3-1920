#ifndef ___BRANCH_H___
#define ___BRANCH_H___


typedef struct filial* Filial;

typedef struct relacaoComCliente* RelacaoComCliente;

typedef struct relacaoComProduto* RelacaoComProduto;

typedef struct infoCliente* InfoCliente;

typedef struct infoProduto* InfoProduto;

Filial initFilial();

RelacaoComCliente initRelacaoComCliente();

RelacaoComProduto initRelacaoComProduto();

InfoCliente initInfoCliente();

InfoProduto initInfoProduto();

void addRelacaoComCliente(Filial f, char* product, RelacaoComCliente rcc);

void addRelacaoComProduto(Filial f, char* client, RelacaoComProduto rcp);

void addInfoCliente(RelacaoComCliente rcc, char* client, InfoCliente ic);

void addInfoProduto(RelacaoComProduto rcp, char* product, InfoProduto ip);

void updateFilial(Filial f, char* client_code, char* product_code, int units, char promotion, float faturado, int month);

void updateRelacaoComProduto(RelacaoComProduto rcp, char* product, int qnt, float faturado, int mes);

void updateRelacaoComCliente(RelacaoComCliente rcc, char* client, int units, char promotion);

void updateInfoCliente(InfoCliente ic, int units, char promotion);

void updateInfoProduto(InfoProduto ip, int quantidade, float faturado, int mes);

void freeFilial(Filial f);

void freeRelacaoComCliente(RelacaoComCliente rc);

void freeRelacaoComProduto(RelacaoComProduto rp);

void freeInfoCliente(InfoCliente ic);

void freeInfoProduto(InfoProduto ip);

#endif