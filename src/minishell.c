
#include "minishell.h"

/*
** repl => Read-Eval-Print-Loop
*/
int repl(t_env *env)
{
	int		ret = 0;
	char	*input;
	size_t	len;

	// env->input->line = str_dup("cd aslkmd");
	env->input->line = readline(PROMPT);
	if (env->input->line == NULL)
	{
		put_str("exit\n");
		destroy_env(env);
		// system("leaks minishell");
		exit(env->exitcode);
	}
	if (!line_is_whitespaces(env->input->line))
		add_history(env->input->line);
	env->input->len = str_len(env->input->line);
	expand_input(env);
	tokenize_input(env);
	analyse_syntax(env);
	// debug_commands(env);
	cast_cmd(env->commands, env->cmds_count, env);
	return (0);
}

int main(int argc, char **argv, char **env_vars)
{
	t_env	*env;

	// setmemlimit(1); // (supposedly) limits memory to avoid stupid crashes
	env = init_env(argc, argv, env_vars);
	signal(SIGINT, handle_interuption);
	while (1)
	{
		repl(env);
		reset_data(env);
	}
	return (0);
}
