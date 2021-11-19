#include "minishell.h"

void	pwd(t_env *env)
{
	write(1, env->cwd, str_len(env->cwd));
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

int	cd(t_simpcmd *scmd, t_env *env)
{
	char		*path;
	struct stat	buf;

	if (!scmd->tokarr[1])
	{
		path = get_env(env, "HOME");
		if (!path)
			return (print_er(scmd->tokarr[0], scmd->tokarr[1], ERR_N_HOME, 0));
	}
	else
		path = scmd->tokarr[1];
	if (env->commands->pipe_count)
	{
		if (stat(path, &buf) || !S_ISDIR(buf.st_mode))
			print_er(scmd->tokarr[0], scmd->tokarr[1], strerror(errno), 0);
		return (stat(path, &buf) || !S_ISDIR(buf.st_mode));
	}
	if (chdir(path))
		return (print_er(scmd->tokarr[0], scmd->tokarr[1], strerror(errno), 0));
	else
	{
		safe_free((void **)&env->cwd);
		env->cwd = getcwd(0, 0);
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
		print_er("exit", scmd->tokarr[1], ERR_NUM_WRONG, 0);
		*exitcode = 255;
	}
	else
		*exitcode = (unsigned char)my_atoi(scmd->tokarr[1]);
	if (scmd->tokarr[2] && !(*exitcode))
	{
		print_er("exit", ERR_TOO_MANY_ARGS, 0, 0);
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
