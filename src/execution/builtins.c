#include "minishell.h"

void	echo(t_simpcmd *scmd)
{
	int	n;
	int	i;

	n = str_cmp(scmd->tokarr[1], "-n");
	i = 0;
	while (scmd->tokarr[++i + n])
	{
		write(1, scmd->tokarr[i + n], str_len(scmd->tokarr[i + n]));
		// printf("%s\n", scmd->tokarr[i + n]);
		if (scmd->tokarr[i + 1 + n])
			// write(1, " ", 1);
			write(1, " ", 1);
	}
	if (!n)
		write(1, "\n", 1);
}

void	pwd(t_simpcmd *scmd)
{
	write(1, g_cwd, str_len(g_cwd));
	write(1, "\n", 1);
}

void	env(t_envvar *env)
{
	while (env)
	{
		if (env->content)
			printf("%s=%s\n", env->name, env->content);
		env = env->next;
	}
}

int		go_to_envv(t_envvar **env, char *str)
{
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

void	export(t_envvar *env, t_simpcmd *scmd)
{
	t_envvar	*start;
	int			i;

	i = 0;
	start = env;
	if (!scmd->tokarr[1])
	{
		while (env)
		{
			if (!str_cmp(env->name, "_"))
				printf("declare -x %s=\"%s\"\n", env->name, env->content);
			env = env->next;
		}
	}
	else
	{
		while (scmd->tokarr[++i])
		{
			if (!go_to_envv(&env, scmd->tokarr[i]))
				new_envv(env, scmd->tokarr[i]);
			else
				reassign_envv(env, scmd->tokarr[i]);
			env = start;
		}
	}
}

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
	// while (env)
	// {
	// 	printf("%s=%s\n", env->name, env->content);
	// 	env = env->next;
	// }
	j = 0;
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
	// printf("#######\n");
	// while (env)
	// {
	// 	printf("%s=%s\n", env->name, env->content);
	// 	env = env->next;
	// }
}

void	cd(t_simpcmd *scmd)
{
	char	*path;
	if (!scmd->tokarr[1])
		path = getenv("HOME");
	else
		path = scmd->tokarr[1];
	if (chdir(path))
		printf("%s: %s: %s: %s\n",SHELL_NAME, scmd->tokarr[0], scmd->tokarr[1], strerror(errno));
	else
		g_cwd = getcwd(0, 0);
}
