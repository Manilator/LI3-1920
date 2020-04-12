#include "client_catalog.h"
#include "constants.h"

#include <string.h>
#include <glib.h>

struct clients
{
    GHashTable* clients; /**< Códigos de clientes e a sua estrutura */
};

Clients initClients() {
    Clients clients;
    clients = g_malloc(sizeof(struct clients));
    clients->clients = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, g_free);
    return clients;
}

void fillClientsHT(Clients clients, GHashTable * clients_ht){
    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init (&iter, clients->clients);
    while (g_hash_table_iter_next (&iter, &key, &value)){
        g_hash_table_insert(clients_ht, (char*)key, (char*)key);
    }
}

int addClient(Clients clients, char* client) {
    char* client_code = strdup(client);
    strtok(client_code, "\r\n");
    if(verifyClient(client_code) && !g_hash_table_contains(clients->clients, client_code)) {
        /* Try/Except missing*/
        g_hash_table_insert(clients->clients, (char*)client_code, (gpointer)newClient(client_code));
        return ONE;
    }
    g_free(client_code);
    return ZERO;
}

int existClient (Clients clients, Client client) {
    char* _temp;
    _temp = getClientCode(client);
    if (g_hash_table_contains(clients->clients, _temp)) {
        g_free(_temp);
        return ONE;
    }
    g_free(_temp);
    return ZERO;
}

int existClientCode (Clients clients, char* client_code) {
    if (g_hash_table_contains(clients->clients, client_code)) {
        return ONE;
    }
    return ZERO;
}


int getSizeClients(Clients clients) {
    return g_hash_table_size(clients->clients);
}

int getNumberClientsNotUsed(Clients client_catalog, GHashTable * clients_used){
    return getSizeClients(client_catalog) - g_hash_table_size(clients_used);
}

void destroyClients(Clients clients) {
    g_hash_table_destroy (clients->clients);
    g_free(clients);
}
