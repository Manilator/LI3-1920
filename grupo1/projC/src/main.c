/**
@file main.c
\brief Ficheiro principal.
*/

#include "args.h"
#include "controller.h"

/**
  \brief Função principal.
  */
int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        startController();
    }
    else if (argc > 1)
    {
        startInput(argc-1, argv+1);
    }
        
    return 0;
}
