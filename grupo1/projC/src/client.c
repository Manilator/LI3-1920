#include "client.h"

#include <stdlib.h>
#include <stdio.h>

struct client
{
    char letter; /**< Primeira letra no código de cliente */
    int number; /**< Número presente no código de cliente */
};

char* getClientCode(Client client) {
    char* code = malloc(sizeof(char)*8);
    sprintf(code, "%c%d",client->letter,client->number);
    return code;
}

bool verifyClient(char *client) {
    int number = atoi(client+1);
    char letter = client[0];
    if( (number >= 1000 && number <= 5000) &&
            (letter >= 'A' && letter <= 'Z') ) {
                return true;
            }
    return false;
}

Client newClient(char* client) {
    Client new = malloc(sizeof(struct client));
    new->letter = client[0];
    new->number = atoi(client+1);
    return new;
}

int equalsClient(Client a, Client b) {
    return (a->letter == b->letter && a->number == b->number);
}

void destroyClient(Client client) {
    free(client);
}
