#include "minishell.h"

void	handle_interuption(int sig_code)
{
	if (sig_code == SIGQUIT && g_sig)
		put_str("Quit: 3\n");
	else if (sig_code == SIGQUIT && g_sig == 0)
		rl_on_new_line();
	else if (sig_code == SIGINT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		rl_on_new_line();
		rl_replace_line("", 0);	
		return ;
	}
	else
		return ;
	rl_redisplay();
}

void	handle_heredoc_signal(int sig_code)
{
	if (sig_code != SIGINT)
		return ;
	rl_replace_line("", 0);
	put_str("\n");
	put_str(PROMPT);
}
