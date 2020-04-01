#ifndef ___CLIENT_CATALOG_H___
#define ___CLIENT_CATALOG_H___

#include "client.h"

typedef struct clients* Clients;

Clients initClients();

int addClient(Clients, char*);

int getSizeClients(Clients);

int existClient (Clients, Client);

void destroyClients(Clients);

int getNumberClientsNotUsed(Clients, GHashTable *);

#endif
