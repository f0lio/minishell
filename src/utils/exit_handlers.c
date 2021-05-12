
#include "minishell.h"

void    exit_program(ENV, int exit_code)
{
    //free memory
    exit(exit_code);
}


void    destroy_env(ENV)
{
    //Recursively, free all t_env properties.
}
