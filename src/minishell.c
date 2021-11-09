
#include "minishell.h"

int read_input(char **input)
{
	ssize_t read_ret;
	char	*buff;
	char	*p;

	ARRLLOC(buff, 2);
	*input = str_dup("");
	if (!*input || !buff)
		return (-1);
	while ((read_ret = read(0, buff, 1)) != -1)
	{
		buff[read_ret] = 0;
		if (*buff == EOL)
			return 0;
		else if (*buff == 0)
			return 1;
		p = *input;
		*input = str_join(*input, buff);
		free(p);
	}
	if (read_ret == -1)
		return (-1);
	return (0);
}

void	show_prompt(char *msg)
{
	put_str(GREEN);
	put_str(msg);
	put_str("$ ");
	put_str(NO_COLOR);
}

//This is the shell loop.
//repl => Read-Eval-Print-Loop
int repl(t_env *env)
{
	int	 ret;
	char	*input;
	size_t  len;

	show_prompt(SHELL_NAME);
	signal(SIGINT, handle_interuption);
	ret = read_input(&env->input->line);
	if (ret == -1)
		raise_error(env, ERR_INPUT);
	else if (ret == 1) //CTRL+D
		exit_program(env, EXIT_SUCCESS);
	if (line_isempty(env->input->line))
	{
		env->history->curr_line = env->history->last_line;
		return (0);
	}
	if (is_arrow(env)) //tmp condition
		return get_history(env);
	saveto_history(env);
	env->input->len = str_len(env->input->line);
	if (expand_input(env))
		return 0;
	if (tokenize_input(env))
		return 0;
		
	// put_str(GREEN);
	// printf("-- COUNT -- : %d\n", env->cmds_count);
	// for (int i = 0; i < env->cmds_count; i++)
	// {
	// 	put_str(RED);
	// 	printf("-- Command: %d\n", i);
	// 	put_str(NO_COLOR);
	// 	print_tokens(env->commands[i]->tokens, env->commands[i]->tokens_count);
	// }
	cast_cmd(env->commands, env->cmds_count);
	return (0);
}

int main(int argc, char **argv, char **env_vars)
{
	t_env   *env;

	// setmemlimit(1); // (supposedly) limits memory to avoid stupid crashes

	env = init_env(argc, argv, env_vars);
	set_history(env);
	while (1)
	{
		if (repl(env))
			break;
		reset_data(env);
	}
	//-Free allocated mem
	return (0);
}

