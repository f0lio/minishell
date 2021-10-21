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

char	*search_cmd(char *cmd)
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
	while (ret && g_paths[++i])
	{
		free(str);
		str = str_join(g_paths[i], cmd);
		ret = stat(str, &buf);
	}
	if (!g_paths[i])
	{
		free(str);
		return (NULL);
	}
	return (str);
}

int		search_path(char *path)
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
		printf("%s: %s: %s\n",SHELL_NAME, path, strerror(errno));
		return (127);
	}
	printf("%d, %d, %d, %d\n", ret, buf.st_mode, S_IXUSR, buf.st_mode & S_IXUSR);
	return (0);
}

int		treat_exec_token(char **path, t_simpcmd scmd)
{
	int		ret;

	ret = search_path(scmd.tokarr[0]);
	if (ret == 1)
		*path = search_cmd(scmd.tokarr[0]);
	else
		*path = str_dup(scmd.tokarr[0]);
	if (!*path)
		printf("%s: %s: %s\n", SHELL_NAME, scmd.tokarr[0], ERR_CMD_NOT_FOUND);
	if (!*path || ret == 127)
		return (ret);
	return (0);
}

void	closeallpipes(t_simpcmd *scmd, int ppcout)
{
	int	j;

	j = -1;
	while (++j <= ppcout)
	{
		close(scmd[j].pipe[0]);
		close(scmd[j].pipe[1]);
	}
}

void	free_closepipes(char **path, t_simpcmd *scmd, int ppcout)
{
	safe_free((void **)path);
	closeallpipes(scmd, ppcout);
}

void	redirect_stdio(t_simpcmd *scmd, int i, int ppcout)
{
	// echo hi | tr 'x'
	if (i)
		dup2(scmd[i].pipe[0], STDIN_FILENO);
	if (i != ppcout)
		dup2(scmd[i + 1].pipe[1], STDOUT_FILENO);
}

void	exec(char *path, t_command *command, int i)
{
	command->scmd[i].pid = fork();
	if (!command->scmd[i].pid)
	{
		redirect_stdio(command->scmd, i, command->pipe_count);
		closeallpipes(command->scmd, command->pipe_count);
		execve(path, command->scmd[i].tokarr, 0);
		printf("WHAT THE FUCK HAPPENED\n");
		exit(1);
	}
}

void	redirect_commands(t_command *command)
{
	int		i;
	char	*path;

	i = -1;
	path = 0;
	search_pipes(command);
	// printf("ppcout%d\n", command->pipe_count);
	// for (int i = 0; i < command->pipe_count; i++)
	// 	printf("pploc %d\n",command->pipe_location[i]);
	command->tokarr = token_to_arr(command->tokens, command->tokens_count);
	pipe_this(command);
	while (++i <= command->pipe_count)
		pipe(command->scmd[i].pipe);
	i = -1;
	while (++i <= command->pipe_count)
	{
		if (!treat_exec_token(&path, command->scmd[i]))
			// return (free_closepipes(&path, command->scmd, command->pipe_count));
			exec(path, command, i);
		safe_free((void **)&path);
	}
	closeallpipes(command->scmd, command->pipe_count);
	i = -1;
	while (++i <= command->pipe_count)
		waitpid(command->scmd[i].pid, NULL, 0);
}

void	cast_cmd(t_command **commands, int cmdcout)
{
	int	i;

	i = 0;
	while (i < cmdcout)
		redirect_commands(commands[i++]);
}
