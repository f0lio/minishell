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

void	env(char **env_vars)
{
	int		i;

	i = -1;
	while (env_vars[++i])
	{
		write(1, env_vars[i], str_len(env_vars[i]));
		write(1, "\n", 1);
	}
}

// placeholder export
void	export(char ***env_vars, t_simpcmd *scmd)
{
	int		i;

	i = -1;
	if (!scmd->tokarr[1])
	{
		while ((*env_vars)[++i])
			if (!str_ncmp("_=", (*env_vars)[i], 2))
			{
				write(1, (*env_vars)[i], str_len((*env_vars)[i]));
				write(1, "\n", 1);
			}
	}
	else
	{
		i = 0;
		while (scmd->tokarr[++i])
		{

			if (!scmd->tokarr[i][0])
				// bash: export: `': not a valid identifier
				;
			else if (!is_included('=',scmd->tokarr[i]))
				;
			else
				;
		}
	}
	// int		i;
	// char	**new_var;

	// i = 0;
	// while (*env_vars[i])
	// 	i++;
	// new_var = malloc(sizeof(char *) * (i + 2));
	// new_var[i + 1] = 0;
	// i = -1;
	// while (*env_vars[++i])
	// 	new_var[i] = *env_vars[i];
	// new_var[i] = scmd;
}

void	unset(char ***envv, t_simpcmd *scmd)
{
	int	i;
	int	j;

	j = -1;
	while (scmd->tokarr[++j])
	{
		i = -1;
		while (*envv[++i])
			if (str_ncmp(*envv[i], scmd->tokarr[j], str_len(scmd->tokarr[j])))
			{
				*envv = arrdup(envv, i, 1, 0);

			}
	}
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
