#include "minishell.h"

void	destroy_env_vars(t_envvar **vars)
{
	t_envvar	*it;
	t_envvar	*p;

	if (*vars == NULL)
		return ;
	it = *vars;
	while (it->prev)
		it = it->prev;
	while (it)
	{
		safe_free((void **)&(it->content));
		safe_free((void **)&(it->name));
		p = it->next;
		safe_free((void **)&it);
		it = p;
	}
}

void	destroy_env(t_env *env)
{
	reset_data(env);
	destroy_env_vars(&env->envll);
}
