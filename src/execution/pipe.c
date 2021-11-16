#include "minishell.h"

char	**scmd_tokarr(t_command *command, int pipe_num)
{
	int		i;
	int		j;
	int		k;
	char	**arr;

	i = 0;
	j = 0;
	k = command->pipe_location[pipe_num];
	if (k < 0)
		k = command->tokens_count;
	if (pipe_num)
		j = command->pipe_location[pipe_num - 1] + 1;
	arr = malloc(sizeof(char *) * (k - j + 1));
	arr[k - j] = 0;
	while (i < k - j)
	{
		arr[i] = command->tokarr[i + j];
		i++;
	}
	return (arr);
}

void	scmd_tokarr_loop(t_command *command)
{
	int	i;

	i = 0;
	command->scmd = malloc(sizeof(t_simpcmd) * (command->pipe_count + 2));
	command->scmd[command->pipe_count + 1].tokarr = 0;
	if (!command->pipe_count)
		command->scmd[0].tokarr = command->tokarr;
	while (i <= command->pipe_count)
	{
		command->scmd[i].tokarr = scmd_tokarr(command, i);
		initscmd(&command->scmd[i]);
		i++;
	}
	command->origio[0] = dup(STDIN_FILENO);
	command->origio[1] = dup(STDOUT_FILENO);
}

int	norm_topple(t_command *command, int i, int j)
{
	int	ret;

	if (command->tokens[!!i * (command->pipe_location[i - 1] + 1) + j]->quoted)
		return (0);
	if (str_cmp(command->scmd[i].tokarr[j], ">")
		|| str_cmp(command->scmd[i].tokarr[j], ">>"))
		ret = rediro(command->scmd[i].tokarr[j + 1], j, &command->scmd[i]);
	else if (str_cmp(command->scmd[i].tokarr[j], "<"))
		ret = rediri(command->scmd[i].tokarr[j + 1], &command->scmd[i]);
	else if (str_cmp(command->scmd[i].tokarr[j], "<<"))
		ret = heredoc(command->scmd[i].tokarr[j + 1], &command->scmd[i]);
	else
		return (0);
	command->scmd[i].tokarr[j] = 0;
	if (ret)
		return (-1);
	return (1);
}

int	pipe_this(t_command *command)
{
	int		i;
	int		j;
	int		ret;
	char	*tok;
	t_token	*tk;

	scmd_tokarr_loop(command);
	i = -1;
	while (++i <= command->pipe_count)
	{
		command->scmd[i].stdio[0] = dup(command->origio[0]);
		command->scmd[i].stdio[1] = dup(command->origio[1]);
		pipe(command->scmd[i].pipe);
		j = -1;
		while (command->scmd[i].tokarr[++j])
		{
			ret = norm_topple(command, i, j);
			if (ret)
				j++;
			if (ret < 0)
				return (1);
		}
	}
	return (0);
}
