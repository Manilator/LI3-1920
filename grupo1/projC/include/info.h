#ifndef ___INFO_H___
#define ___INFO_H___

#include <glib.h>


typedef struct info* Info;

typedef struct aux* Aux;

typedef struct money* Money;

typedef struct querie8Aux* Querie8Aux;

typedef struct querie9Aux* Querie9Aux;

/**
@brief Compara duas estruturas Money
@param a xxx
@param b xxx
@return int Diferença entre o montante na estrutura a e na b
*/
int compareMoney(gconstpointer, gconstpointer);

/**
@brief Copia as informações para uma nova estrutura Money
@param money Estrutura Money
@return Money Estrutura auxiliar para retornar resultados da query 12
*/
Money cloneMoney(Money);

/**
@brief Libertação da estrutura Money
@param money Estrutura Money
*/
void freeMoney(Money);

/**
@brief Copia as informações para uma nova estrutura Aux
@param aux Estrutura Aux
@return Aux Estrutura auxiliar para retornar resultados da query xxx
*/
Aux cloneAux(Aux);

/**
@brief Libertação da estrutura Aux
@param aux Estrutura Aux
*/
void freeAux(Aux);

/**
@brief Compara duas estruturas Aux
@param a xxx
@param b xxx
@return int Diferença entre o total de unidades vendidas na estrutura a e na b
*/
int compareAux(gconstpointer, gconstpointer);

/**
@brief Compara duas estruturas Info
@param a xxx
@param b xxx
@return int Diferença entre as unidades vendidas na estrutura a e na b
*/
int compareInfo(gconstpointer, gconstpointer);

/**
@brief Copia as informações para uma nova estrutura Info
@param info Estrutura Info
@return Info Estrutura auxiliar para retornar resultados da query xxx
*/
Info cloneInfo(Info);

/**
@brief Libertação da estrutura Info
@param info Estrutura Info
*/
void freeInfo(Info);

/**
@brief Inicialização da estrutura Money
@param key xxx
@param value xxx
@return Money Estrutura auxiliar para retornar resultados da query 12
*/
Money initMoney(char*, double);

/**
@brief Atualizar os dados dentro da estrutura Money
@param money Estrutura Money
@param value Montante gasto a ser adicionado
*/
void updateMoney(Money, double);

/**
@brief Atualizar os dados dentro da estrutura Aux
@param aux Estrutura Aux
@param branch xxx
@param value xxx
*/
void updateAux(Aux, int, int *);

/**
@brief Inicialização da estrutura Aux
@param key xxx
@param branch xxx
@param value xxx
@return Aux Estrutura auxiliar para retornar resultados da query xxx
*/
Aux initAux(char*, int, int *);

/**
@brief Atualizar os dados dentro da estrutura Info
@param info Estrutura Info
@param value Unidades vendidas que serão adicionadas
*/
void updateInfo(Info, int);

/**
@brief Inicialização da estrutura Info
@param key xxx
@param value xxx
@return Info Estrutura auxiliar para retornar resultados da query xxx
*/
Info initInfo(char*, int);

/**
@brief Libertação de um array de estruturas Info
@param list Array de estruturas Info
*/
void freeInfoList(Info*);

/**
@brief Libertação de um array de estruturas Aux
@param list Array de estruturas Aux
*/
void freeAuxList(Aux*);

/**
@brief Libertação de um array de estruturas Money
@param list Array de estruturas Money
*/
void freeMoneyList(Money*);

/**
@brief Devolve o código de produto da estrutura Info
@param info Estrutura Info
@return char* Código de Produto
*/
char* getInfoProduct(Info);

/**
@brief Devolve o código de produto da estrutura Aux
@param aux Estrutura Aux
@return char* Código de Produto
*/
char* getAuxProduct(Aux);

/**
@brief Devolve as unidades vendidas de um índice na estrutura Aux
@param aux Estrutura Aux
@param i Índice xxx
@return int Unidades vendidas
*/
int getAuxUnitsSold(Aux, int);

/**
@brief Devolve o número de clientes de um índice na estrutura Aux
@param aux Estrutura Aux
@param i Índice xxx
@return int Número de clientes
*/
int getAuxTotalClients(Aux, int);

/**
@brief Devolve o código de produto da estrutura Money
@param aux Estrutura Aux
@return char* Código de Produto
*/
char* getMoneyProduct(Money);

/**
@brief Devolve o montante gasto da estrutura Money
@param money Estrutura Money
@return double Montante gasto
*/
double getMoneySpent(Money money);

/**
@brief Devolve a quantidade de unidades vendidas da estrutura Info
@param info Estrutura Info
@return int Quantidade de unidades vendidas
*/
int getInfoUnitsSold(Info info);

/**
@brief Atualizar os dados dentro da estrutura Querie8Aux
@param aux Estrutura Querie8Aux
@param billed Montante faturado
@param units Unidades vendidas
@param sales Quantidade de vendas
*/
void updateQuerie8(Querie8Aux, double, int, int);

/**
@brief Inicialização da estrutura Querie8Aux
@return Querie8Aux Estrutura auxiliar para retornar resultados da query 8
*/
Querie8Aux initQuerie8Aux();

/**
@brief Devolve a quantidade de unidades vendidas da estrutura Aux
@param aux Estrutura Querie8Aux
@return int Quantidade de unidades vendidas
*/
int getQuerie8AuxUnits(Querie8Aux);

/**
@brief Devolve o total faturado da estrutura Aux
@param aux Estrutura Querie8Aux
@return double Montante faturado
*/
double getQuerie8AuxBilled(Querie8Aux);

/**
@brief Devolve a quantidade de vendas da estrutura Aux
@param aux Estrutura Querie8Aux
@return int Quantidade de vendas
*/
int getQuerie8AuxSales(Querie8Aux);

/**
@brief Libertação da estrutura Querie8Aux
@param aux Estrutura Querie8Aux
*/
void freeQuerie8Aux(Querie8Aux);

/* xxx ??
void updateQuerie9(Querie9Aux, double, int, int);

Querie8Aux initQuerie9Aux();

int getQuerie9AuxUnits(Querie9Aux);

double getQuerie9AuxBilled(Querie9Aux);

int getQuerie9AuxSales(Querie9Aux);

void freeQuerie9Aux(Querie9Aux);*/

/**
@brief Incrementa o valor totalN dentro da estrutura Querie9Aux
@param aux Estrutura Querie9Aux
*/
void updateTotalN(Querie9Aux);

/**
@brief Incrementa o valor totalP dentro da estrutura Queries9Aux
@param aux Estrutura Querie9Aux
*/
void updateTotalP(Querie9Aux);

/**
@brief Devolve o valor de totalN da estrutura Querie9Aux
@param aux Estrutura Querie9Aux
@return int xxx
*/
int getQuerie9TotalN(Querie9Aux aux);

/**
@brief Devolve o valor de totalP da estrutura Querie9Aux
@param aux Estrutura Querie9Aux
@return int xxx
*/
int getQuerie9TotalP(Querie9Aux aux);

/**
@brief Inicialização da estrutura Querie9Aux
@param size xxx
@return Querie9Aux Estrutura auxiliar para retornar resultados da query 9
*/
Querie9Aux initQuerie9Aux(int);

/**
@brief Atualizar o valor clientsN de um certo índice na estrutura Querie9Aux
@param aux Estrutura Querie9Aux
@param i Índice onde será adicionada a key
@param key xxx
*/
void updateClientsN(Querie9Aux, int, char*);

/**
@brief Atualizar o valor clientsP de um certo índice na estrutura Querie9Aux
@param aux Estrutura Querie9Aux
@param i Índice onde será adicionada a key
@param key xxx
*/
void updateClientsP(Querie9Aux, int, char*);

/**
@brief Atualizar clientsN e clientsP para NULL na estrutura Querie9Aux
@param aux Estrutura Querie9Aux
@param i Índice xxx
@param i Índice xxx
*/
void updateClients(Querie9Aux, int, int);

/**
@brief Devolve o valor de clientsP num certo índice na estrutura Querie9Aux
@param aux Estrutura Querie9Aux
@param i Índice xxx
@return char* Código de Cliente
*/
char * getQuerie9ClientN(Querie9Aux, int);

/**
@brief Devolve o valor de clientsP num certo índice na estrutura Querie9Aux
@param aux Estrutura Querie9Aux
@param i Índice xxx
@return char* Código de Cliente
*/
char * getQuerie9ClientP(Querie9Aux, int);

/**
@brief Libertação da estrutura Querie9Aux
@param aux Estrutura Querie9Aux
*/
void freeQuerie9Aux(Querie9Aux);

#endif
