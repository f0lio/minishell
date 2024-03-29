#include "minishell.h"

int	isbuiltin(char *cmd)
{
	int		i;
	int		j;
	char	**fme;

	i = -1;
	j = FALSE;
	fme = ft_split(BUILTINS, ':');
	while (fme[++i])
	{
		if (str_cmp(cmd, fme[i]))
			j = TRUE;
		safe_free((void **)&fme[i]);
	}
	safe_free((void **)&fme);
	return (j);
}

int	treat_exec_token(char **path, t_simpcmd scmd, char **paths)
{
	int	ret;

	if (scmd.isbuiltin)
	{
		*path = 0;
		return (0);
	}
	ret = search_path(scmd.tokarr[0]);
	if (ret == 1)
		*path = search_cmd(scmd.tokarr[0], paths);
	else
		*path = str_dup(scmd.tokarr[0]);
	if (!*path)
	{
		ret = 127;
		print_er(scmd.tokarr[0], ERR_CMD_NOT_FOUND, 0, 0);
	}
	if (ret == 127)
		return (ret);
	return (0);
}

void	scmd_loop(t_command *command, t_env *env, char *envv)
{
	int		i;
	char	*path;
	char	**paths;

	i = -1;
	path = NULL;
	paths = ft_split(envv, ':');
	while (++i <= command->pipe_count)
	{
		if (!command->scmd[i].tokarr[0])
			continue ;
		command->scmd[i].isbuiltin = isbuiltin(command->scmd[i].tokarr[0]);
		env->exitcode = treat_exec_token(&path, command->scmd[i], paths);
		if (!env->exitcode)
		{
			redirect_stdio(command, i);
			if (!command->scmd[i].isbuiltin)
				exec(path, command, i, env->envll);
			else
				execbuiltins(&command->scmd[i], command, env);
		}
		safe_free((void **)&path);
	}
	closefdfree(command, &paths);
}

void	redirect_commands(t_command *command, t_env *env)
{
	int		i;
	int		j;
	char	*envv;

	search_pipes(command);
	command->tokarr = token_to_arr(command->tokens, command->tokens_count);
	if (pipe_this(command))
		return ;
	envv = get_env(env, "PATH");
	scmd_loop(command, env, envv);
	i = -1;
	while (++i <= command->pipe_count)
	{
		j = 0;
		waitpid(command->scmd[i].pid, &j, 0);
		unlink(command->scmd[i].heredoc);
	}
	if (j)
	{
		env->exitcode = WEXITSTATUS(j);
		if (WIFSIGNALED(j))
			env->exitcode = WTERMSIG(j) + 128;
	}
	set_exitcode(env);
}

void	cast_cmd(t_command *commands, int cmdcout, t_env *env)
{
	int	i;

	i = 0;
	while (i < cmdcout)
		redirect_commands(&commands[i++], env);
}
