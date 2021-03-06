
#include "minishell.h"

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
        else if (*buff == 0)
            return 1;
        p = *input;
        *input = str_join(*input, buff);
        free(p);
    }
    if (read_ret == -1)
        return (-1);
    return (0);
}


void    show_prompt(char *msg)
{
    put_str(msg);
    put_str("$ ");
}

//This is the shell loop.
//repl => Read-Eval-Print-Loop
int repl(t_env *env)
{
    int     ret;
    char    *input;
    size_t  len;

    show_prompt(SHELL_NAME);
    signal(SIGINT, handle_interuption);
    ret = read_input(&env->input->line);
    if (ret == -1)
        raise_error(env, ERR_INPUT);
    else if (ret == 1) //CTRL+D
        exit_program(env, EXIT_SUCCESS);
    if (line_isempty(env->input->line))
    {
        env->history->curr_line = env->history->last_line;
        return (0);
    }
    if (is_arrow(env)) //tmp condition
        return get_history(env);
    saveto_history(env);
    /* TODO:
        +> Split commands
        +> then tokenize.
    */
    env->input->len = str_len(env->input->line);
    if (split_commands(env) == -1)
        return 0;
    if (tokenize_commands(env) == -1)
        return 0;
    //ret = lex_tokens(env);
    //ret = parse_tokens();
    //ret = execute();
    return (0);
}

int main(int argc, char **argv, char **env_vars)
{
    t_env   *env;

    env = init_env(argc, argv, env_vars);
    set_history(env);
    while (1)
    {
        if (repl(env))
            break;
        reset_data(env);
    }
    //-Free allocated mem
    return (0);
}
/*
echo okay; cd $MY_DIR; pwd | cat | grep $VAR
*/
