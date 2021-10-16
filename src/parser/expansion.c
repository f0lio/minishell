#include "minishell.h"

void expand_command_tokens(t_env *env)
{
    int i;
    int j;

    i = -1;
    while (++i < env->cmds_count)
    {
        j = -1;
        while (++j < env->commands[i]->tokens_count)
            expand_tokens(env, env->commands[i]->tokens[j]);
    }
}

void expand_tokens(t_env *env, t_token *token)
{
    char    *var;
    char    *val;
    char    *new_tok;
    int     i;

    if (token->quoted == TYPE_SINGLE_QT)
        return ;
    new_tok = str_dup("");
    i = 0;
    while (i < token->len)
    {
        if (token->tok[i] == '$' && (i == token->len - 1))
        {
            new_tok = str_join((const char*)new_tok, "$");
            break ;
        }
        else if (token->tok[i] == '$' && token->tok[i - 1] != '\\')
        {
            var = parse_variable_name(token, &i);
            val = getenv(var);
            i -= (val != NULL);
            if (val)
                new_tok = str_join((const char*)new_tok, (const char*)val);
            // printf("[%s] -> [%s]\n", var, val);
        }
        else
        {
            var = new_tok;
            val = parse_simple_chars(token, &i);
            new_tok = str_join(
                (const char*)new_tok,
                (const char*)val);
            i--;
            // continue ;
        }
        i++;
    }
    // if (token->tok) free(token->tok);
    token->tok = new_tok;
}
// echo "hi $USER"

char    *parse_variable_name(t_token *token, int *i)
{
    int     start;
    size_t     j;

    j = *i + 1;
    start = j;
    while (j < token->len && 
    (is_alphanum(token->tok[j]) || token->tok[j] == '_'))
        j++;
    *i = j;
    return (sub_str(token->tok, start, j));
}

char    *parse_simple_chars(t_token *token, int *i)
{
    int         start;
    size_t      j;

    start = *i;
    j = *i;
    while (j < token->len && token->tok[j] != '$')
        j++;
    *i = j;
    return (sub_str(token->tok, start, j));
}
