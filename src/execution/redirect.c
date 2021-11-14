#include "minishell.h"

char	**token_to_arr(t_token **tokens, int tokcout)
{
	int		i;
	char	**arr;

	i = 0;
	arr = malloc(sizeof(char *) * (tokcout + 1));
	while (i < tokcout)
	{
		arr[i] = tokens[i]->tok;
		i++;
	}
	arr[i] = 0;
	return (arr);
}

char	*search_cmd(char *cmd, char **paths)
{
	char		*str;
	int			i;
	struct stat	buf;
	int			ret;

	i = -1;
	ret = 1;
	str = malloc(sizeof(char) * 2);
	str[0] = '/';
	str[1] = 0;
	cmd = str_join(str, cmd);
	// probably leaks idk
	while (ret && paths && paths[++i])
	{
		safe_free((void **)&str);
		str = str_join(paths[i], cmd);
		ret = stat(str, &buf);
	}
	safe_free((void **)&cmd);
	if (!paths || !paths[i])
	{
		safe_free((void **)&str);
		return (NULL);
	}
	return (str);
}

int	search_path(char *path)
{
	int			i;
	int			j;
	int			ret;
	struct stat	buf;

	i = 0;
	j = -1;
	while (path[i])
	{
		if (path[i] == '/')
			j = i;
		i++;
	}
	if (j > -1)
		path[j] = 0;
	else
		return (1);
	path[j] = '/';
	ret = stat(path, &buf);
	if (!ret && !(buf.st_mode & S_IXUSR))
		errno = EACCES;
	if (!ret && buf.st_mode & S_IFDIR)
		errno = EISDIR;
	if (ret || !(buf.st_mode & S_IXUSR) || (buf.st_mode & S_IFDIR))
	{
		printf("%s: %s: %s\n", SHELL_NAME, path, strerror(errno));
		return (127);
	}
	// printf("%d, %d, %d, %d\n", ret, buf.st_mode,
	// S_IXUSR, buf.st_mode & S_IXUSR);
	return (0);
}

int	isbuiltin(char *cmd)
{
	int	i;

	i = -1;
	while (BUILTINS[++i])
		if (str_cmp(cmd, BUILTINS[i]))
			return (TRUE);
	return (FALSE);
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
		printf("%s: %s: %s\n", SHELL_NAME, scmd.tokarr[0], ERR_CMD_NOT_FOUND);
	if (!*path || ret == 127)
		return (ret);
	return (0);
}

void	closeallpipes(t_command *command)
{
	int	j;

	j = -1;
	while (++j <= command->pipe_count)
	{
		close(command->scmd[j].pipe[0]);
		close(command->scmd[j].pipe[1]);
		close(command->scmd[j].stdio[0]);
		close(command->scmd[j].stdio[1]);
	}
	close(command->origio[0]);
	close(command->origio[1]);
}

void	closefdfree(t_command *command, char ***paths)
{
	int	i;

	dup2(command->origio[0], STDIN_FILENO);
	dup2(command->origio[1], STDOUT_FILENO);
	closeallpipes(command);
	i = -1;
	while (*paths && (*paths)[++i])
	{
		// printf("%X\n", (int)((*paths)[i]));
		safe_free((void **)(&((*paths)[i])));
		// printf("%X\n", (int)((*paths)[i]));
	}
	// printf("%X\n", (int)*paths);
	safe_free((void **)paths);
	// printf("%X\n", (int)*paths);
}

void	redirect_stdio(t_command *command, int i)
{
	dup2(command->scmd[i].stdio[0], STDIN_FILENO);
	dup2(command->scmd[i].stdio[1], STDOUT_FILENO);
	if (i)
		dup2(command->scmd[i].pipe[0], STDIN_FILENO);
	if (i != command->pipe_count)
		dup2(command->scmd[i + 1].pipe[1], STDOUT_FILENO);
}

void	exec(char *path, t_command *command, int i)
{
	command->scmd[i].pid = fork();
	if (!command->scmd[i].pid)
	{
		closeallpipes(command);
		execve(path, command->scmd[i].tokarr, 0);
		printf("WHAT THE FUCK HAPPENED\n");
		exit(1);
	}
}

int	execbuiltins(t_simpcmd *scmd, t_command *command, t_env *en)
{

	// closeallpipes(command);
	// printf("builtin not yet built in\n");
	if (str_cmp(scmd->tokarr[0], "echo"))
		echo(scmd);
	if (str_cmp(scmd->tokarr[0], "cd"))
		cd(scmd);
	if (str_cmp(scmd->tokarr[0], "pwd"))
		pwd(scmd);
	if (str_cmp(scmd->tokarr[0], "env"))
		env(en->envll);
	if (str_cmp(scmd->tokarr[0], "unset"))
		unset(en->envll, scmd);
	if (str_cmp(scmd->tokarr[0], "export"))
		export(en->envll, scmd);
	// if (str_cmp(scmd->tokarr[0], "exit"))
	// 	my_exit();
	return (1);
}

void	redirect_commands(t_command *command, t_env *env)
{
	int		i;
	char	*path;
	char	**paths;
	char	*envv;

	path = 0;
	search_pipes(command);
	// printf("ppcout%d\n", command->pipe_count);
	// for (int i = 0; i < command->pipe_count; i++)
	// 	printf("pploc %d\n",command->pipe_location[i]);
	command->tokarr = token_to_arr(command->tokens, command->tokens_count);
	pipe_this(command);
	envv = getenv("PATH");
	paths = ft_split(envv, ':');
	i = -1;
	while (++i <= command->pipe_count)
	{
		command->scmd[i].isbuiltin = isbuiltin(command->scmd[i].tokarr[0]);
		if (!treat_exec_token(&path, command->scmd[i], paths))
		{
			redirect_stdio(command, i);
			if (!command->scmd[i].isbuiltin)
				exec(path, command, i);
			else
				execbuiltins(&command->scmd[i], command, env);
		}
		safe_free((void **)&path);
	}
	closefdfree(command, &paths);
	i = -1;
	while (++i <= command->pipe_count)
		waitpid(command->scmd[i].pid, NULL, 0);
}

void	cast_cmd(t_command **commands, int cmdcout, t_env *env)
{
	int	i;

	i = 0;
	while (i < cmdcout)
		redirect_commands(commands[i++], env);
}
