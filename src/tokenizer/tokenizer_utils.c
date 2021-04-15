
#include "minishell.h"

t_token    *tokenize_quoted_command(ENV, t_command *cmd)
{
    t_token    *token;

    if (env->input->line[cmd->i] == SINGLE_QT)
        token = tokenize_single_quoted(env, cmd);
    else
        token = tokenize_double_quoted(env, cmd);
    if (token)
        token->quoted = TRUE;
    return (token);
    //Should be cleaned from backSlashes
}

t_token    *tokenize_single_quoted(ENV, t_command *cmd)
{
    t_token     *token;
    char        *line;
    size_t      j;

    line = cmd->cmd;
    j = cmd->i;
    while (++j < cmd->len)
        if (line[j] == SINGLE_QT && line[j - 1] != BACK_SLASH)
        {
            j++;
            break;
        }
    token = new_token(sub_str(line, cmd->i, j));
    cmd->i = j;
    return (token);
}

t_token    *tokenize_double_quoted(ENV, t_command *cmd)
{
    t_token     *token;
    size_t      j;
    char        *line;

    line = cmd->cmd;
    j = cmd->i;
    while (++j < cmd->len)
        if (line[j] == DOUBLE_QT && line[j - 1] != BACK_SLASH)
        {
            j++;
            break;
        }
    token = new_token(sub_str(line, cmd->i, j));
    cmd->i = j;
    return (token);
}

# define ARR_SIZE 256

t_token *get_token(ENV, t_command *cmd)
{
    t_token     *token;
    char        *line;
    t_array     *skip;
    size_t      j;
    short       k;

    //To h&&le:
    //  +[ cd d\ ir]
    //  -[echo okay \\ > file]
    //  -[echo okay \ > file]

    skip = new_array(ARR_SIZE);
    k = 0;
    line = cmd->cmd;
    j = cmd->i;
    while (j < cmd->len)
    {
        write(1, &line[j], 1);
        if (line[j] == BACK_SLASH)
            skip->arr[k++] = j;
        else if (line[j] == ' ' && line[j - 1] != BACK_SLASH)
            break ;
        j++;
    }
    write(1, "\n", 1);
    token = new_token(clean_sub_str(line, cmd->i, j, skip));
    cmd->i = j;
    return token;
}
