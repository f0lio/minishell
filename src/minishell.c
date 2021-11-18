
#include "minishell.h"

/*
** repl => Read-Eval-Print-Loop
*/
int repl(t_env *env)
{
	env->input.line = readline(PROMPT);
	// env->input.line = str_dup("ls");
	if (env->input.line == NULL)
	{
		put_str("exit");
		destroy_env(env);
		// system("leaks minishell");
		exit(env->exitcode);
	}
	if (line_is_whitespaces(env->input.line))
		return 0;
	add_history(env->input.line);
	env->input.len = str_len(env->input.line);
	expand_input(env);
	tokenize_input(env);
	analyse_syntax(env);
	// debug_commands(env);
	cast_cmd(env->commands, env->cmds_count, env);
	return (0);
}

int main(int argc, char **argv, char **env_vars)
{
	t_env	env;

	init_env(&env, argc, argv, env_vars);
	while (1)
	{
		signal(SIGINT, handle_interuption);
		repl(&env);
		reset_data(&env);
		
	}
	return (0);
}
