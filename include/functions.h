#ifndef FUNCTIONS_H
# define FUNCTIONS_H
# include "minishell.h"

int				repl(t_env *env);
int				read_input(char **input);
void			show_prompt(char *msg);

// Constructors
t_token			*new_token(char *tok);
t_array			*new_array(int size);
void			init_env(t_env *env, int argc, char **argv, char **env_var);
t_command		*create_commands_array(t_node *list, int size);
t_token			*create_tokens_array(t_node *list, int size);

// Destructors 
void			reset_data(t_env *env);
void			destroy_command(void *command);
void			destroy_token(void *token);
void			safe_free(void **ptr);

// Tokenizer
BOOL			tokenize_input(t_env *env);
void			tokenizer(t_env *env, t_node **cmds_list, t_node **tokens_list);
void			add_new_token(
					t_env *env,
					t_node **tokens_list,
					int *tokens_count);
void			add_new_cmd(
					t_env *env,
					t_node **cmds_list,
					t_node **tokens_list,
					int *tokens_count);
t_token			*get_token(t_env *env, char *line);
t_token			*tokenize_quoted_cmd(t_env *env, t_command *cmd);
t_token			*tokenize_single_quoted(t_env *env, t_command *cmd);
t_token			*tokenize_double_quoted(t_env *env, t_command *cmd);
void			clean_from_quotes(t_token *token);

t_command		*create_command(t_node *tokens, int count);

// Commands
BOOL			split_commands(t_env *env);
t_command		*new_cmd(void);
t_command		*get_quoted_command(t_env *env);
t_command		*single_quoted_cmd(t_env *env);
t_command		*double_quoted_cmd(t_env *env);
t_command		*get_command(t_env *env);
BOOL			command_is_valid(t_env *env, t_command *cmd);

// Execution and Pipage
void			cast_cmd(t_command *commands, int cmdcout, t_env *env);
void			search_pipes(t_command *command);
int				pipe_this(t_command *command);
void			redirect_stdio(t_command *command, int i);
char			**token_to_arr(t_token *tokens, int tokcout);
char			*search_cmd(char *cmd, char **paths);
int				search_path(char *path);
void			exec(char *path, t_command *command, int i, t_envvar *env);
void			closefdfree(t_command *command, char ***paths);
int				execbuiltins(t_simpcmd *scmd, t_command *command, t_env *en);

// Apaexx strtools
int				ft_strlen(char *str);
char			*ft_substr(char *s, int start, size_t len);
char			**ft_split(char *s, char c);
int				c_w(char *str, char c);
void			initscmd(t_simpcmd *scmd);
void			arr_to_ll(char **arr, t_envvar **node);
char			**ll_to_arr(t_envvar *node);
t_envvar		*str_to_envv(char *str);
char			**strcut(char *str, char c);
char			*randname(void);
int				rediro(char *tok, int j, t_simpcmd *scmd);
int				rediri(char *tok, t_simpcmd *scmd);
int				heredoc(char *eof, t_simpcmd *scmd);
void			print_err(char *s1, char *s2, char *s3, char *s4);
void			ft_putnbr(long nbr, int base_len, char *base);
long			my_atoi(char *str);
int				is_alphatiriblwit(char c, int i);
void			move_redir_down(t_command *command, int i, int j);

// Builtins
void			echo(t_simpcmd *scmd);
void			pwd(void);
int				cd(t_simpcmd *scmd);
void			env(t_envvar *en);
void			unset(t_envvar *env, t_simpcmd *scmd, int *exitcode);
void			exportt(t_envvar *env, t_simpcmd *scmd, int *exitcode);
int				my_exit(t_env *env, t_simpcmd *scmd, int pipenum, int ex);

// strtools_0
size_t			str_len(const char *str);
void			put_char(char c);
void			put_str(const char *str);
void			fput_char(char c, int fd);
void			fput_str(const char *str, int fd);

// strtools_1
size_t			line_len(const char *str);
BOOL			find_eol(char *buff);
BOOL			line_is_empty(char *line);
BOOL			line_is_whitespaces(char *line);
BOOL			str_cmp(char *s1, char *s2);
BOOL			str_ncmp(char *s1, char *s2, int max);
BOOL			is_alphanum(char c);
BOOL			is_included(char c, char *s);

// strtools_2
char			*str_dup(const char *str);
char			**str_dup_2d(char **src);
char			*str_join(const char *s1, const char *s2);
void			str_fjoin(char **dst, char *src);
char			*sub_str(
					char const *s, int start, int end);
char			*clean_sub_str(
					char const *s, int start, int end, t_array *arr );
int				skip_char(char *s, char c);
char			*int_to_str(int n);
void			mem_zero(void *mem, size_t size);

// Quotes stuff
BOOL			check_quotes(char *str);
BOOL			check_quoted_str(char *str, char c);
BOOL			is_str_quoted(char *str, char mark);
BOOL			is_bad_quoted(char *str);

// Linked list functions
t_node			*new_node(void *data);
t_node			*get_n_node(t_node *lines, int index);
t_node			*push_back(t_node **list, void *data);
void			push_front(t_node **list, void *data);

size_t			list_size(t_node *list);
void			list_iter(t_node **list, void (*fun)(void *));
void			destroy_list(t_node **list);
void			delete_list(t_node **list);

// Parser
BOOL			split_by_type(char *buff, t_node **tokens);
int				tokenize(char *buff, t_env *env);

// Expansion
BOOL			expand_input(t_env *env);
void			handle_unquoted_token(char *input, char **new_input, int *i);
void			handle_unquoted_dollar(
					t_env *env, char *input, char **new_input, int *i);
BOOL			handle_sinqle_quote(char *input, char **new_input, int *i);
BOOL			handle_double_quote(
					t_env *env, char *input, char **new_input, int *i);
char			*expand_dquoted_token(t_env *env, char *tok);
char			*handle_dollar_sign(t_env *env, char *tok, int *i);
char			*parse_variable_name(char *buf, int *i);
char			*sub_until_chars(char *buf, int *i, char *chars);
char			*get_env(t_env *env, char *var_name);
void			handle_backslash(
					t_env *env, const char *input, char **new_input, int *i);

// Syntaxer
BOOL			analyse_syntax(t_env *env);
BOOL			check_next_token(
					t_env *env, BOOL *flag, int len, t_command *cmd);

// Errors
BOOL			raise_error(t_env *env, char *msg);
void			destroy_env(t_env *env);

// File tools
BOOL			create_file(char *path);
BOOL			file_exists(char *path);
t_node			*read_lines(int fd);
int				get_line(int fd, char **line);
BOOL			write_line(int fd, char *line);
BOOL			write_lines(int fd, t_node *lines);

// History
BOOL			is_arrow(t_env *env);
BOOL			get_history(t_env *env);
BOOL			set_history(t_env *env);
void			saveto_history(t_env *env);

// Signal handlers
void			handle_interuption(int sig_code);
void			handle_heredoc_signal(int sig_code);
BOOL			is_ctrl_d(char *input);

// On exit
void			exit_program(t_env *env, int exit_code);
void			set_exitcode(t_env *env);

#endif
