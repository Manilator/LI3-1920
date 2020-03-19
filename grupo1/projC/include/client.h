#ifndef ___CLIENT_H___
#define ___CLIENT_H___


#include <stdbool.h>

typedef struct client* Client;

bool verifyClient(char*);

Client newClient(char*);

char* getClientCode(Client);

int equalsClient(Client, Client);

void destroyClient(Client);

#endif
