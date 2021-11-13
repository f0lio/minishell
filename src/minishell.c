
#include "minishell.h"

//This is the shell loop.
//repl => Read-Eval-Print-Loop
int repl(t_env *env)
{
	int		ret = 0;
	char	*input;
	size_t	len;

	env->input->line = readline(PROMPT);
	if (env->input->line == NULL)
	{
		reset_data(env);
		put_str("exit");
		return -1;
	}
	if (!line_is_whitespaces(env->input->line))
		add_history(env->input->line);
	env->input->len = str_len(env->input->line);
	if (expand_input(env))
		return 0;
	if (tokenize_input(env))
		return 0;
	if (analyse_syntax(env))
		return 0;
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
		if (repl(env))
			break;
		reset_data(env);
		// CHECK_LEAKS;
	}
	//-Free allocated mem
	return (0);
}
