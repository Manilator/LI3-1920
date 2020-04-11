/**
@file client_catalog.h
\brief Módulo de tratamentos do catálogo de clientes
*/

#ifndef ___CLIENT_CATALOG_H___
#define ___CLIENT_CATALOG_H___

#include "client.h"

#include <glib.h>

typedef struct clients* Clients;

/**
@brief Inicia a estrutura de catálogo de clientes
@return Clients estrutura inicializada
*/
Clients initClients();

/**
@brief Adiciona um cliente ao catálogo de clientes
@param clients Catálogo de clientes ao qual vai ser adicionado o novo cliente
@param client Cliente a ser adicionado ao catálogo de clientes
@return int Verificação da inserção
*/
int addClient(Clients, char*);

/**
@brief Calcula o número de clientes que existe no catálogo
@param clients Catálogo de clientes
@return int Número de clientes existentes no catálogo
*/
int getSizeClients(Clients);

/**
@brief Verifica se existe um cliente no catálogo
@param clients Catálogo de clientes
@param client Cliente a ser consultado
@return int Verificação da procura
*/
int existClient (Clients, Client);

/**
@brief Verifica se existe um código de cliente no catálogo
@param clients Catálogo de clientes
@param client_code Código de cliente
@return int Verificação da procura
*/
int existClientCode (Clients, char*);

/**
@brief Destroi o catálogo de clientes
@param clients Catálogo de clientes
*/
void destroyClients(Clients);

/**
@brief Devolve o número de clientes não utilizados
@param client_catalog Estrutura de clientes
@param clients_used Hashtable com os códigos de clientes usados
@return int Número de clientes não usados
*/
int getNumberClientsNotUsed(Clients, GHashTable *);

/**
@brief Preencher a hashtable dada com todos os códigos de clientes
@param clients Estrutura de clientes
@param clients_ht Hashtable a ser preenchida
*/
void fillClientsHT(Clients, GHashTable *);

#endif
