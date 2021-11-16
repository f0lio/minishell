#include "minishell.h"

int	rediro(char *tok, int j, t_simpcmd *scmd)
{
	int	i;

	close(scmd->stdio[1]);
	i = str_cmp(">", scmd->tokarr[j]);
	scmd->isappend = !i * (int)O_APPEND + i * (int)O_TRUNC;
	scmd->stdio[1] = open(tok, O_WRONLY | scmd->isappend | O_CREAT, 0644);
	if (scmd->stdio[1] < 0)
		print_err(tok, strerror(errno), 0, 0);
	return (scmd->stdio[1] < 0);
}

int	rediri(char *tok, t_simpcmd *scmd)
{
	close(scmd->stdio[0]);
	scmd->stdio[0] = open(tok, O_RDONLY);
	if (scmd->stdio[0] < 0)
		print_err(tok, strerror(errno), 0, 0);
	return (scmd->stdio[0] < 0);
}

void	heredoc_loop(char *eof, int fd)
{
	char	*buffer;

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
		if (!buffer)
			break ;
	}
	safe_free((void **)&buffer);
}

int	heredoc(char *eof, t_simpcmd *scmd)
{
	int		fd;

	scmd->heredoc = 1;
	fd = open(HERE_DOC_FILE, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd < 0)
	{
		print_err(HERE_DOC_FILE, strerror(errno), 0, 0);
		return (1);
	}
	heredoc_loop(eof, fd);
	close(fd);
	rediri(HERE_DOC_FILE, scmd);
	return (0);
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
