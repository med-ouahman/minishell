/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:23:24 by mouahman          #+#    #+#             */
/*   Updated: 2025/06/30 11:53:24 by mouahman         ###   ########.fr       */
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
    pid_t       *pids;
    int         pid_size;
    t_list      *pipeline;
    char        **paths;
    int         stdio[2];
}   t_exec_controll_block;

int 	simple_command(t_cmd *cmd, int *stdio, char **pvs);
int	    setup_execution(AST *parse_t);
int		executor(AST *parse_t, t_exec_controll_block *exec_cb);
int	    execute_builtin(t_cmd *cmd, int *stdio);
int		set_stdio(t_cmd *cmd, int *stdio);
void	close_pipes(t_pipefd *pipes, int size);
t_pipefd    *create_pipes(int count);
char	*command_path(char **pvs, char *cmd);
char	**split_path(void);
int	    wait_children(pid_t *pids, int num_children);
int	    exit_code(int status);
int     execute_pipeline(t_exec_controll_block *exec_cb);
int	execute_single_command(AST *parse_t, t_exec_controll_block *exec_cb);
int	subshell(AST *atom, t_exec_controll_block *exec_cb);

#endif
