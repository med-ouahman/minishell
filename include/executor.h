/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:23:24 by mouahman          #+#    #+#             */
/*   Updated: 2025/07/03 13:49:42 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "./utils.h"
# include "./parser.h"
# include <sys/wait.h>
# include "./builtins.h"

# define OPEN_MODE 0644

typedef struct s_pipefd
{
    int pipefds[2];
}   t_pipefd;

typedef struct
{
    t_pipefd    *pipes;
    pid_t       *pids;
    int         pid_size;
    int         curr_pid;
    t_list      *pipeline;
    char        **paths;
    int         stdio[2];
}   t_exec_control_block;

/*

stdio

*/

int	close_stdio(int stdio[]);
int reset_stdio(int *stdio);
int	set_stdio(t_exec_control_block *exec_cb, int curr);

/* stdio */


/* built-in stdio */

int     restore_stdio(int *stdio);
int	dup_stdio(int *stdio);
int	preserve_stdio(int *old_stdio, int *stdio);

/* built-in stdio */

void	print_file_error(char *filename, char *__err_msg);

t_list	*redirs(t_cmd *cmd);

int	    simple_command(t_cmd *cmd, t_exec_control_block *exec_cb);
int	    setup_execution(AST *parse_t);
int		executor(AST *parse_t, t_exec_control_block *exec_cb);
int	    execute_builtin(t_cmd *cmd, int *stdio);
int	    run_builtin_in_subshell(t_cmd *builtin_cmd, t_exec_control_block *exec_cb);
int		prepare_redirs(t_list *redirs, int *stdio);
void	close_pipes(t_pipefd *pipes, int size);
t_pipefd    *create_pipes(int count);
char	*command_path(char **pvs, char *cmd);
char	**split_path(void);
int	    wait_children(pid_t *pids, int num_children);
int	    exit_code(int status);
int     execute_pipeline(t_exec_control_block *exec_cb);
int	    execute_single_command(AST *parse_t, t_exec_control_block *exec_cb);
int	    subshell(AST *atom, t_exec_control_block *exec_cb);

#endif
