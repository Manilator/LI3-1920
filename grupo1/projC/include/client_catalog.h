#ifndef ___CLIENT_CATALOG_H___
#define ___CLIENT_CATALOG_H___

#include "client.h"

#include <glib.h>

typedef struct clients* Clients;

Clients initClients();

int addClient(Clients, char*);

int getSizeClients(Clients);

int existClient (Clients, Client);

int existClientCode (Clients, char*);

void destroyClients(Clients);

int getNumberClientsNotUsed(Clients, GHashTable *);

void fillClientsHT(Clients, GHashTable *);

#endif
