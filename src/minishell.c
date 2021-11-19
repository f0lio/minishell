#include "minishell.h"

/*
** repl => Read-Eval-Print-Loop
*/

int	repl(t_env *env)
{
	env->input.line = readline(PROMPT);
	if (env->input.line == NULL)
	{
		put_str("exit");
		destroy_env(env);
		exit(env->exitcode);
	}
	if (line_is_whitespaces(env->input.line))
		return (0);
	add_history(env->input.line);
	env->input.len = str_len(env->input.line);
	if (expand_input(env))
		return (SYNTAX_ERR_CODE);
	if (tokenize_input(env))
		return (SYNTAX_ERR_CODE);
	if (analyse_syntax(env))
		return (SYNTAX_ERR_CODE);
	cast_cmd(env->commands, env->cmds_count, env);
	return (0);
}

int	main(int argc, char **argv, char **env_vars)
{
	t_env	env;

	init_env(&env, argc, argv, env_vars);
	while (1)
	{
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, handle_sigquit);
		if (repl(&env) == SYNTAX_ERR_CODE)
		{
			env.exitcode = SYNTAX_ERR_CODE;
			set_exitcode(&env);
		}
		reset_data(&env);
		g_sig = 0;
	}
	return (0);
}
