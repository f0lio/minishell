#ifndef MACROS_H
# define MACROS_H

# undef BUFF_SIZE
# define BUFF_SIZE 32
# ifndef OPEN_MAX
#  define OPEN_MAX 512
# endif

# define SHELL_NAME         "minishell"
# define HISTORY_FILE       ".minishell_history"

# define BOOL               char
# define FALSE              0
# define TRUE               1
# define DIGITS             "0123456789"
# define ASCII_LOWER        "abcdefghijklmnopqrstuvwxyz"
# define ASCII_UPPER        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
# define PUNCTS             "!\"#$%&\'()*+,-./:;<=>?@[\\]^_`{|}~"
# define WHITESPACES        " \t\n\r\x0b\x0c"
# define SPACE              ' '
# define SINGLE_QT          '\''
# define DOUBLE_QT          '"'
# define BACK_SLASH         '\\'
# define EOL                '\n'
# define SEP                ';'

// Colors
# define RED                "\033[1;31m"
# define GREEN              "\033[1;32m"

// Error messages must have "ERR_" as a prefix
# define ERR_MALLOC         "Couldn't allocate memory"
# define ERR_SYNTAX         "invalid syntax"
# define ERR_INPUT          "invalid input"


// Temporary macros
//////////////////////////////////////////////////////////
# include "minishell.h"
# define MALLOC(ptr)        (ptr) = malloc(sizeof(*(ptr)))
# define ARRLLOC(p, l)      (p) = malloc(sizeof(*(p)) * l)
# define IS_NUM(c)          (c >= '0' && c <= '0')
# define IS_LOWER(c)        (c >= 'a' && c <= 'z')
# define IS_UPPER(c)        (c >= 'A' && c <= 'Z')
# define IS_ALPHA(c)        (IS_LOWER(c) || IS_UPPER(c))
# define ENV                t_env *env
# define LIST               t_node **list

# define FLUSH              write(1, '\n', 1)
# define PASS               0;
//////////////////////////////////////////////////////////

#endif
