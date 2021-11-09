
#include "minishell.h"

void handle_backslash(
	t_env *env, const char *input, char **new_input, int *i)
{
	char *va;

	if (input[*i] == 0)
		raise_error(env, ERR_SYNTAX);
	va = sub_str(input, *i, *i+ 1);
	printf("@@[%s]\n", va);
	if (va)
	{
		str_fjoin(new_input, va);
		free(va);
	}
	(*i)++;
}
