#include "minishell.h"

t_bool    raise_error(ENV, char *msg)
{
    put_str("Error\n");
    put_str(msg);
    put_char('\n');
    //Free memory
    return (-1);
}
