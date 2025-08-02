/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:23:24 by mouahman          #+#    #+#             */
/*   Updated: 2025/07/12 22:28:39 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "./utils.h"
# include "./parser.h"
# include <sys/wait.h>
# include "./builtins.h"
# include "./signal_handler.h"
# include <sys/types.h>
# include <fcntl.h>
# include <sys/stat.h>

# define OPEN_MODE 0644

typedef struct s_pipefd
{
	int	pipefds[2];
}	t_pipefd;

typedef struct s_exec_cb
{
	t_pipefd	*pipes;
	pid_t		*pids;
	t_uint		pid_size;
	t_uint		curr_pid;
	t_list		*pipeline;
	char		**paths;
	int			stdio[2];
}	t_exec_control_block;

/* stdio */

int			close_stdio(int stdio[]);
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
int			execute_builtin(t_cmd *cmd, int *stdio);
int			run_builtin_in_subshell(t_cmd *builtin_cmd,
				t_exec_control_block *exec_cb);
int			prepare_redirs(t_list *redirs, int *stdio);
int			execute_pipeline(t_list *pipeline, t_exec_control_block *exec_cb);
int			execute_single_command(t_cmd *cmd, t_exec_control_block *exec_cb);

/* pipes */

void		close_pipes(t_pipefd *pipes, int size);
t_pipefd	*create_pipes(int count);

/* command paths */

int			is_executable(char *pathname);
int			get_file_type(char *filename);
int			is_path(char *pathname);
char		*command_path(char *cmd);
char		*get_next_path(char *path, int r);
char		*getpath(int init);

/* child process termination and exit status */

int			wait_children(pid_t *pids, t_uint num_children);
int			exit_code(int status);

#endif
