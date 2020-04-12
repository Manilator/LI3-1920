/**
@file branch_catalog.h
\brief Módulo de tratamentos do catálogo de filiais
*/
#ifndef ___BRANCH_CATALOG_H___
#define ___BRANCH_CATALOG_H___

#include "branch.h"
#include "sale.h"

typedef struct branches* Branches;

/**
@brief Inicialização da estrutura Branches
@param branches Número de filiais a inicializar
@return Branches Estrutura Branches inicializada
*/
Branches initBranches(int);

/**
@brief Adicionar a estrutura Branch á hashtable branches
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
@return char** Array de clientes que compraram em todos as filiais
*/
char ** clientsInCommon(Branches, Clients);

/**
@brief Devolve um array de códigos de produto vendidos numa certa filial
@param bs Estrutura Branches
@param branch Número da filial escolhida
@return char** Array de códigos de produto vendidos numa certa filial
*/
char ** getProductsBought(Branches, int);

/**
@brief Deolve uma estrutura Query9Aux com os valores especificos a um dado código de produto
@param bs Estrutura Branches
@param product_code Código do produto
@param branch Número da filial escolhida
@return Query9Aux Estrutura auxiliar para devolver resultados da query 9
*/
Query9Aux clientsWhoBoughtProduct(Branches, char*, int);

/**
@brief Devolve um array com todos os códigos de cliente de uma certa filial
@param bs Estrutura Branches
@param branch Número da filial escolhida
@return char** Array de códigos de clientes
*/
char ** getClientsUsed(Branches, int);

/**
@brief Devolve um array com as quantidades de produtos comprados em cada mês
@param bs Estrutura Branches
@param client_code Código do cliente
@param branch Número da filial escolhida
@return int* Array com quantidades de produtos comprados em cada mês
*/
int * clientBranchShopLog(Branches, char*, int);

/**
@brief Devolve um array por ordem descendente de por quantidade comprada com a estrutura Info
@param bs Estrutura Branches
@param client_code Código do cliente
@param month Mês a procurar
@return Info Estrutura auxiliar para devolver resultados da query xxx
*/
Info * getMostBought(Branches, char*, int);

/**
@brief Devolve um array com a estrutura auxiliar Aux com os N produtos mais comprados
@param bs Estrutura Branches
@param n_products
@return Aux Estrutura auxiliar para devolver resultados da query xxx
*/
Aux * getNMostBoughtProducts(Branches, int);

/**
@brief Devolve um array com a estrutura auxiliar Money com os N produtos em que um cliente gastou mais dinheiro
@param bs Estrutura Branches
@param client_code Código do cliente
@param n Número de produtos a adicionar ao array final
@return Money* Array com estrutura auxiliar para devolver resultados da query 12
*/
Money * clientSpentMostOn(Branches, char*, int);

#endif
