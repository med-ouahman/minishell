/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:23:24 by mouahman          #+#    #+#             */
/*   Updated: 2025/06/22 14:51:46 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "./utils.h"
# include "./parser.h"
# include <sys/wait.h>
# include "./builtins.h"

typedef struct  s_stdio
{
    int in;
    int out;
}   t_stdio;

int 	simple_command(t_cmd *cmd, int *stdio, char **pvs);
int		executor(t_list *exec_list);
int	    execute_builtin(t_cmd *cmd, int *stdio);
int		set_stdio(t_cmd *cmd, int *stdio);
void	close_pipes(int **pipes);
int		**create_pipes(int);
char	*command_path(char **pvs, char *cmd);
char	**split_path(char **envp);
int	wait_children(pid_t *pids, int num_children);
int	exit_code(int status);

#endif
