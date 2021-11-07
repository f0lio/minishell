
#include "minishell.h"

//initialize props
t_env   *init_env(int argc, char **argv, char **env_var)
{
    t_env   *env;

    MALLOC(env);
    MALLOC(env->history);
    MALLOC(env->input);
    env->env_var = env_var;
	arr_to_ll(env_var, &env->envll);
	printf("%s=%s\n", ((t_envvar *)env->envll->data)->name, ((t_envvar *)env->envll->data)->content);
    env->commands = NULL;
    env->cmds_count = 0;
	// this global variable g_stdin is a temporary fix
	// TODO: pass this variable whenever you read from stdin instead of 0.
	g_stdin = dup(STDIN_FILENO);
	g_cwd = getcwd(0, 0);
    return (env);
}

t_token *new_token(char *tok)
{
    t_token *token;

    MALLOC(token);
    if (!token)
        return NULL;
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

t_command *new_cmd(void)
{
    t_command *cmd;

    MALLOC(cmd);
    if (!cmd)
        return (NULL);
	cmd->pipe_count = -1;
    cmd->cmd = NULL;
	cmd->scmd  = NULL;
	cmd->tokarr = NULL;
	cmd->pipe_count = 0;
	cmd->pipe_location = NULL;
	cmd->sep = 0;
	cmd->ret = 0;
    cmd->cmd = NULL;
    cmd->tokens = NULL;
    return (cmd);
}

t_array *new_array(int size)
{
    t_array *array;
    int     i;

    MALLOC(array);
    ARRLLOC(array->arr, size);
    array->size = size;
    i = 0;
    while (i < size)
        array->arr[i++] = -1;
    return (array);
}
