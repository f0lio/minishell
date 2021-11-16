#include "minishell.h"

void	rm_link_iter(t_envvar **env, t_envvar **start)
{
	t_envvar	*tmp;

	if ((*env)->prev)
		(*env)->prev->next = (*env)->next;
	else
		*start = (*env)->next;
	if ((*env)->next)
		(*env)->next->prev = (*env)->prev;
	safe_free((void **)&((*env)->name));
	safe_free((void **)&((*env)->content));
	tmp = (*env)->next;
	safe_free((void **)env);
	*env = tmp;
}

void	unset(t_envvar *env, t_simpcmd *scmd)
{
	int			j;
	t_envvar	*start;

	start = env;
	j = 0;
	if (!env)
		return ;
	while (scmd->tokarr[++j])
	{
		env = start;
		while (env)
		{
			if (str_cmp(env->name, scmd->tokarr[j]))
				rm_link_iter(&env, &start);
			else
				env = env->next;
		}
	}
	env = start;
}
