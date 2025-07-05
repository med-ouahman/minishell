/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 01:20:10 by mouahman          #+#    #+#             */
/*   Updated: 2025/07/04 21:18:09 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/executor.h"

int	subshell(AST *atom, t_exec_control_block *exec_cb)
{
	t_subshell	*subshell_node;
	pid_t		pid;
	int			status;
	
	subshell_node = (t_subshell *)atom->data;
	if (subshell_node->ast_node->node_type == ATOM)
		return (subshell(subshell_node->ast_node, exec_cb));
	prepare_redirs(subshell_node->redirs, exec_cb->stdio);
	atom = subshell_node->ast_node;
	pid = fork();
	if (0 > pid)
		return (-1);
	if (0 == pid)
	{
		dup_stdio(exec_cb->stdio);
		close_pipes(exec_cb->pipes, exec_cb->pid_size - 1);
		status = executor(atom, exec_cb);
		exit(status);
	}
	exec_cb->pids[exec_cb->curr_pid] = pid;
	exec_cb->curr_pid++;
	close_stdio(exec_cb->stdio);
	return (0);
}
