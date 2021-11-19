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

int	check_valid_id(char *str, int *exitcode)
{
	int		len;

	len = 0;
	while (is_alphatiriblwit(str[len], len) && str[len])
		len++;
	if (!len || (str[len] && !is_alphatiriblwit(str[len], len)))
	{
		*exitcode = 1;
		print_er("unset", str, ERR_INVALID_ENVV, 0);
		return (1);
	}
	return (0);
}

void	unset(t_envvar *env, t_simpcmd *scmd, int *exitcode, int pipe)
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
		if (check_valid_id(scmd->tokarr[j], exitcode))
			continue ;
		while (env)
		{
			if (str_cmp(env->name, scmd->tokarr[j]) && !pipe)
				rm_link_iter(&env, &start);
			else
				env = env->next;
		}
	}
	env = start;
}
