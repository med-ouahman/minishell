/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aid-bray <aid-bray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:23:24 by mouahman          #+#    #+#             */
/*   Updated: 2025/08/15 14:55:55 by aid-bray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "./parser.h"
# include <sys/wait.h>
# include "./builtins.h"
# include "./signal_handler.h"
# include <fcntl.h>
# include <sys/stat.h>

# define OPEN_MODE 0644
# define PERMISSION_DENIED 126
# define NOT_FOUND 127

typedef struct s_pipefd
{
	int	pipefds[2];
}	t_pipefd;

typedef struct s_exec_cb
{
	t_cmd		*current;
	t_pipefd	*pipes;
	pid_t		*pids;
	t_uint		num_commands;
	t_uint		curr_pid;
	t_list		*pipeline;
	int			stdio[2];
}	t_exec_control_block;

typedef enum s_enum_builtins
{
	NOT,
	CD,
	ECHO,
	EXIT,
	PWD,
	ENV,
	EXPORT,
	UNSET
}	t_enum_builtins;

/* stdio */

int			close_stdio(int *stdio);
int			reset_stdio(int *stdio);
int			set_stdio(t_exec_control_block *exec_cb, t_uint curr);
int			restore_stdio(int *stdio);
int			dup_stdio(int *stdio);
int			preserve_stdio(int *old_stdio, int *stdio);

/* command execution and I/O redirection */

char		**build_argument_list(t_list *lst);
int			simple_command(t_cmd *cmd, t_exec_control_block *exec_cb);
int			is_builtin(char *command);
int			executor(t_list *pipeline);
int			execute_builtin(t_cmd *builtin_cmd, int *stdio);
int			run_builtin_in_subshell(t_cmd *builtin_cmd,
				t_exec_control_block *exec_cb);
int			prepare_redirs(t_list *redirs, int *stdio);
int			execute_pipeline(t_list *pipeline, t_exec_control_block *exec_cb);
int			execute_single_command(t_cmd *cmd, t_exec_control_block *exec_cb);
int			is_redout(int type);
int			is_redin(int type);
int			open_red(t_redir *redir);
int			red_flags(int redir_type);

/* pipes */

void		close_pipes(t_pipefd *pipes, int size);
t_pipefd	*create_pipes(int count);

/* command path */

char		*is_executable(char *pathname);
int			is_path(char *pathname);
char		*command_path(char *cmd);
char		*get_next_path(char *path, int r);
char		*getpath(int init);
int			get_file_type(char *__file_path, mode_t *file_type);
int			is_dir(char *name, mode_t f_type, int msg);
int			access_denied(char *save, char **path);
int			fill_path(char **path, char *try_path, char *cmd);
int			save_path(char **save, char *path, int c);

/* child process termination and exit status */

int			wait_children(pid_t *pids, t_uint num_children);
int			exit_code(int status);

#endif
