# include "minishell.h"

BOOL     is_pipe(t_token *t)
{
    if (!t || t->quoted)
        return FALSE;
    return (t->tok[0] == '|' && t->tok[1] == '\0');
}

int		count_pipes(t_command *command)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (i < command->tokens_count)
	{
		if (is_pipe(command->tokens[i]))
			c++;
		i++;
	}
	return (c);
}

void	search_pipes(t_command *command)
{
    int     p;
    int     j;

	p = 0;
	j = 0;
	command->pipe_count = count_pipes(command);
	command->pipe_location = malloc(sizeof(int) * (command->pipe_count + 1));
	while (j < command->tokens_count)
	{
		command->pipe_location[p] = -1;
		if (is_pipe(command->tokens[j]))
		{
			command->tokens[j]->type = TYPE_PIPE;
			command->pipe_location[p] = j;
			p++;
		}
		j++;
	}
}
char	**pipe_tokarr(t_command *command, int pipe_num)
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

void	pipe_this(t_command *command)
{
	int	i;
	int	j;

	i = 0;
	command->scmd = malloc(sizeof(t_simpcmd) * (command->pipe_count + 2));
	command->scmd[command->pipe_count + 1].tokarr = 0;
	if (!command->pipe_count)
			command->scmd[0].tokarr = command->tokarr;
	while (i <= command->pipe_count)
	{
		command->scmd[i].tokarr = pipe_tokarr(command, i);
		i++;
	}
	// i = 0;
	// while (i <= command->pipe_count)
	// {
	// 	j = 0;
	// 	while (command->scmd[i].tokarr[j])
	// 	{
	// 		printf("pipe[%d]tok[%d]: %s\n", i, j, command->scmd[i].tokarr[j]);
	// 		j++;
	// 	}
	// 	i++;
	// }
}
