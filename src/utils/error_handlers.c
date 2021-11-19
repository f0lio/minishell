#include "minishell.h"

BOOL	raise_error(t_env *env, char *msg)
{
	(void)env;
	fput_str("Error\n", 2);
	fput_str(msg, 2);
	fput_char('\n', 2);
	return (-1);
}
