#ifndef ___CLIENT_CATALOG_H___
#define ___CLIENT_CATALOG_H___

#include "client.h"

typedef struct clients* Clients;

Clients initClients();

int addClient(Clients clients, char* client);

int getSizeClients(Clients clients);

int existClient (Clients clients, Client client);

void destroyClients(Clients clients);

#endif