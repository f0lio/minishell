
#include "minishell.h"

void    destroy_token(void **ptr)
{
    t_token *token;

    token = (t_token*)ptr;
    if (token->tok)
    {
        free(token->tok);
        if (token->type)
            free(token->type);
        // token->tok = NULL;
    }
    free(token);
    // token = NULL;
}

void    destroy_command(void **ptr)
{
    t_command   *cmd;

    cmd = *ptr;      // ¯\_(ツ)_/¯
    free(cmd->cmd);
    cmd->cmd = NULL;

    list_iter(&cmd->tokens, destroy_token);

    // cmd->tokens = NULL;
    free(cmd);
    cmd = NULL;
}
