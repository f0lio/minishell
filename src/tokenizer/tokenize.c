
#include "minishell.h"

t_command *create_command(t_node *tokens, int count)
{
    t_command   *cmd;
    int         i;

    cmd = new_cmd();
    if (!cmd)
        return NULL;
    cmd->tokens_count = count;
    cmd->tokens = create_tokens_array(tokens, count);
    return cmd;
}

# define    ARR_SIZE   256

t_token *get_token(ENV)
{
    t_token     *token;
    size_t      j;
    char        *line;

    BOOL dq = 0, sq = 0;
    line = env->input->line;
    j = env->input->i + skip_char(&line[env->input->i], SPACE);
    while (j < env->input->len)
    {
        if (j == 0 || (line[j - 1] != BACK_SLASH))
        {
            sq += (line[j] == SINGLE_QT);
            sq -= (sq == 1 && dq != 1) * 2 * (line[j] == SINGLE_QT);
            dq += (line[j] == DOUBLE_QT);
            dq -= (dq == 1 && sq != 1) * 2 * (line[j] == DOUBLE_QT);
        }
        
        if (line[j] == SPACE || line[j] == SEP)
        {
            if (!sq && !dq)
                break ;
            else if ((dq == 2 || sq == 2) && line[j] == SPACE)
                break ;
        }
        j++;
    }
    token = new_token(sub_str(line, env->input->i, j));
    env->input->i = j;
    return token;
}

BOOL tokenize_input(ENV)
{
    t_token     *token;
    t_node      *tokens_list;
    t_node      *cmds_list;
    char        *line;
    int         i;

    int         tokens_count;

    tokens_count = 0;
    tokens_list = NULL;
    cmds_list = NULL;
    line = env->input->line;
    i = skip_char(line, ' ');
    if (line[i] == SEP)
        return raise_error(env, ERR_SYNTAX);
    while (i < env->input->len)
    {
        // if line[i] == B_SLASH => skip..?
        env->input->i = i;
        if (line[i] != SPACE)
        {
            if (line[i] == SEP)
            {
                push_back(
                    &cmds_list,
                    create_command(tokens_list, tokens_count));
                // destroy_list(&tokens_list);
                tokens_list = NULL;
                tokens_count = 0;
                env->cmds_count++;
                i++;
                continue ;
            }
            token = get_token(env);
            i = env->input->i;
            push_back(&tokens_list, token);
            tokens_count++;
        }
        else
            i++;
    }
    if (tokens_list)
    {
        push_back(
            &cmds_list, create_command(tokens_list, tokens_count));
        // destroy_list(&tokens_list);
        env->cmds_count++;
        tokens_list = NULL;
    }
    env->commands = create_commands_array(cmds_list, env->cmds_count);
    return (0);
}
