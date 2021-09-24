
#include "minishell.h"

/* TODO:
**  On read_lines() function, read lines using get_line() function
**  get_line() is in get_line.c, which has a TODO.
*/
t_bool  create_file(char *path)
{
    int fd;

    fd = open(path, O_WRONLY | O_APPEND | O_CREAT, 0644);
    if (fd < 0)
        return FALSE;
    close(fd);
    return TRUE;
}

t_bool  file_exists(char *path)
{
    int fd;

    fd = open(path, O_RDONLY);
    if (fd < 0)
        return FALSE;
    close(fd);
    return TRUE;
}

/**
**  Reads a file and make doubly linked list from lines
** 
**  @param fd file descriptor to read from
**  @return Doubly_linked_list containing file lines
**/
t_node  *read_lines(int fd)
{
    t_node  *lines;
    char    *line;

    lines = NULL;
    // tmp block for testing purposes
    {
        # define MAX_LINE_LENGTH 1024
        FILE *file = fopen(HISTORY_FILE, "r");
        char *line = calloc(MAX_LINE_LENGTH, sizeof(char));
        while (fgets(line, MAX_LINE_LENGTH, file))
        {
            if (!line)
                break;
            push_back(&lines, str_dup(line));
        }
    }
    return lines;
}

/**
**  Writes a line to file
** 
**  @param fd file descriptor to write in
**  @return 0 on success
**/
t_bool  write_line(int fd, char *line)
{
    return (write(fd, line, str_len((const char *)line)) != -1);
}

/**
**  Writes to file from a doubly linked list
** 
**  @param fd file descriptor to write in
**  @return 0 on success
**/
t_bool  write_lines(int fd, t_node *lines)
{
    t_node *iter;

    iter = lines;
    while (iter)
    {
        if (write_line(fd, (char*)iter->data))
            return 1;
        iter = iter->next;
    }
    return 0;
}
