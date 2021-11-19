
.PHONEY: all clean fclean re bonus

NAME				=	minishell
CC					=	gcc
FLAGS				=	-Werror -Wextra -Wall

INCLUDES			=	-I include -I /usr/include/readline/readline.h

UTILS				=	strtools_0.c strtools_1.c strtools_2.c strtools_3.c\
						str_join.c itoa.c\
						linked_list.c linked_list_helpers.c destructors.c\
						error_handlers.c signals_handlers.c exit_handlers.c

CONSTRUCTORS		=	env.c

EXPANSION			=	expand.c helpers.c double_quoted_tokens.c get_env_var.c
TOKENIZER			=	tokenizer.c get_token.c tokenize_quoted.c utils.c
SYNTAX_ANALYSER			= analyse_syntax.c

EXECUTION			=	redirect.c\
						redirio.c\
						prep.c\
						exec.c\
						apex_strtools.c\
						strtools.c\
						pipe.c\
						pipe2.c\
						error.c\
						b_echo.c\
						b_export.c\
						b_unset.c\
						builtins.c\
						tools.c

SRC					=	src/minishell.c\
						$(DBG:%.c=./dbg/%.c)\
						$(CONSTRUCTORS:%.c=./src/constructors/%.c)\
						$(TOKENIZER:%.c=./src/tokenizer/%.c)\
						$(SYNTAX_ANALYSER:%.c=./src/syntax_analyser/%.c)\
						$(EXPANSION:%.c=./src/expansion/%.c)\
						$(UTILS:%.c=./src/utils/%.c)\
						$(EXECUTION:%.c=./src/execution/%.c)

READLINE			=	-lreadline\
						-L /Users/$(USER)/goinfre/.brew/opt/readline/lib\
						-I /Users/$(USER)/goinfre/.brew/opt/readline/include

COMPILE				= $(CC) $(FLAGS) $(SRC) $(INCLUDES) $(READLINE) -o $(NAME)

all: $(NAME)

$(NAME): $(SRC)
	@$(COMPILE)

run: all
	@./$(NAME)

#install readline on debian based OS
install:
	@echo "Installing dependencies.."
	@apt-get install libreadline6 libreadline6-dev

clean:
	@rm -rf *.o

fclean: clean
	@-rm -f $(NAME)
	@-rm -f *.out
	@-rm -f *.gch
	@-rm -rf ./*.d*

re: fclean all

#dev rules
sandbox:
	@sh ./start.sh

check_leaks: $(NAME)
	valgrind --leak-check=full ./$(NAME)
