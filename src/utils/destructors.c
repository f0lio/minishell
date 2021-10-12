
#include "minishell.h"

void    reset_data(ENV)
{
    safe_free ((void**)&env->input->line);
    while (--env->cmds_count >= 0)
        destroy_command(env->commands[env->cmds_count]);
    safe_free((void**)&env->commands);
    env->commands = NULL;
    env->input->i = 0;
}

void    destroy_command(void *ptr)
{
    t_command *cmd;
    cmd = ptr;
    if (!cmd)
        return ;
    safe_free((void**)&cmd->cmd);
    safe_free((void**)&cmd->pipe_location);
    // printf("#[%d]\n", cmd->tokens_count);
    while (--cmd->tokens_count >= 0)
        destroy_token(cmd->tokens[cmd->tokens_count]);
    safe_free((void**)&cmd);
}

void    destroy_token(void *ptr)
{
    t_token *token;

    token = ptr;
    if (token == NULL)
        return ;
    
    safe_free((void*)&token->tok);
    safe_free((void*)&token);
}

void safe_free(void **ptr)
{
    if (*ptr == NULL)
        return ;
    free(*ptr);
    *ptr = NULL;
}

/* 
echo okay; cd dir; pwd | cat | grep *
*/
