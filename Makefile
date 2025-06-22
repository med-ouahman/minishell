CC = cc

CFLAGS = -Wall -Wextra -Werror -g

SRC = src
BUILTINS = builtins
COMMANDS = commands
PIPES = pipes
SIGNALS = signals
PARSING = parsing
REDIRECTIONS = redirections
LIBFT = libft

SRCS = $(shell find . -type f -name '*.c')

OBJS = $(SRCS:.c=.o)

RM = rm -f

NAME = minishell

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -lreadline -o $(NAME)
	@alias minishell=./$(NAME)

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
