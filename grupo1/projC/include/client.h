#ifndef ___CLIENT_H___
#define ___CLIENT_H___


#include <stdbool.h>

typedef struct client* Client;

bool verifyClient(char *client);

Client newClient(char* client);

char* getClientCode(Client client);

int equalsClient(Client a, Client b);

void destroyClient(Client client);

#endif