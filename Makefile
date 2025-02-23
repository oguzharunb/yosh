#CC				= cc
#CFLAGS			= -Wall -Wextra -Werror
#LDFLAGS			= -lreadline
#NAME			= minishell
#
#MANDATORY_DIR 		= source
#
#SOURCE			= parser.c parse_pipe.c expander.c lexer.c main.c parse_redirect.c parse_command.c test_print.c
#SRC				= $(addprefix $(MANDATORY_DIR)/, $(SOURCE))
#OBJ				= $(SRC:.c=.o)
#
#all: $(NAME)
#
#$(NAME): $(OBJ)
#	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LDFLAGS)
#
#clean:
#	rm -rf $(OBJ)
#
#fclean: clean
#	rm -rf $(NAME)
#
#re: fclean all
#
#.PHONY: all clean fclean re

CC				= cc
CFLAGS			= -Wall -Wextra -Werror
LDFLAGS			= -lreadline
NAME			= minishell

MANDATORY_DIR 		= source

SRC				= $(wildcard $(MANDATORY_DIR)/*.c)
OBJ				= $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LDFLAGS)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re