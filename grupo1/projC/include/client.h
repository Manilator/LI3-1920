/**
@file client.h
\brief Módulo de tratamentos de clientes
*/

#ifndef ___CLIENT_H___
#define ___CLIENT_H___


#include <stdbool.h>

typedef struct client* Client;

/**
@brief Verifica se um código de cliente é válido
@param client Código de cliente
@return bool Verificação se o código de cliente é válido ou não
*/
bool verifyClient(char*);

/**
@brief Cria um novo Client
@param client Código de cliente
@return Client Client criado a partir do código
*/
Client newClient(char*);

/**
@brief Extrai o código de cliente a partir de um Client
@param client Client que contém as informações do cliente
@return char* Código de cliente
*/
char* getClientCode(Client);

/**
@brief Compara dois Client
@param a Primeiro cliente
@param b Segundo cliente
@return int Resultado da comparação
*/
int equalsClient(Client, Client);

/**
@brief Destroi um Client
@param client Cliente a ser destruido
*/
void destroyClient(Client);

#endif
