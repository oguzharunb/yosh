CC				= cc
CFLAGS			= -Wall -Wextra -Werror
LDFLAGS			= -lreadline
NAME			= minishell

MANDATORY_DIR 		= source

SOURCE			= parser.c expander.c lexer.c main.c
SRC				= $(addprefix $(MANDATORY_DIR)/, $(SOURCE))
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