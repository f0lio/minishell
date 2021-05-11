#ifndef __MINISHELL_H__
# define __MINISHELL_H__

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include "macros.h"
# include "structs.h"
# include "functions.h"

//tempo
# include "../dbg/my_dbg.h" 
//dbg
# define ITER(list) t_node *iter; iter = list;
# define NEXT(iter) iter = iter->next;


static char *builtins[] = {"echo", "cd", "pwd", "export", "unset", "env", "exit"};

#endif
