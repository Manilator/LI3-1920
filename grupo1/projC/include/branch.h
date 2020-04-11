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
@brief xxx
@param branch Estrutura Branch
@param product_code Código do produto
@param rcc Estrutura RelationWithClient
*/
void addRelationWithClient(Branch, char*, RelationWithClient);

/**
@brief xxx
@param branch Estrutura Branch
@param client_code Código do cliente
@param rcp Estrutura RelationWithProduct
*/
void addRelationWithProduct(Branch, char*, RelationWithProduct);

/**
@brief xxx
@param rcc Estrutura RelationWithClient
@param client_code Código do cliente
@param ic Estrutura InfoClient
*/
void addInfoClient(RelationWithClient, char*, InfoClient);

/**
@brief xxx
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
@brief xxx
@param branch Estrutura Branch
@param n xxx
@return char** xxx
*/
char** getClientCodes(Branch, int*);

/**
@brief xxx
@param b Estrutura Branch
@return char** xxx
*/
char ** getProductsInBranch(Branch);

/**
@brief xxx
@param b Estrutura Branch
@param product_code Código do produto
@return Querie9Aux Estrutura auxiliar para devolver resultados da query 9
*/
Querie9Aux productBoughtBy(Branch, char *);

/**
@brief xxx
@param branch Estrutura Branch
@return char** Array de códigos de clientes
*/
char ** getClientsInBranch(Branch);

/**
@brief xxx
@param b Estrutura Branch
@param client_code Código do cliente
@return char** xxx (?) Clientes que realizaram compras numa filial
*/
int * getClientShopLog(Branch, char*);

/**
@brief xxx
@param b Estrutura Branch
@param client_code Código do cliente
@param month Mês a procurar
@param _mostBought xxx
*/
void getMostBoughtByBranch(Branch, char*, int, GHashTable *);

/**
@brief xxx
@param b Estrutura Branch
@param _mostBought xxx
@param branch Número da filial escolhida
*/
void updateNMostBought(Branch, GHashTable *, int);

/**
@brief xxx
@param b Estrutura Branch
@param client_code Código do cliente
@param _maxSpent xxx
*/
void clientSpentMostOnBranch(Branch, char*, GHashTable *);

/**
@brief xxx
@param b Estrutura Branch
@param _mostBought xxx
*/
void intersectClients(Branch, GHashTable *);

#endif
