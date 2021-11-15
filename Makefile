
.PHONEY: all clean fclean re bonus

NAME				=	minishell
CC					=	clang
FLAGS				=	-Werror -Wextra -Wall

INCLUDES			=	-I include -I /usr/include/readline/readline.h

UTILS				=	strtools_0.c strtools_1.c strtools_2.c strtools_3.c\
						file_tools.c get_line.c linked_list.c  destructors.c\
						error_handlers.c signals_handlers.c exit_handlers.c\
						itoa.c tmp_utils.c

CONSTRUCTORS		=	env.c

EXPANSION			=	expand.c helpers.c double_quoted_tokens.c get_env_var.c
TOKENIZER			=	tokenize.c tokenize_quoted.c utils.c
SYNTAX_ANALYSER			= analyse_syntax.c

EXECUTION			=	redirect.c\
						apex_strtools.c\
						pipe.c\
						builtins.c\
						tools.c

DBG					=	dbg_utils.c mem-limit.c

SRC					=	src/minishell.c\
						$(DBG:%.c=./dbg/%.c)\
						$(CONSTRUCTORS:%.c=./src/constructors/%.c)\
						$(TOKENIZER:%.c=./src/tokenizer/%.c)\
						$(SYNTAX_ANALYSER:%.c=./src/syntax_analyser/%.c)\
						$(EXPANSION:%.c=./src/expansion/%.c)\
						$(UTILS:%.c=./src/utils/%.c)\
						$(EXECUTION:%.c=./src/execution/%.c)

COMPILE	= $(CC) $(SRC) $(INCLUDES) -lreadline -o $(NAME) -g #-I dbg #-fsanitize=address 

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
	@$(NAME)
	@sh ./start.sh

check_leaks: $(NAME)
	valgrind --leak-check=full ./$(NAME)
