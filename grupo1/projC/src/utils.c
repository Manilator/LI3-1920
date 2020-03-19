#include "utils.h"

char* cleanString(char* string){
    int i=0;
    while(string[i] != '\r' && string[i] != '\n'){
        i++;
    }
    string[i] = '\0';
    return string;
}
