#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <dirent.h>
# include <stdlib.h>
# include <signal.h>
# include <string.h>
# include <errno.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "macros.h"
# include "structs.h"
# include "functions.h"

char	*g_cwd;
int g_sig;
#endif
