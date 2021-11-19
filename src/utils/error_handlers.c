#include "minishell.h"

BOOL    raise_error(ENV, char *msg)
{
    fput_str("Error\n", 2);
    fput_str(msg, 2);
    fput_char('\n', 2);
    //Free memory
    return (-1);
}
