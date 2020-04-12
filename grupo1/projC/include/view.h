/**
@file view.h
\brief Módulo da view.
*/

#ifndef ___VIEW_H___
#define ___VIEW_H___

#include "info.h"

/**
@brief Imprimir o menu
 */
void printMenu();

/**
@brief Imprimir um separador
*/
void printSeparator();

/**
@brief Limpar o terminal
*/
void cleanConsole();

/**
@brief Resetar o texto à sua cor padrão
*/
void resetColor();

/**
@brief Colocar a vermelho o conteúdo impresso de seguida
*/
void boldRed();

/**
@brief Colocar a ciano o conteúdo impresso de seguida
*/
void boldCyan();

/**
@brief Imprimir os valores de carregamento da base de dados
*/
void viewPrintStartValues(char *clients_path,
                          char *products_path,
                          char *sales_path,
                          int   valid_clients,
                          int   valid_products,
                          int   valid_sales,
                          int   clients_read,
                          int   products_read,
                          int   sales_read);

/**
@brief Imprime a mensagem fornecida
@param message Mensagem a ser impressa
*/
void printMessage(char*);

/**
@brief De um array de strings, mostra ao utilizador o conteúdo em forma de páginas
@param list Array de códigos de produtos
@param size Tamanho do array
*/
void listView(char **, int, int);

/**
@brief De um array de inteiros, mostra ao utilizador o conteúdo numa tabela
@param list Array de quantidades de produtos comprados nos meses
@param client Código do cliente ao qual as quantidades estão relacionadas
*/
void tableView(int**, char*);

/**
@brief Função responsável por mostrar o resultado da query 1 ao utilizador
@param clients_path Caminho para o ficheiro dos clients
@param products_path Caminho para o ficheiro dos produtos
@param sales_path Caminho para o ficheiro das vendas
*/
void querie1View(char*, char*, char*);

/**
@brief Função responsável por mostrar o resultado da query 2 ao utilizador
@param list Array com os produtos inicializados com uma letra inicial especifica por ordem alfabética
*/
void querie2View(char**);

/**
@brief Função responsável por mostrar o resultado da query 3 ao utilizador
@param products Array com valores totais de vendas e faturado de um certo produtos globalmente ou dividido por filial
@param int Escolha do utilizador se pretende ver os resultados globalmente ou dividido filial a filial
@param char* Código do produto ao qual as informações pertencem
*/
void querie3View(double *, int, char*);

/**
@brief Função responsável por mostrar o resultado da query 4 ao utilizador
@param products Array com produtos que nínguem comprou ordenados por ordem alfabética
@param global Escolha do utilizador se pretende ver globalmente ou separado por filiais
@param branch Número da filial escolhida
@param size Tamanho do array dos produtos
*/
void querie4View(char ***, int, int, int*, int);

/**
@brief Função responsável por mostrar o resultado da query 5 ao utilizador
@param clients Array com os clients que compraram em todas as filiais
*/
void querie5View(char**);

/**
@brief Função responsável por mostrar o resultado da query 6 ao utilizador
@param list Array com os valores totais dos clientes que que não realizaram compras e dos produtos que não foram comprados
*/
void querie6View(int*);

/**
@brief Função responsável por mostrar o resultado da query 7 ao utilizador
@param totals Valores totais dos produtos comprados separados por mês de um certo cliente
*/
void querie7View(int**);

/**
@brief Função responsável por mostrar o resultado da query 8 ao utilizador
@param aux Array com as totais de vendas e unidades vendidas num intervalo de meses
@param first Primeiro mês do intervalo
@param second Ultimo mês do intervalo
*/
void querie8View(Query8Aux, int, int);

/**
@brief Função responsável por mostrar o resultado da query 9 ao utilizador
@param aux Array com os clientes qe compraram certo produto nas diferentes filiais
@param type Tipo de vendas
@param page Página da lista que é para ser mostrada
*/
void querie9View(Query9Aux aux, char type, int);

/**
@brief Função responsável por mostrar o resultado da query 10 ao utilizador
@param *info Array com os produtos mais comprados por um certo cliente
@param n Tamanho do array com os produtos
@param client Cliente ao qual as informações do array estão relacionadas
@param page Página da lista que é para ser mostrada
*/
void querie10View(Info *, int , char *, int);

/**
@brief Função responsável por mostrar o resultado da query 11 ao utilizador
@param result Lista com os top n produtos mais vendidos
@param n Número de produtos a serem mostrados
@param page Página da lista qque é para ser mostrada
*/
void querie11View(Aux * , int, int);

/**
@brief Função responsável por mostrar o resultado da query 12 ao utilizador
@param list Lista com os top n produtos mais comprados por um certo cliente
@param n Número de produtos a serem mostrados
@param page Página da lista qque é para ser mostrada
*/
void querie12View(Money *, int,  char*, int);

#endif
