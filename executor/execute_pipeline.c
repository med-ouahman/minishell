/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 10:12:02 by mouahman          #+#    #+#             */
/*   Updated: 2025/06/30 13:42:06 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/executor.h"

int execute_pipe_end(AST *parse_t, t_exec_controll_block *exec_cb)
{
	if (parse_t->node_type == CMD)
	{
		return (execute_single_command(parse_t, exec_cb));
	}
	if (parse_t->node_type == ATOM)
	{
		return (subshell(parse_t, exec_cb));
	}
	return (0);
}

int	execute_pipeline(t_exec_controll_block *exec_cb)
{
	int		    stat;
	t_pipefd    *pipes;
	int         i;
	AST			*pipe_end;

	exec_cb->pid_size = ft_lstsize(exec_cb->pipeline);
	pipes = create_pipes(exec_cb->pid_size - 1);
	exec_cb->pids = malloc(exec_cb->pid_size * sizeof *exec_cb->pids);
	garbage_collector(exec_cb->pids, ALLOC);
	i = 0;
	while (exec_cb->pipeline)
	{
		pipe_end = (AST *)exec_cb->pipeline->content;
		if (pipe_end->node_type == CMD)
			set_stdio((t_cmd *)pipe_end->data, exec_cb->stdio);
		if (exec_cb->stdio[0] == STDIN_FILENO && i > 0)
		{
			exec_cb->stdio[0] = pipes[i - 1].pipefds[0];
		}
		if (exec_cb->stdio[1] == STDOUT_FILENO && (i < exec_cb->pid_size - 1))
		{
			exec_cb->stdio[1] = pipes[i].pipefds[1];
		}
		execute_pipe_end(exec_cb->pipeline->content, exec_cb);
		exec_cb->pipeline = exec_cb->pipeline->next;
		i++;
	}
	close_pipes(pipes, exec_cb->pid_size - 1);
	stat = wait_children(exec_cb->pids, exec_cb->pid_size);
	return (access_exit_code(stat, WRITE));
}
