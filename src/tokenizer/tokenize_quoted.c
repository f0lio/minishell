
#include "minishell.h"

t_token     *tokenize_quoted_cmd(ENV, t_command *cmd)
{
    t_token     *token;

    if (env->input->line[env->input->i] == SINGLE_QT)
    {
        token = tokenize_single_quoted(env, cmd);
        if (token)
            token->quoted = TYPE_SINGLE_QT;
    }
    else
    {
        token = tokenize_double_quoted(env, cmd);
        if (token)
            token->quoted = TYPE_DOUBLE_QT;
    }
    return (token);
    //Should be cleaned from backSlashes
}

t_token    *tokenize_single_quoted(ENV, t_command *cmd)
{
    t_token     *token;
    size_t      j;
    char        *line;

    line = cmd->cmd;
    j = env->input->i;
    while (++j < env->input->len)
        if (line[j] == SINGLE_QT && line[j - 1] != BACK_SLASH)
        {
            j++;
            break;
        }
    char *tok = sub_str(line, env->input->i, j);
    token = new_token(tok);
    env->input->i = j;
    return (token);
}

t_token    *tokenize_double_quoted(ENV, t_command *cmd)
{
    t_token     *token;
    size_t      j;
    char        *line;

    line = cmd->cmd;
    j = env->input->i;
    while (++j < env->input->len)
        if (line[j] == DOUBLE_QT && line[j - 1] != BACK_SLASH)
        {
            j++;
            break;
        }
    token = new_token(sub_str(line, env->input->i, j));
    env->input->i = j;
    return (token);
}
