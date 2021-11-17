#include "minishell.h"

void	echo(t_simpcmd *scmd, int exitcode)
{
	int	n;
	int	i;

	n = str_cmp(scmd->tokarr[1], "-n");
	i = 0;
	while (scmd->tokarr[++i + n])
	{
		write(1, scmd->tokarr[i + n], str_len(scmd->tokarr[i + n]));
		if (scmd->tokarr[i + 1 + n])
			write(1, " ", 1);
	}
	if (!n)
		write(1, "\n", 1);
}
