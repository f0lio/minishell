
#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h> //tmp?
# include <unistd.h>
# include <stdlib.h>
# include "macros.h"
# include "structs.h"
# include "functions.h"

//tempo
# include "../dbg/my_dbg.h" 

// it's tempo', I promise.
static
char *builtins[] =
{
    "echo",
    "cd",
    "pwd",
    "export",
    "unset",
    "env",
    "exit"
};

#endif
