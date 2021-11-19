#include "minishell.h"

void	pwd(t_simpcmd *scmd)
{
	(void)scmd;
	write(1, g_cwd, str_len(g_cwd));
	write(1, "\n", 1);
}

void	env(t_envvar *env)
{
	while (env)
	{
		if (env->content && !str_cmp(env->name, "?"))
		{
			put_str(env->name);
			put_char('=');
			put_str(env->content);
			put_char('\n');
		}
		env = env->next;
	}
}

int	cd(t_simpcmd *scmd)
{
	char	*path;

	if (!scmd->tokarr[1])
		path = getenv("HOME");
	else
		path = scmd->tokarr[1];
	if (chdir(path))
	{
		print_err(scmd->tokarr[0], scmd->tokarr[1], strerror(errno), 0);
		return (1);
	}
	else
	{
		safe_free((void **)&g_cwd);
		g_cwd = getcwd(0, 0);
	}
	return (0);
}

int	check_syntax(t_simpcmd *scmd, int *exitcode)
{
	int	i;

	i = 0;
	while (scmd->tokarr[1][i] == ' ')
		i++;
	if (scmd->tokarr[1][i] == '-' || scmd->tokarr[1][i] == '+')
		i++;
	while (scmd->tokarr[1][i] <= '9' && scmd->tokarr[1][i] >= '0')
		i++;
	if (scmd->tokarr[1][i] || (i && (scmd->tokarr[1][i - 1] == '-'
		|| scmd->tokarr[1][i - 1] == '+')))
	{
		print_err("exit", scmd->tokarr[1], ERR_NUM_WRONG, 0);
		*exitcode = 255;
	}
	else
		*exitcode = (unsigned char)my_atoi(scmd->tokarr[1]);
	if (scmd->tokarr[2] && !(*exitcode))
	{
		print_err("exit", ERR_TOO_MANY_ARGS, 0, 0);
		return (255);
	}
	return (0);
}

int	my_exit(t_env *env, t_simpcmd *scmd, int pipenum, int exitcode)
{
	char	*not_trma;

	if (scmd->tokarr[1])
	{
		if (check_syntax(scmd, &exitcode))
			return (255);
	}
	else
	{
		not_trma = get_env(env, "?");
		exitcode = my_atoi(not_trma);
		safe_free((void **)&not_trma);
	}
	if (!pipenum)
	{
		destroy_env(env);
		exit(exitcode);
	}
	else
		return (exitcode);
	return (0);
}
