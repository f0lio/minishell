#include "minishell.h"

void	print_err(char *s1, char *s2, char *s3, char *s4)
{
	fput_str(SHELL_NAME, STDERR_FILENO);
	if (s1)
	{
		fput_str(": ", STDERR_FILENO);
		fput_str(s1, STDERR_FILENO);
	}
	if (s2)
	{
		fput_str(": ", STDERR_FILENO);
		fput_str(s2, STDERR_FILENO);
	}
	if (s3)
	{
		fput_str(": ", STDERR_FILENO);
		fput_str(s3, STDERR_FILENO);
	}
	if (s4)
	{
		fput_str(": ", STDERR_FILENO);
		fput_str(s4, STDERR_FILENO);
	}
	fput_str("\n", STDERR_FILENO);
}
