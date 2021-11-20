#include "minishell.h"

void	update_shell_level(t_env *env)
{
	char	*tmp;

	if (!env->envll)
		return ;
	while (env->envll->next && !str_cmp(env->envll->name, "SHLVL"))
		env->envll = env->envll->next;
	if (str_cmp(env->envll->name, "SHLVL"))
	{
		tmp = int_to_str(my_atoi(env->envll->content) + 1);
		safe_free((void **)&env->envll->content);
		env->envll->content = tmp;
	}
	while (env->envll->prev)
		env->envll = env->envll->prev;
}

void	init_env(t_env *env, int argc, char **argv, char **env_var)
{
	(void)argc;
	(void)argv;
	env->env_var = env_var;
	arr_to_ll(env_var, &env->envll);
	update_shell_level(env);
	env->commands = NULL;
	env->cmds_count = 0;
	env->cwd = getcwd(0, 0);
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
