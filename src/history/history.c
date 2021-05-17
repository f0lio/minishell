
#include "minishell.h"

/* TODO:
**  -if file creation failed, choose a different path.
*/
t_bool  set_history(ENV)
{
    t_file *history;
    t_bool ret;

    ret = TRUE;
    history = env->history;
    history->path = HISTORY_FILE;
    if (!file_exists(history->path))
        ret = create_file(history->path);
    if (ret == FALSE)
    {
        print("READ TODO ON history.c");
        exit(EXIT_FAILURE);
    }
    history->fd = open(history->path, O_RDONLY);
    history->lines = read_lines(history->fd);
    history->last_line = get_n_node(history->lines, -1);
    history->curr_line = history->last_line;
    // print_linked_list(history->lines);
    //should stay open for realtime updates? coffee?
    close(history->fd); 
    return 0;
}

//Protect unresolved FDs
void  saveto_history(ENV)
{
    int fd;

    fd = open(env->history->path, O_APPEND | O_WRONLY);
    write_line(fd, env->input->line);
    write(fd, "\n", 1);
    close(fd);
    env->history->last_line = push_back(
        &env->history->lines, str_dup(env->input->line));
    env->history->curr_line = env->history->last_line;
}

t_bool  is_arrow(ENV)
{
    if (str_cmp(env->input->line, "UP"))
        return TRUE;
    return FALSE;
}

t_bool  get_history(ENV)
{
    
    print(env->history->curr_line->data);
    fflush(stdout);
    if (env->history->curr_line->prev)
        env->history->curr_line = env->history->curr_line->prev;
    return 0;
}


void    print_linked_list(t_node *list)
{
    LOOP_LIST(list, print)
}
