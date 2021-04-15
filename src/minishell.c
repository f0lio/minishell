
# include "minishell.h"

int read_input(char **input)
{
	ssize_t read_ret;
    char    *buff;
    char    *p;

    ARRLLOC(buff, 2);
    *input = str_dup("");
    if (!*input || !buff)
        return (-1);
    while ((read_ret = read(0, buff, 1)) != -1)
    {
        buff[read_ret] = 0;
        if (*buff == EOL)
            return 0;
        p = *input;
        *input = str_join(*input, buff);
        free(p);
    }
    if (read_ret == -1)
        return (-1);
    return (0);
}

//This is the shell loop.
//repl => Read-Eval-Print-Loop
int repl(t_env *env)
{
    int     ret; 
    char    *input;
    size_t  len;

    put_str(SHELL_NAME);
    put_str("$ ");

    if (read_input(&env->input->line) == -1)
        return (-1);
    else if (line_isempty(env->input->line))
        return (0);

    //print(env->input->line);

    /* TODO:
        -> Split commands then tokenize.
    */

    env->input->len = str_len(env->input->line);

    // ret = split_commands(env);
    ret = tokenize_input(env); // ""


    print_tokens(&env->tokens);

    // ret = lex_tokens(env);
    //ret = parse_tokens();
    //ret = execute();
    return (0);
}

int main(int argc, char **argv, char **env_vars)
{
    t_env   *env;
    int     i;

    env = init_env(argc, argv, env_vars);
    i = 0;
    while (1)
        if (repl(env))
            break;
    
    //Free allocated mem
    return (0);
}
