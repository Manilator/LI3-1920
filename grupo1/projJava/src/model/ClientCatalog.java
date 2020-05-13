package model;

import java.util.Hashtable;

public class ClientCatalog {

    private final Hashtable<String,Client> clients;

    public ClientCatalog(){
        clients = new Hashtable<>();
    }

    public void insertClient(String clientCode){
        this.clients.put(clientCode, new Client(clientCode));
    }
/*
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
    }*/

    public int getSize() {
        return this.clients.size();
    }

    public Hashtable<String, Client> getClients() {
        return (Hashtable<String, Client>) this.clients.clone();
    }
}
