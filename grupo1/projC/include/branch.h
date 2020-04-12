/**
@file branch.h
\brief Módulo de tratamento de filiais.
*/
#ifndef ___BRANCH_H___
#define ___BRANCH_H___

#include <glib.h>
#include "info.h"

typedef struct branch* Branch;

typedef struct relationWithClient* RelationWithClient;

typedef struct relationWithProduct* RelationWithProduct;

typedef struct infoClient* InfoClient;

typedef struct infoProduct* InfoProduct;

/**
@brief Inicialização da estrutura Branch
@return Branch Devolve um Branch com valores iniciais
*/
Branch initBranch();

/**
@brief Inicialização da estrutura RelationWithClient
@return RelationWithClient Devolve um RelationWithClient com valores iniciais
*/
RelationWithClient initRelationWithClient();

/**
@brief Inicialização da estrutura RelationWithProduct
@return RelationWithProduct Devolve um RelationWithProduct com valores iniciais
*/
RelationWithProduct initRelationWithProduct();

/**
@brief Inicialização da estrutura InfoClient
@return InfoClient Devolve um InfoClient com valores iniciais
*/
InfoClient initInfoClient();

/**
@brief Inicialização da estrutura InfoProduct
@return InfoProduct Devolve um InfoProduct com valores iniciais
*/
InfoProduct initInfoProduct();

/**
@brief Adiciona a estrutura relationWithClient á hashtable presente na estrutura productsClients
@param branch Estrutura Branch
@param product_code Código do produto
@param rcc Estrutura RelationWithClient
*/
void addRelationWithClient(Branch, char*, RelationWithClient);

/**
@brief Adiciona a estrutura RelationWithProduct á hashtable presente na estrutura clientsProducts
@param branch Estrutura Branch
@param client_code Código do cliente
@param rcp Estrutura RelationWithProduct
*/
void addRelationWithProduct(Branch, char*, RelationWithProduct);

/**
@brief Adiciona a estrutura InfoClient á hashtable presente na estrutura RelationWithClient
@param rcc Estrutura RelationWithClient
@param client_code Código do cliente
@param ic Estrutura InfoClient
*/
void addInfoClient(RelationWithClient, char*, InfoClient);

/**
@brief Adiciona a estrutura InfoProduct á hashtable presente na estrutura RelationWithProduct
@param rcp Estrutura RelationWithProduct
@param product_code Código do produto
@param ip Estrutura InfoProduct
*/
void addInfoProduct(RelationWithProduct, char*, InfoProduct);

/**
@brief Atualizar os dados dentro da estrutura Branch
@param b Estrutura Branch
@param client_code Código do cliente
@param product_code Código do produto
@param units Unidades a adicionar
@param promotion_type Tipo de promoção
@param billed Valor faturado
@param month Mês em que xxx
*/
void updateBranch(Branch, char*, char*, int, char, double, int);

/**
@brief Atualizar os dados dentro da estrutura RelationWithProduct
@param rcp Estrutura RelationWithProduct
@param product_code Código do produto
@param quantity Quantidade de itens vendidos
@param billed Valor faturado
@param month Mês em que xxx
*/
void updateRelationWithProduct(RelationWithProduct, char*, int, double, int);

/**
@brief Atualizar os dados dentro da estrutura RelationWithClient
@param rcc Estrutura RelationWithClient
@param client_code Código do cliente
@param units Unidades (xxx vendidas/compradas)
@param promotion_type Tipo de promoção
*/
void updateRelationWithClient(RelationWithClient, char*, int, char);

/**
@brief Atualizar os dados dentro da estrutura InfoClient
@param ic Estrutura InfoClient
@param units Unidades (xxx vendidas/compradas)
@param promotion_type Tipo de promoção
*/
void updateInfoClient(InfoClient, int, char);

/**
@brief Atualizar os dados dentro da estrutura InfoProduct
@param ip Estrutura InfoProduct
@param quantity Quantidade de itens vendidos
@param billed Valor faturado
@param month Mês em que xxx
*/
void updateInfoProduct(InfoProduct, int, double, int);

/**
@brief Libertação da estrutura Branch
@param branch Estrutura Branch a ser libertada
*/
void freeBranch(Branch);

/**
@brief Libertação da estrutura RelationWithClient
@param rc Estrutura RelationWithClient a ser libertada
*/
void freeRelationWithClient(RelationWithClient);

/**
@brief Libertação da estrutura RelationWithProduct
@param rp Estrutura RelationWithProduct a ser libertada
*/
void freeRelationWithProduct(RelationWithProduct);

/**
@brief Libertação da estrutura InfoClient
@param ic Estrutura InfoClient a ser libertada
*/
void freeInfoClient(InfoClient);

/**
@brief Libertação da estrutura InfoProduct
@param ip Estrutura InfoProduct a ser libertada
*/
void freeInfoProduct(InfoProduct);

/**
@brief Devolve o array ordenado dos códigos de clientes que compraram numa certa filial
@param branch Estrutura Branch
@param n Número easter egg
@return char** Array ordenado dos códigos de clientes que compraram numa certa filial
*/
char** getClientCodes(Branch, int*);

/**
@brief Devolve um array de códigos de produto vendidos numa certa filial
@param b Estrutura Branch
@return char** Array de códigos de produto vendidos numa certa filial
*/
char ** getProductsInBranch(Branch);

/**
@brief Deolve uma estrutura Query9Aux com os valores especificos a um dado código de produto
@param b Estrutura Branch
@param product_code Código do produto
@return Query9Aux Estrutura auxiliar para devolver resultados da query 9
*/
Query9Aux productBoughtBy(Branch, char *);

/**
@brief Devolve um array com todos os códigos de cliente de uma certa filial
@param branch Estrutura Branch
@return char** Array de códigos de clientes
*/
char ** getClientsInBranch(Branch);

/**
@brief Devolve um array com as quantidades de produtos comprados em cada mês
@param b Estrutura Branch
@param client_code Código do cliente
@return int* Array com quantidades de produtos comprados em cada mês
*/
int * getClientShopLog(Branch, char*);

/**
@brief Atualiza Hashtable com key=código de produto e value=Estrutura Info
@param b Estrutura Branch
@param client_code Código do cliente
@param month Mês a procurar
@param _mostBought Hashtable com códigos de produto e quantidades compradas num mês especifico
*/
void getMostBoughtByBranch(Branch, char*, int, GHashTable *);

/**
@brief Atualiza Hashtable com key=código de produto e value=Estrutura Aux
@param b Estrutura Branch
@param _mostBought Hashtable com códigos de produto e quantidades compradas o ano todo
@param branch Número da filial escolhida
*/
void updateNMostBought(Branch, GHashTable *, int);

/**
@brief Atualiza Hashtable com key=código de cliente e value=Estrutura Money
@param b Estrutura Branch
@param client_code Código do cliente
@param _maxSpent Hashtable com códigos de clientes e os valores gastos o ano todo
*/
void clientSpentMostOnBranch(Branch, char*, GHashTable *);

/**
@brief Remove todos os códigos de cliente que não compraram numa dada filial
@param b Estrutura Branch
@param _mostBought Hashtable com códigos de clientes
*/
void intersectClients(Branch, GHashTable *);

#endif
