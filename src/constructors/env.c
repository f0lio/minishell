#include "minishell.h"

void	init_env(t_env *env, int argc, char **argv, char **env_var)
{
	(void)argc;
	(void)argv;
	env->env_var = env_var;
	arr_to_ll(env_var, &env->envll);
	env->commands = NULL;
	env->cmds_count = 0;
	g_cwd = getcwd(0, 0);
	env->exitcode = 0;
}

t_token	*new_token(char *tok)
{
	t_token	*token;

	token = malloc(sizeof(*(token)));
	if (!token)
		return (NULL);
	token->tok = NULL;
	token->len = 0;
	token->quoted = FALSE;
	token->type = -1;
	if (tok)
	{
		token->tok = tok;
		token->len = str_len(tok);
	}
	return (token);
}

t_command	*new_cmd(void)
{
	t_command	*cmd;

	cmd = malloc(sizeof(*(cmd)));
	if (!cmd)
		return (NULL);
	cmd->pipe_count = -1;
	cmd->cmd = NULL;
	cmd->scmd = NULL;
	cmd->tokarr = NULL;
	cmd->pipe_location = NULL;
	cmd->sep = 0;
	cmd->ret = 0;
	cmd->cmd = NULL;
	cmd->scmd = NULL;
	cmd->tokens = NULL;
	return (cmd);
}

t_array	*new_array(int size)
{
	t_array	*array;
	int		i;

	array = malloc(sizeof(*(array)));
	ARRLLOC(array->arr, size);
	array->size = size;
	i = 0;
	while (i < size)
		array->arr[i++] = -1;
	return (array);
}

void	initscmd(t_simpcmd *scmd)
{
	scmd->isbuiltin = 0;
	scmd->biexitstatus = -1;
	scmd->pid = 0;
	scmd->isappend = 0;
	scmd->heredoc = 0;
	scmd->infile = 0;
	scmd->outfile = 0;
	scmd->stdio[0] = 0;
	scmd->stdio[1] = 0;
	scmd->pipe[0] = 0;
	scmd->pipe[1] = 0;
}
