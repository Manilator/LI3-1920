#ifndef ___BRANCH_CATALOG_H___
#define ___BRANCH_CATALOG_H___

#include "branch.h"
#include "sale.h"

typedef struct branches* Branches;


/**
@brief De um array de inteiros, mostra ao utilizador o conteúdo numa tabela
@param list Array de quantidades de produtos comprados nos meses
@param client Código do cliente ao qual as quantidades estão relacionadas
@return int devolve a escolha dada no input 
*/


/**
@brief Inicialização da estrutura Branches
@param branches Número de filiais a inicializar
@return Branches xxx
*/
Branches initBranches(int);

/**
@brief xxx
@param branches Estrutura Branches
@param branch Estrutura Branch a ser inserida
@param number Número da filial que vai ser inserida
*/
void addBranch(Branches, Branch, int);

/**
@brief Atualizar os dados dentro da estrutura Branches
@param branches Estrutura Branches
@param sale Estrutura Sale
*/
void updateBranches(Branches, Sale);

/**
@brief Libertar memória alocada da estrutura Branches
@param branches Estrutura Branches a ser libertada
*/
void destroyBranches(Branches);

/**
@brief Encontrar os clientes que compraram em todas as filiais
@param bs Estrutura Branches
@param clients Estrutura Clients
@return char** xxx
*/
char ** clientsInCommon(Branches, Clients);

/**
@brief xxx
@param bs Estrutura Branches
@param branch Número da filial escolhida
@return char** xxx
*/
char ** getProductsBought(Branches, int);

/**
@brief xxx
@param bs Estrutura Branches
@param product_code Código do produto
@param branch Número da filial escolhida
@return Querie9Aux Estrutura auxiliar para devolver resultados da query 9
*/
Querie9Aux clientsWhoBoughtProduct(Branches, char*, int);

/**
@brief xxx
@param bs Estrutura Branches
@param branch Número da filial escolhida
@return char** xxx
*/
char ** getClientsUsed(Branches, int);

/**
@brief xxx
@param bs Estrutura Branches
@param client_code Código do cliente
@param branch Número da filial escolhida
@return int* xxx
*/
int * clientBranchShopLog(Branches, char*, int);

/**
@brief xxx
@param bs Estrutura Branches
@param client_code Código do cliente
@param month Mês a procurar
@return Info Estrutura auxiliar para devolver resultados da query xxx
*/
Info * getMostBought(Branches, char*, int);

/**
@brief xxx
@param bs Estrutura Branches
@param n_products
@return Aux Estrutura auxiliar para devolver resultados da query xxx
*/
Aux * getNMostBoughtProducts(Branches, int);

/**
@brief xxx
@param bs Estrutura Branches
@param client_code Código do cliente
@param n xxx
@return Money Estrutura auxiliar para devolver resultados da query 12
*/
Money * clientSpentMostOn(Branches, char*, int);

#endif
