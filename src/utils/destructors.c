#include "minishell.h"

void	reset_data(t_env *env)
{
	safe_free((void **)&env->input.line);
	while (--env->cmds_count > -1)
		destroy_command(&env->commands[env->cmds_count]);
	safe_free((void **)&env->commands);
	env->commands = NULL;
	env->input.i = 0;
	env->cmds_count = 0;
}

void	destroy_command(void *ptr)
{
	t_command	*cmd;

	cmd = ptr;
	if (!cmd)
		return ;
	safe_free((void **)&cmd->cmd);
	safe_free((void **)&cmd->pipe_location);
	safe_free((void **)&cmd->tokarr);
	while (--cmd->tokens_count > -1)
		destroy_token(&cmd->tokens[cmd->tokens_count]);
	safe_free((void **)&cmd->tokens);
	while (--cmd->pipe_count >= -1)
	{
		safe_free((void **)&cmd->scmd[cmd->pipe_count + 1].tokarr);
		safe_free((void **)&cmd->scmd[cmd->pipe_count + 1].quoted);
		safe_free((void **)&cmd->scmd[cmd->pipe_count + 1].heredoc);
	}
	safe_free((void **)&cmd->scmd);
}

void	destroy_token(void *ptr)
{
	t_token	*token;

	token = ptr;
	if (token == NULL)
		return ;
	safe_free((void **)&token->tok);
}

void	safe_free(void **ptr)
{
	if (*ptr == NULL)
		return ;
	free(*ptr);
	*ptr = NULL;
}
