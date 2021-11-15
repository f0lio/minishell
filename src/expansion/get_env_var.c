

#include "minishell.h"

char	*get_env(t_env *env, char *var_name)
{
	t_envvar	*it;

	it = env->envll;
	while (it)
		if (str_cmp(var_name,  it->name))
			return (str_dup(it->content));
		else
			it = it->next;
	return NULL;
}
