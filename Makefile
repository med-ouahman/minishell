CC = cc

CFLAGS = -Wall -Wextra -Werror

RM = rm -f

INCLUDE = include/

NAME = minishell

LIBFT = ./libft/libft.a

LIBFT_DIR = ./libft/

SRCS =  parser/expander.c parser/expander_tools.c parser/tokenizer.c\
		parser/expander_join_tokens.c parser/heredoc.c parser/parser.c parser/tools.c\
		parser/expander_tokens.c parser/heredoc_parser.c parser/set_commands.c parser/valid_input.c\
		executor/build_argument_list.c parser/get_prompt.c parser/heredoc_tools.c\
		executor/builtin_stdio.c executor/cleanup.c executor/command_path2.c executor/command_path3.c\
		executor/command_path.c executor/execute_builtin.c executor/execute_pipeline.c executor/executor.c\
		executor/exit_code.c executor/get_path.c executor/pipes.c executor/pipe_size.c executor/prepare_redirs.c\
		executor/redirections.c executor/simple_command.c executor/stdio.c executor/wait_children.c\
		builtins/cd/cd.c\
		builtins/echo/echo.c builtins/env/env.c builtins/exit/exit.c builtins/export/export_add.c builtins/export/export.c\
		builtins/export/export_tools.c builtins/export/print_env.c builtins/pwd/pwd.c builtins/unset/unset.c\
		utils/access_exit_code.c utils/ft_join.c\
		utils/add_exit_code.c utils/array_size.c utils/collect_malloc.c utils/list_properties.c utils/min_max.c utils/panic.c\
		utils/print_arr.c utils/printer2.c utils/printer.c utils/print_list.c utils/prompt.c\
		signals/new_prompt.c signals/signal_handler.c\
		src/main.c

OBJS = $(SRCS:.c=.o)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(LIBFT) $(OBJS) 
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -I$(INCLUDE) -lreadline -o $(NAME)

clean:
	@$(RM) $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
