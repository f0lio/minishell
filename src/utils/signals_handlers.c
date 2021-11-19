#include "minishell.h"

void	handle_interuption(int sig_code)
{
	if (sig_code == SIGQUIT)
	{
		put_str("Quit: 3\n");
		exit(1);
	}
	if (sig_code != SIGINT)
		return ;
	rl_replace_line("", 0);
	put_str("\n");
	put_str(PROMPT);
}

void	handle_heredoc_signal(int sig_code)
{
	if (sig_code != SIGINT)
		return ;
	rl_replace_line("", 0);
	put_str("\n");
	put_str(PROMPT);
}
