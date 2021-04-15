#ifndef __MINISHELL_H__
# define __MINISHELL_H__

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include "macros.h"
# include "structs.h"
# include "functions.h"

//tempo
# include "../dbg/my_dbg.h" 

static char *builtins[] = {"echo", "cd", "pwd", "export", "unset", "env", "exit"};

#endif
