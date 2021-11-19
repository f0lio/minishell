#include "minishell.h"

size_t	str_len(const char *str)
{
	size_t	len;

	len = 0;
	while (*str && ++len)
		str++;
	return (len);
}

void	fput_char(char c, int fd)
{
	write(fd, &c, 1);
}

void	fput_str(const char *str, int fd)
{
	write(fd, str, str_len(str));
}

void	put_char(char c)
{
	fput_char(c, 1);
}

void	put_str(const char *str)
{
	fput_str(str, 1);
}
