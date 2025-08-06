CC = cc

CFLAGS = -Wall -Wextra -Werror

RM = rm -f

NAME = minishell

# Define the directories for the different components of the project

SRCS = src
BUILTINS = builtins
EXECUTOR = executor
SIGNALS = signals
PARSER = parser
LIBFT_DIR = libft
UTILS = utils
WILDCARD = wildcard

INCLUDE = include

LIBFT = $(LIBFT_DIR)/libft.a

# Fetch all source files from the defined directories

SRCS_SRC = $(SRCS)/main.c
BUILTINS_SRC = $(wildcard $(BUILTINS)/*.c)
EXECUTOR_SRC = $(wildcard $(EXECUTOR)/*.c)
SIGNALS_SRC = $(wildcard $(SIGNALS)/*.c)
PARSER_SRC = $(wildcard $(PARSER)/*.c)
UTILS_SRC = $(wildcard $(UTILS)/*.c)
WILDCARD_SRC = $(wildcard $(WILDCARD)/*.c)

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
WILDCARD_OBJS = $(WILDCARD_SRC:.c=.o)

OBJS = $(SRCS_OBJS) $(BUILTINS_OBJS) $(EXECUTOR_OBJS) $(SIGNALS_OBJS) $(PARSER_OBJS) $(UTILS_OBJS) $(WILDCARD_OBJS)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(LIBFT):
	@echo "compiling libft..."
	@$(MAKE) -C $(LIBFT_DIR)
	@echo "libft done!"

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -I$(INCLUDE) -lreadline -o $(NAME)

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(RM) $(OBJS)

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
