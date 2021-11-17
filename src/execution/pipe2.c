#include "minishell.h"

BOOL	is_pipe(t_token *t)
{
	if (!t || t->quoted)
		return (FALSE);
	return (t->tok[0] == '|' && t->tok[1] == '\0');
}

int	count_pipes(t_command *command)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (i < command->tokens_count)
	{
		if (is_pipe(&(command->tokens[i])))
			c++;
		i++;
	}
	return (c);
}

void	search_pipes(t_command *command)
{
	int	p;
	int	j;

	p = 0;
	j = 0;
	command->pipe_count = count_pipes(command);
	command->pipe_location = malloc(sizeof(int) * (command->pipe_count + 1));
	while (j < command->tokens_count)
	{
		command->pipe_location[p] = -1;
		if (is_pipe(&(command->tokens[j])))
		{
			command->tokens[j].type = TYPE_PIPE;
			command->pipe_location[p] = j;
			p++;
		}
		j++;
	}
}
