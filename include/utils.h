/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aid-bray <aid-bray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 05:22:53 by aid-bray          #+#    #+#             */
/*   Updated: 2025/07/30 06:16:17 by aid-bray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "../libft/libft.h"
# include <signal.h>
# include <stdio.h>
# include <errno.h>
# include <readline/readline.h>

typedef enum e_gb
{
	CHECK = 1,
	DELETE,
	CLEAR,
	ENV_CHECK,
	ENV_DELETE,
	ENV_CLEAR,
	DESTROY
}	t_gb;

# define READ 0
# define WRITE 1

typedef unsigned int	t_uint;

typedef enum s_num
{
	false,
	true
}	t_bool;

/////////// printer.c
void	print_err_syntax(char *msg);
void	print_err1(char *msg);
void	print_err2(char *cmd, char *msg);
void	print_err3(char *cmd, char *arg, char *msg);
void	print_file_error(char *filename, char *__err_msg);
void	print_file_error2(char *filename, char *__err_msg, char *sda);
void	print_list(t_list *list);
//////////// collect_malloc.c
void	collect_malloc(void *ptr, int option);

/////////// signal_handler.c
void	handle_signals(void);
void	sigint_handler(int signum);

/////////// prompt.c
void	rl_after_fork(void);
void	rl_new_prompt(void);

/////////// access_exit_code.c
int		access_exit_code(int new_val, int mode);
int		error(int c, int mode);
t_uint	min(unsigned int a, unsigned int b);
int		cleanup(int code);

#endif
