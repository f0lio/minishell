#include "minishell.h"

/*
TODO:
	-Make it more readable.
	-plz.
*/
static short	free_buff(char **p)
{
	if (*p)
		free(*p);
	return (-1);
}

static int		got_line(char **stream, char **buff, char **line)
{
	char		*p;

	free_buff((void*)buff);
	if (!(*line = sub_str(*stream, 0, line_len(*stream))))
		return (-1);
	p = *stream;
	if (!(*stream = str_dup(*stream + line_len(*stream) + 1)))
	{
		free_buff(&p);
		return (-1);
	}
	free_buff(&p);
	return (1);
}

// WTF !!! 🤖
int		get_line(int fd, char **line)
{
	static char *stream[OPEN_MAX];
	ssize_t		read_ret;
	char		*p;
	char		*buff;

	if (fd < 0 || !line || BUFF_SIZE < 0
		|| read(fd, NULL, 0) || !(buff = malloc(BUFF_SIZE + 1)))
		return (-1);
	if (!stream[fd] && !(stream[fd] = str_dup("")))
			return (-1);
	while (!find_eol(stream[fd]) && (read_ret = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[read_ret] = '\0';
		p = stream[fd];
		stream[fd] = str_join(stream[fd], buff);
		if (NOT stream[fd])
			return (free_buff(&p));
		free_buff(&p);
	}
	if (find_eol(stream[fd]))
		return (got_line(&stream[fd], &buff, line));
	if (!(*line = str_dup(stream[fd])))
		return (-1);
	stream[fd] ? free_buff(&stream[fd]) : 0;
	buff ? free_buff(&buff) : 0;
	return (read_ret > 0 ? 1 : read_ret);
}
