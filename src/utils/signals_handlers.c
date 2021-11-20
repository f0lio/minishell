#include "minishell.h"

void	handle_sigint(int sig_code)
{
	(void)sig_code;
	if (g_sig == 0)
	{
		put_char('\n');
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (g_sig == 2)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	handle_sigquit(int sig_code)
{
	(void)sig_code;
	if (g_sig == 1)
		put_str("Quit: 3\n");
	else
	{
		rl_on_new_line();
		rl_redisplay();
	}
}
