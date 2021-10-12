#include "minishell.h"

BOOL     is_pipe(t_token *t)
{
    if (!t || t->quoted)
        return FALSE;
    return (t->tok[0] == '|' && t->tok[1] == '\0');
}

int     lex_tokens(ENV)
{
    t_token *token;
    int     pipes_location[256];
    int     p;
    int     i;
    int     j;

    pipes_location[0] = -1;
    p = 0;
    i = 0;
    while (i < env->cmds_count)
    {
        j = 0;
        while (j < env->commands[i]->tokens_count)
        {
            token = env->commands[i]->tokens[j];
            // printf("->[%s]\n", token->tok);
            if (is_pipe(token))
            {
                token->type = TYPE_PIPE;
                pipes_location[p] = j;
                p++;
            }
            j++;
        }
        i++;
    }
    return 0;
}
