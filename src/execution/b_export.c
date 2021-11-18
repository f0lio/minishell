#include "minishell.h"

int	go_to_envv(t_envvar **env, char *str, int *exitcode)
{
	int		len;

	len = 0;
	while ((str[len] != '=') && is_alphatiriblwit(str[len], len) && str[len])
		len++;
	if (!len || (str[len] && !is_alphatiriblwit(str[len], len)
			&& (str[len] != '=')))
	{
		*exitcode = 1;
		print_err("export", str, ERR_INVALID_ENVV, 0);
		return (-1);
	}
	while ((*env)->next)
	{
		if (str_ncmp((*env)->name, str, str_len((*env)->name)))
			return (TRUE);
		*env = (*env)->next;
	}
	if (str_ncmp((*env)->name, str, str_len((*env)->name)))
		return (TRUE);
	return (FALSE);
}

void	new_envv(t_envvar *env, char *str)
{
	env->next = str_to_envv(str);
	if (!env->next)
		return ;
	env->next->prev = env;
	env = env->next;
	env->next = 0;
}

void	reassign_envv(t_envvar *env, char *str)
{
	char	**arr;

	arr = strcut(str, '=');
	safe_free((void **)&arr[0]);
	if (arr[1])
	{
		safe_free((void **)&env->content);
		env->content = arr[1];
	}
	safe_free((void **)&arr);
}

void	print_envp(t_envvar *env)
{
	while (env)
	{
		if (!str_cmp(env->name, "_") && !str_cmp(env->name, "?"))
		{
			put_str("declare -x ");
			put_str(env->name);
			if (env->content)
			{
				put_str("=\"");
				put_str(env->content);
				put_char('\"');
			}
			put_char('\n');
		}
		env = env->next;
	}
}

void	exportt(t_envvar *env, t_simpcmd *scmd, int *exitcode)
{
	t_envvar	*start;
	int			i;
	int			j;

	i = 0;
	start = env;
	if (!env)
		return ;
	if (!scmd->tokarr[1])
		print_envp(env);
	else
	{
		while (scmd->tokarr[++i])
		{
			if (str_cmp(scmd->tokarr[i], "?"))
				continue ;
			j = go_to_envv(&env, scmd->tokarr[i], exitcode);
			if (!j)
				new_envv(env, scmd->tokarr[i]);
			else if (j > 0)
				reassign_envv(env, scmd->tokarr[i]);
			env = start;
		}
	}
}
