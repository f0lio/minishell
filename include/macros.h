#ifndef MACROS_H
# define MACROS_H

# undef BUFF_SIZE
# define BUFF_SIZE 32
# ifndef OPEN_MAX
#  define OPEN_MAX 512
# endif

# define SHELL_NAME			"minishell"
# define PROMPT				"minishell$ "
# define HISTORY_FILE       ".minishell_history"
# define BUILTINS			"echo:pwd:cd:env:unset:export:exit"
# define HERE_DOC_FILE		"/tmp/msh_heredoc"
# define SYNTAX_ERR_CODE    258
# define BOOL				char
# define FALSE				0
# define TRUE				1
# define DIGITS				"0123456789"
# define ASCII_LOWER		"abcdefghijklmnopqrstuvwxyz"
# define ASCII_UPPER		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
# define PUNCTS				"!\"#$%&\'()*+,-./:;<=>?@[\\]^_`{|}~"
# define WHITESPACES		" \t\n\r\x0b\x0c"
# define SPACE				' '
# define SINGLE_QT			'\''
# define DOUBLE_QT			'"'
# define BACK_SLASH			'\\'
# define EOL				'\n'
# define CMD_SEP			';'
# define PIPE				'|'
# define DOLLAR				'$'

// Token types
# define TYPE_CMD                0
# define TYPE_ARG                1
# define TYPE_PIPE               2
# define TYPE_GREATER            3
# define TYPE_LESSER             4
# define TYPE_APPEND             5
# define TYPE_HEREDOC            6
# define TYPE_FILE               7
# define TYPE_SINGLE_QT          1
# define TYPE_DOUBLE_QT          2

// Colors
# define RED                "\033[1;31m"
# define GREEN              "\033[1;32m"
# define WHITE              "\033[1;37m"
# define NO_COLOR           "\033[0m"

# define ERR_MALLOC         "Couldn't allocate memory"
# define ERR_SYNTAX         "invalid syntax"
# define ERR_INPUT          "invalid input"
# define ERR_CMD_NOT_FOUND	"command not found"
# define ERR_TOO_MANY_ARGS	"too many arguments"
# define ERR_NUM_WRONG		"numeric argument required"
# define ERR_INVALID_ENVV	"not a valid identifier"

#endif
