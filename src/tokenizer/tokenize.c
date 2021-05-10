
#include "minishell.h"

t_token     *tokenize_quoted_cmd(ENV, t_command *cmd)
{
    t_token     *token;

    if (env->input->line[env->input->i] == SINGLE_QT)
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
    print("TOK------------");
    print(tok);
    print("---------------");
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

# define ARR_SIZE 256

t_token *get_token(ENV, t_command *cmd)
{
    t_token *token;
    t_array *skip;
    size_t  j;
    short   k;
    char    *line;
    
    //To handle:
    //  +[ cd d\ ir]
    //  -[echo okay \\ > file]
    //  -[echo okay \ > file]

    skip = new_array(ARR_SIZE);
    k = 0;
    j = env->input->i + 1;
    line = cmd->cmd;
    while (j < env->input->len)
    {
        if (line[j] == BACK_SLASH)
            skip->arr[k++] = j;
        else if (line[j] == ' ' && line[j - 1] != BACK_SLASH)
            break ;
        j++;
    }
    token = new_token(clean_sub_str(line, env->input->i, j, skip));
    env->input->i = j;
    return token;
}

t_bool tokenize_cmd(ENV, t_command *cmd)
{
    t_token     *token;
    char        *line;
    int         i;
    int         len;

    line = cmd->cmd;
    i = 0;
    while (i < env->input->len)
    {
        env->input->i = i;
        if (line[i] != SPACE)
        {
            if (line[i] == DOUBLE_QT || line[i] == SINGLE_QT)
                token = tokenize_quoted_cmd(env, cmd);
            else
                token = get_token(env, cmd);
            i = env->input->i;
            push_back(&cmd->tokens, token);
        }
        else
            i++;
    }
    // print("############");
    // print_tokens(cmd->tokens);
    // print("############");
    return 0;
}

t_bool tokenize_commands(ENV)
{
    t_command   *cmd;
    t_node      *iter;

    iter = env->commands;
    while (iter)
    {
        cmd = (t_command*)iter->data;
        env->input->i = 0;
        env->input->len = str_len(cmd->cmd);
        tokenize_cmd(env, cmd);
        iter = iter->next;
    }
    return 0;
}
