#ifndef STRUCTS_H
#define STRUCTS_H
typedef char t_bool;

typedef struct s_node
{
	void *data;
	struct s_node *next;
} t_node;

typedef struct s_btree
{
	void *data;
	struct s_btree *r;
	struct s_btree *l;
} t_btree;

typedef struct s_file
{
	int fd;
	char *name;
} t_file;

typedef struct s_array
{
	int *arr;
	int size;
} t_array;

typedef struct s_token
{
	char *tok;	//"cd" ";"
	char *type; //BUILTIN, ARG, SEP,  "PIPE"
	size_t *len;
	int order; //...??
	t_bool quoted;
} t_token;

/*
** -tokens:	list of command tokens ["ls", "-la", "file"]
** -
** -ret		return value of the command,
**			if ret == ZERO && sep == "&&" then stop executing.
*/

typedef struct s_command
{
	char *cmd;
	t_node *tokens;
	t_bool ret;
	t_bool sep;
} t_command;

typedef struct	s_input
{
	char		*line;
	size_t		len;
	size_t		i;
}				t_input;

typedef struct s_env
{
	int argc;
	char **argv;
	char **env_var;

	t_input *input;
	t_node *commands; //[, , , ], [, , , ]
					  //char				**builtins;
} t_env;

#endif