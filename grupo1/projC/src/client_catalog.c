#include <glib.h>
#include <string.h>

#include "client_catalog.h"

struct clients
{
    GHashTable* clients;
};

Clients initClients() {
    Clients clients;
    clients = g_malloc(sizeof(struct clients));
    clients->clients = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, g_free);
    return clients;
}

int addClient(Clients clients, char* client) {
    char* client_code = strdup(client);
    strtok(client_code, "\r\n");
    if(verifyClient(client_code) && !g_hash_table_contains(clients->clients, client_code)) {
        /* Try/Except missing*/
        g_hash_table_insert(clients->clients, (char*)client_code, (gpointer)newClient(client_code));
        return 1;
    }
    g_free(client_code);
    return 0;
}

int existClient (Clients clients, Client client) {
    char* _temp;
    _temp = getClientCode(client);
    if (g_hash_table_contains(clients->clients, _temp)) {
        g_free(_temp);
        return 1;
    }
    g_free(_temp);
    return 0;
}

int getSizeClients(Clients clients) {
    return g_hash_table_size(clients->clients);
}

void destroyClients(Clients clients) {
    g_hash_table_destroy (clients->clients);
    g_free(clients);
}
