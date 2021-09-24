
#include "minishell.h"

void	handle_interuption(int sig_code)
{
	// printf("[SIG: %d]\n", sig_code);
	if (sig_code != SIGINT)
		return ;
	put_str("\n");
	show_prompt(SHELL_NAME);
}
