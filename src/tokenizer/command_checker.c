
#include "minishell.h"

t_bool   command_is_valid(ENV, t_command *cmd)
{
    //No weird syntax
    if (cmd == NULL)
        return FALSE;
    return TRUE;
}