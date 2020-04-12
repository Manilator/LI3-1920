/**
@file sgv.h
\brief Módulo de sistema de gestão de vendas
*/
#ifndef ___SGV__H___
#define ___SGV__H___

#include "info.h"

#include <glib.h>

typedef struct sgv* SGV;

typedef struct startValues* StartValues;

/**
@brief Devolve a estrutura SGV com o conteúdo dos ficheiros dados
@param sgv Estrutura SGV
@param sv Estrutura StartValues
@return SGV Estrutura SGV
 */
SGV startSGV(SGV, StartValues);

/**
@brief Devolve a estrutura SGV inicializada
@return SGV Estrutura SGV
 */
SGV initSGV();

/**
@brief Devolve a estrutura StartValues inicializada
@return StartValues Estrutura StartValues
 */
StartValues initStartValues();

/**
@brief Devolve a estrutura SGV com o conteúdo dos ficheiros dados
@param startValues Estrutura StartValues
@param clients_path Path do ficheiro de clientes
@param products_path Path do ficheiro de produtos
@param sales_path Path do ficheiro de vendas
 */
void setPathsSV(StartValues, char*, char*, char*);

/**
@brief Devolve o número total de vendas e o total facturado com esse produto  em tal mês, distinguindo os totais em modo N e os totais em modo P
@param sgv Estrutura SGV
@param letter Letra entre A a Z
@return char** Path do ficheiro de vendas
 */
char ** getProductsStartedByLetter(SGV, char);

/**
@brief Devolve todos os códigos de produto que começam com uma certa letra
@param sgv Estrutura SGV
@param product_code Código de produto
@param month Número do mês
@param branches Filial
@return double* Path do ficheiro de vendas
 */
double * getProductSalesAndProfit(SGV, char* , int, int);

/**
@brief Devolve a lista ordenada dos códigos dos produtos(e o seu número total)que ninguém comprou, podendo o utilizador decidir igualmente se pretende valores totais ou divididos pelas filiais.
@param sgv Estrutura SGV
@param isGlobal Número que representa modo global ou uma filial
@return char*** Array com Arrays de códigos de produtos
 */
char *** getProductsNeverBought(SGV, int);

/**
@brief Devolve a lista ordenada de códigos de clientes que realizaram compras em todas as filiais
@param sgv Estrutura SGV
@return char** Array com códigos de clientes
 */
char** getClientsOfAllBranches(SGV);

/*6*/
int * getClientsAndProductsNeverBoughtCount(SGV);

/*7*/
int ** getProductsBoughtByClient(SGV, char*);

/*8*/
Querie8Aux getSalesAndProfit(SGV, int, int);

/*9*/
Querie9Aux getProductBuyers(SGV, char*, int);

/*10*/
Info * getClientsFavoriteProducts(SGV, char*, int);

/*11*/
Aux * getTopSoldProducts(SGV, int);

/*12*/
Money * getClientTopProfitProducts(SGV, char*, int);

/**
@brief Devolver o path do ficheiro de clientes
@param sv Estrutura StartValues
@return char* Path do ficheiro de clientes
 */
char* getClientsPath(StartValues);

/**
@brief Devolver o path do ficheiro de produtos
@param sv Estrutura StartValues
@return char* Path do ficheiro de produtos
 */
char* getProductsPath(StartValues);

/**
@brief Devolver o path do ficheiro de vendas
@param sv Estrutura StartValues
@return char* Path do ficheiro de vendas
 */
char* getSalesPath(StartValues);

/**
@brief Devolver o número de clientes válidos no ficheiro de clientes
@param sv Estrutura StartValues
@return int Número de clientes válidos
 */
int getValidClients(StartValues);

/**
@brief Devolver o número de clientes válidos no ficheiro de produtos
@param sv Estrutura StartValues
@return int Número de produtos válidos
 */
int getValidProducts(StartValues);

/**
@brief Devolver o número de clientes válidos no ficheiro de vendas
@param sv Estrutura StartValues
@return int Número de vendas válidos
 */
int getValidSales(StartValues);

/**
@brief Devolver o número de clientes lidos no ficheiro de clientes
@param sv Estrutura StartValues
@return int Número de clientes lidos
 */
int getReadClients (StartValues);

/**
@brief Devolver o número de produtos lidos no ficheiro de produtos
@param sv Estrutura StartValues
@return int Número de produtos lidos
 */
int getReadProducts (StartValues);

/**
@brief Devolver o número de vendas lidos no ficheiro de vendas
@param sv Estrutura StartValues
@return int Número de vendas lidos
 */
int getReadSales (StartValues);


/**
@brief Devolver o tamanho de um Array de strings(char*)
@param list Array de strings(char*)
@return int Tamanho de um Array de strings(char*)
 */
int listSize(char**);

/**
@brief Libertar memória na estrutura SGV
@param sgv Estrutura SGV
 */
void destroySGV(SGV);

/**
@brief Libertar memória na estrutura StartValues
@param sv Estrutura StartValues
 */
void destroyStartValues(StartValues);

/**
@brief Libertar memória alocada no array
@param list Array de strings(char*)
 */
void freeStringList(char **);

/**
@brief Libertar memória alocada na matriz
@param matrix Array com arrays de strings(char*)
 */
void freeStringMatrix(char ***);

/**
@brief Libertar memória alocada na matriz
@param matrix Array com arrays de int
 */
void freeIntMatrix(int **);

#endif
