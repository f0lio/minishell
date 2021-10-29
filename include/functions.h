
#ifndef FUNCTIONS_H
# define FUNCTIONS_H
# include "minishell.h"

// main
int             repl(ENV);
int             read_input(char **input);
void            show_prompt(char *msg);

// Constructors
t_token         *new_token(char *tok);
t_array         *new_array(int size);
t_env           *init_env(int argc, char **argv, char **env_var);
t_command       **create_commands_array(t_node *list, int size);
t_token         **create_tokens_array(t_node *list, int size);

// Destructors 
void            reset_data(ENV);
void            destroy_command(void *command);
void            destroy_token(void *token);
void            safe_free(void **ptr);

// Tokenizer
BOOL            tokenize_input(ENV);
t_token         *get_token(ENV);
t_token         *tokenize_quoted_cmd(ENV, t_command *cmd);
t_token         *tokenize_single_quoted(ENV, t_command *cmd);
t_token         *tokenize_double_quoted(ENV, t_command *cmd);

t_command       *create_command(t_node *tokens, int count);

// Commands

BOOL            split_commands(ENV);
t_command       *new_cmd(void);
t_command       *get_quoted_command(ENV);
t_command       *single_quoted_cmd(ENV);
t_command       *double_quoted_cmd(ENV);
t_command       *get_command(ENV);
BOOL            command_is_valid(ENV, t_command *cmd);

// Execution
void            cast_cmd(t_command **commands, int cmdcout);
// Pipage
void            search_pipes(t_command *command);
void            pipe_this(t_command *command);
// Apex strtools
char            *ft_substr(char *s, int start, size_t len);
char            **ft_split(char *s, char c);
int	            c_w(char *str, char c);

// Lexer
// int             lex_tokens(t_command **commands, int cmds_count);

// strtools_0
size_t          str_len(const char *str);
void            put_char(char c);
void            put_str(const char *str);
void            fput_char(char c, int fd);
void            fput_str(const char *str, int fd);

// strtools_1
size_t          line_len(const char *str);
BOOL            find_eol(char *buff);
BOOL            line_isempty(char *line);
BOOL            str_cmp(char *s1, char *s2);
BOOL            str_ncmp(char *s1, char *s2, int max);
BOOL            is_alphanum(char c);
BOOL            is_included(char c, char *s);
//char        *char_addr(char c, char **buff);

// strtools_2
char            *str_dup(const char *str);
char            *str_join(const char *s1, const char *s2);
void            str_fjoin(char **dst, char *src);
char            *sub_str(
                    char const *s, int start, int end);
char            *clean_sub_str(
                    char const *s, int start, int end, t_array *arr );
int             skip_char(char *s, char c);
char			*int_to_str(int n);

// Quotes stuff
BOOL            check_quotes(char *str);
BOOL            check_quoted_str(char *str, char c);
BOOL            is_str_quoted(char *str, char mark);
BOOL            is_bad_quoted(char *str);

// Linked list functions
t_node          *new_node(void *data);
t_node          *get_n_node(t_node *lines, int index);
t_node          *push_back(LIST, void  *data);
void            push_front(LIST, void  *data);

size_t          list_size(t_node *list);
void            list_iter(LIST, void(*fun)(void *));
void            destroy_list(LIST);
void            delete_list(LIST);


// Parser
BOOL            split_by_type(char *buff, t_node **tokens);
int             tokenize(char *buff, ENV);

// Expansion

void            expand_input(t_env *env);
void            handle_unquoted_token(char *input, char **new_input, int *i);
void            handle_unquoted_dollar(char *input, char **new_input, int *i);
BOOL	        handle_sinqle_quote(char *input, char **new_input, int *i);
BOOL	        handle_double_quote(
                    t_env *env, char *input, char **new_input, int *i);
char            *expand_dquoted_token(ENV, char *tok);
char            *handle_dollar_sign(char *tok, int *i);
char            *parse_variable_name(char *buf, int *i);
char            *sub_until_chars(char *buf, int *i, char *chars);

// Errors
BOOL            raise_error(ENV, char *msg);
void            destroy_env(ENV);

// File tools
BOOL            create_file(char *path);
BOOL            file_exists(char *path);
t_node          *read_lines(int fd);
int             get_line(int fd, char **line);
BOOL            write_line(int fd, char *line);
BOOL            write_lines(int fd, t_node *lines);

// History
BOOL            is_arrow(ENV);
BOOL            get_history(ENV);
BOOL            set_history(ENV);
void            saveto_history(ENV);

// Signal handlers
void            handle_interuption(int sig_code);
BOOL            is_ctrl_d(char *input);

// on exit
void            exit_program(ENV, int exit_code);


//temporary utils
void            print_array(t_array *arr, BOOL minus);
void            print_tokens(t_token **tokens, int count);
void            print_linked_list(t_node *list);
void            setmemlimit(int mb);

#endif