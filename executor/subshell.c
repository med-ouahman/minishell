/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 01:20:10 by mouahman          #+#    #+#             */
/*   Updated: 2025/07/03 11:47:24 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/executor.h"

int	subshell(AST *atom, t_exec_control_block *exec_cb)
{
	t_subshell	*subshell_node;
	pid_t		pid;
	int			status;
	return 0;
	subshell_node = (t_subshell *)atom->data;
	if (subshell_node->ast_node->node_type == ATOM)
		return (subshell(subshell_node->ast_node, exec_cb));

	return (0);
	printf("node type: %s", get_token_type(subshell_node->ast_node->node_type));
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
