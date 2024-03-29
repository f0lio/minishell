#ifndef STRUCTS_H
# define STRUCTS_H

typedef char	t_bool;

typedef struct s_node
{
	struct s_node	*prev;
	void			*data;
	struct s_node	*next;
}					t_node;

typedef struct s_file
{
	int			fd;
	char		*path;
	t_node		*lines;
	t_node		*curr_line;
	t_node		*last_line;
}				t_file;

typedef struct s_array
{
	int			*arr;
	int			size;
}				t_array;

typedef struct s_envvar
{
	struct s_envvar	*prev;
	char			*name;
	char			*content;
	struct s_envvar	*next;
}				t_envvar;

typedef struct s_token
{
	char		*tok;
	char		type;
	int			len;
	int			order;
	t_bool		quoted;
}				t_token;

typedef struct s_simpcmd
{
	int			isbuiltin;
	int			biexitstatus;
	char		**tokarr;
	int			*tokquoted;
	char		*infile;
	char		*outfile;
	int			isappend;
	int			*quoted;
	int			stdio[2];
	int			pipe[2];
	char		*heredoc;
	pid_t		pid;
}				t_simpcmd;

typedef struct s_command
{
	char		*cmd;
	t_token		*tokens;
	t_simpcmd	*scmd;
	int			origio[2];
	int			tokens_count;
	char		**tokarr;
	int			pipe_count;
	int			*pipe_location;
	BOOL		ret;
	BOOL		sep;
}				t_command;

typedef struct s_input
{
	char		*line;
	int			len;
	int			i;
}				t_input;

typedef struct s_env
{
	BOOL		state;
	int			argc;
	char		**argv;
	char		**env_var;
	int			exitcode;
	t_envvar	*envll;
	t_file		*history;
	t_input		input;
	char		*cwd;
	int			child;
	t_command	*commands;
	int			cmds_count;
}				t_env;

#endif