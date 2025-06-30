CC = cc

CFLAGS = -Wall -Wextra -Werror -g

# Define the directories for the different components of the project

SRCS = src
BUILTINS = builtins
EXECUTOR = executor
SIGNALS = signals
PARSER = parser
LIBFT_DIR = libft
UTILS = utils

INCLUDE = include

LIBFT = $(LIBFT_DIR)/libft.a

# Fetch all source files from the defined directories

SRCS_SRC = $(wildcard $(SRCS)/*.c)
BUILTINS_SRC = $(wildcard $(BUILTINS)/*.c)
EXECUTOR_SRC = $(wildcard $(EXECUTOR)/*.c)
SIGNALS_SRC = $(wildcard $(SIGNALS)/*.c)
PARSER_SRC = $(wildcard $(PARSER)/*.c)
UTILS_SRC = $(wildcard $(UTILS)/*.c)

# Fech all source files from the builtins directory

# builtins

CD = $(BUILTINS)/cd
ECHO = $(BUILTINS)/echo
ENV = $(BUILTINS)/env
EXIT = $(BUILTINS)/exit
EXPORT = $(BUILTINS)/export
PWD = $(BUILTINS)/pwd
UNSET = $(BUILTINS)/unset

BUILTINS_SRC += $(wildcard $(CD)/*.c)
BUILTINS_SRC += $(wildcard $(ECHO)/*.c)
BUILTINS_SRC += $(wildcard $(ENV)/*.c)
BUILTINS_SRC += $(wildcard $(EXIT)/*.c)
BUILTINS_SRC += $(wildcard $(EXPORT)/*.c)
BUILTINS_SRC += $(wildcard $(PWD)/*.c)
BUILTINS_SRC += $(wildcard $(UNSET)/*.c)

# Compile all source files into object files

SRCS_OBJS = $(SRCS_SRC:.c=.o)
BUILTINS_OBJS = $(BUILTINS_SRC:.c=.o)
EXECUTOR_OBJS = $(EXECUTOR_SRC:.c=.o)
SIGNALS_OBJS = $(SIGNALS_SRC:.c=.o)
PARSER_OBJS = $(PARSER_SRC:.c=.o)
UTILS_OBJS = $(UTILS_SRC:.c=.o)


OBJS = $(SRCS_OBJS) $(BUILTINS_OBJS) $(EXECUTOR_OBJS) $(SIGNALS_OBJS) $(PARSER_OBJS) $(UTILS_OBJS)

RM = rm -f

NAME = minishell

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -I$(INCLUDE) -lreadline -o $(NAME)

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
