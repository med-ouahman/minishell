/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 10:12:02 by mouahman          #+#    #+#             */
/*   Updated: 2025/07/02 11:15:58 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/executor.h"

static int	num_pipes(t_exec_control_block *exec_cb)
{
	t_list	*pipeline;

	pipeline = exec_cb->pipeline;
	exec_cb->pid_size = 0;
	while (pipeline)
	{
		exec_cb->pid_size++;
		pipeline = pipeline->next;
	}
	return (exec_cb->pid_size - 1);
}

static int execute_pipe_end(AST *parse_t, t_exec_control_block *exec_cb)
{
	t_cmd	*cmd;

	if (parse_t->node_type == CMD)
	{
		cmd = (t_cmd *)parse_t->data;
		if (cmd->is_buitlin)
		{
			if (0 > run_builtin_in_subshell(cmd, exec_cb))
				return (-1);
		}
		else if (0 > simple_command(cmd, exec_cb))
		{
			close_stdio(exec_cb->stdio);
			return (-1);
		}
	}
	if (parse_t->node_type == ATOM)
	{
		if (0 > subshell(parse_t, exec_cb))
			return (-1);
	}
	return (0);
}

int	execute_pipeline(t_exec_control_block *exec_cb)
{
	int         i;
	AST			*pipe_end;
	
	exec_cb->pipes = create_pipes(num_pipes(exec_cb));
	exec_cb->pids = malloc(exec_cb->pid_size * sizeof *exec_cb->pids);
	garbage_collector(exec_cb->pids, COLLECT);
	i = 0;
	while (exec_cb->pipeline)
	{
		reset_stdio(exec_cb->stdio);
		pipe_end = (AST *)exec_cb->pipeline->content;
		if (pipe_end->node_type == CMD)
			prepare_redirs((t_cmd *)pipe_end->data, exec_cb->stdio);
		if (access_exit_code(0, READ))
			return (-1);
		set_stdio(exec_cb, i);
		execute_pipe_end(exec_cb->pipeline->content, exec_cb);
		exec_cb->pipeline = exec_cb->pipeline->next;
		i++;
	}
	close_pipes(exec_cb->pipes, exec_cb->pid_size - 1);
	return (wait_children(exec_cb->pids, exec_cb->pid_size));
}
