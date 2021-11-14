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
		if (is_pipe(command->tokens[i]))
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
		if (is_pipe(command->tokens[j]))
		{
			command->tokens[j]->type = TYPE_PIPE;
			command->pipe_location[p] = j;
			p++;
		}
		j++;
	}
	// printf("%d, %d, %d\n", command->pipe_location[0], command->pipe_location[1], command->pipe_location[2]);
}

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
}

void	rediro(char *tok, int j, t_simpcmd *scmd)
{
	int	i;

	close(scmd->stdio[1]);
	i = str_cmp(">", scmd->tokarr[j]);
	scmd->isappend = !i * (int)O_APPEND + i * (int)O_TRUNC;
	if ((scmd->stdio[1] = open(tok, O_WRONLY | scmd->isappend
	| O_CREAT, 0644)) < 0)
		printf("%s\n", strerror(errno));
}

void	rediri(char *tok, t_simpcmd *scmd)
{
	close(scmd->stdio[0]);
	if ((scmd->stdio[0] = open(tok, O_RDONLY)) < 0)
		printf("%s\n", strerror(errno));
}

void	heredoc(char *eof, t_simpcmd *scmd)
{
	int		fd;
	char	*buffer;

	scmd->heredoc = 1;
	if ((fd = open(HERE_DOC_FILE, O_WRONLY | O_TRUNC | O_CREAT, 0644)) < 0)
		printf("asdasdk%s\n", strerror(errno));
	buffer = 0;
	while (!str_cmp(eof, buffer))
	{
		if (buffer)
		{
			write(fd, buffer, str_len(buffer));
			write(fd, "\n", 1);
		}
		safe_free((void **)&buffer);
		buffer = readline("> ");
	}
	safe_free((void **)&buffer);
	close(fd);
	rediri(HERE_DOC_FILE, scmd);
}

void	pipe_this(t_command *command)
{
	int		i;
	int		j;
	char	*tok;
	t_token	*tk;

	scmd_tokarr_loop(command);
	i = -1;
	command->origio[0] = dup(STDIN_FILENO);
	command->origio[1] = dup(STDOUT_FILENO);
	while (++i <= command->pipe_count)
	{
		command->scmd[i].stdio[0] = dup(command->origio[0]);
		command->scmd[i].stdio[1] = dup(command->origio[1]);
		pipe(command->scmd[i].pipe);
		j = -1;
		while (command->scmd[i].tokarr[++j])
		{
			tk = command->tokens[!!i * (command->pipe_location[i - 1] + 1) + j];
			tok = command->scmd[i].tokarr[j];
			if (tk->quoted) // check if token is quoted
			{
				printf("%s\n", command->scmd[i].tokarr[j]);
				continue ;
			}
			if (str_cmp(tok, ">") || str_cmp(tok, ">>"))
				rediro(command->scmd[i].tokarr[j + 1], j, &command->scmd[i]);
			else if (str_cmp(tok, "<"))
				rediri(command->scmd[i].tokarr[j + 1], &command->scmd[i]);
			else if (str_cmp(tok, "<<"))
				heredoc(command->scmd[i].tokarr[j + 1], &command->scmd[i]);
			else // none of them
				continue ;
			command->scmd[i].tokarr[j] = 0;
			j++;
		}
	}
}

// void	pipe_this(t_command *command)
// {
// 	int	i;
// 	int	j;

// 	scmd_tokarr_loop(command);
// 	i = -1;
// 	command->origio[0] = dup(STDIN_FILENO);
// 	command->origio[1] = dup(STDOUT_FILENO);
// 	while (++i <= command->pipe_count)
// 	{
// 		pipe(command->scmd[i].pipe);
// 		j = -1;
// 		while (command->scmd[i].tokarr[++j])
// 		{
// 			if (command->tokens[!!i * (command->pipe_location[i - 1] + 1) + j]->quoted) // check if token is quoted
// 			{
// 				printf("%s\n", command->scmd[i].tokarr[j]);
// 				continue ;
// 			}
// 			if (str_cmp(command->scmd[i].tokarr[j], "<"))
// 				command->scmd[i].infile = command->scmd[i].tokarr[j + 1];
// 			else if ((str_cmp(command->scmd[i].tokarr[j], ">")
// 					|| str_cmp(command->scmd[i].tokarr[j], ">>")))
// 			{
// 				command->scmd[i].isappend = str_len(command->scmd[i].tokarr[j]) - 1;
// 				command->scmd[i].outfile = command->scmd[i].tokarr[j + 1];
// 			}
// 			else
// 				continue ;
// 			command->scmd[i].tokarr[j] = 0;
// 			j++;
// 		}
// 		if (command->scmd[i].infile)
// 		{
// 			if (((command->scmd[i].stdio[0] = open(command->scmd[i].infile, O_RDONLY | O_CREAT)) < 0))
// 				printf("%s\n", strerror(errno));
// 			// printf("infile: %s\nfd:%d\n", command->scmd[i].infile, command->scmd[i].stdio[0]);
// 		}
// 		else
// 			command->scmd[i].stdio[0] = dup(command->origio[0]);
// 		command->scmd[i].isappend *= (int)O_APPEND;
// 		if (!command->scmd[i].isappend)
// 			command->scmd[i].isappend = (int)O_TRUNC;
// 		if (command->scmd[i].outfile)
// 		{
// 			// printf("append mode: %d\noutfile: %s\n", command->scmd[i].isappend, command->scmd[i].outfile);
// 			if ((command->scmd[i].stdio[1] = open(command->scmd[i].outfile, O_WRONLY | command->scmd[i].isappend | O_CREAT, 0644)) < 0)
// 				printf("%s\n", strerror(errno));
// 		}
// 		else
// 			command->scmd[i].stdio[1] = dup(command->origio[1]);
// 	}
// }
