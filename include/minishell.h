#ifndef __MINISHELL_H__
# define __MINISHELL_H__

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include "macros.h"
# include "structs.h"
# include "functions.h"
# include "../dbg/my_dbg.h"
# include "parser.h"
# include "utils.h"

static char *builtins[] = {"echo", "cd", "pwd", "export", "unset", "env", "exit"};

#endif
