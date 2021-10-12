
#include "minishell.h"

//initialize props
t_env   *init_env(int argc, char **argv, char **env_var)
{
    t_env   *env;

    MALLOC(env);
    MALLOC(env->history);
    MALLOC(env->input);
    env->env_var = env_var;
    env->commands = NULL;
    return (env);
}

t_token *new_token(char *tok)
{
    t_token *token;

    MALLOC(token);
    token->tok = NULL;
    token->type = -1;
    token->len = NULL;
    if (tok)
        token->tok = tok;
    return (token);
}

t_command *new_cmd(void)
{
    t_command *cmd;

    MALLOC(cmd);
    if (!cmd)
        return (NULL);
    cmd->cmd = NULL;
	cmd->pipe_count = -1;
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
