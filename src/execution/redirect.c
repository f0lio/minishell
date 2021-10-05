#include "minishell.h"

void	cast_cmd(t_command **commands, int cmdcout)
{
	int	i;

	i = 0;
	while (i < cmdcout)
		redirect_commands(commands[i++]);
}

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

void	exec(t_command *command, char *path)
{
	pid_t	pid;

	pid = fork();
	if (!pid)
		execve(path, token_to_arr(command->tokens, command->tokens_count), 0);
	else
		wait(NULL);
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
	while (ret && paths[++i])
	{
		free(str);
		str = str_join(paths[i], cmd);
		ret = stat(str, &buf);
		// printf("%s\n", str);
		// if (ret)
		// 	printf("%s\n", strerror(errno));
	}
	if (!paths[i])
	{
		free(str);
		return (NULL);
	}
	return (str);
}

void	redirect_commands(t_command *command)
{
	char	*envv;
	char	*path;
	char	**paths;

	envv = getenv("PATH");
	// todo: piping
	if (!path)
	// idk what to do when no $PATH
		return ;
	paths = ft_split(envv, ':');
	path = search_cmd(command->tokens[0]->tok, paths);
	if (path)
		exec(command, path);
	else
		printf("command not found\n");
}
