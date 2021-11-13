
#include "minishell.h"

void	handle_interuption(int sig_code)
{
	printf("SIG: %d\n", sig_code);
	if (sig_code == SIGQUIT)
	{
		put_str("Quit: 3\n");
		exit(1);
	}
	if (sig_code != SIGINT)
		return ;
	put_str("\n");
	put_str(PROMPT);
}
