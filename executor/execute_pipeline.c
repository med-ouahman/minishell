/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 10:12:02 by mouahman          #+#    #+#             */
/*   Updated: 2025/07/06 11:08:56 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/executor.h"

static int	num_pipes(t_exec_control_block *exec_cb)
{
	t_list	*pipeline;

	pipeline = exec_cb->pipeline;
	exec_cb->num_commands = 0;
	while (pipeline)
	{
		exec_cb->num_commands++;
		pipeline = pipeline->next;
	}
	return (-1 + exec_cb->num_commands);
}

static int
	execute_pipe_end(t_cmd *cmd, t_exec_control_block *exec_cb, t_uint i)
{
	int	status;

	status = 0;
	if (prepare_redirs(cmd->redir, exec_cb->stdio))
	{
		close_stdio(exec_cb->stdio);
		return (1);
	}
	set_stdio(exec_cb, i);
	if (cmd->args)
		cmd->is_builtin = is_builtin(cmd->args->content);
	if (cmd->is_builtin)
	{
		status = run_builtin_in_subshell(cmd, exec_cb);
	}
	else
	{
		status = simple_command(cmd, exec_cb);
	}
	reset_stdio(exec_cb->stdio);
	return (status);
}

int	execute_pipeline(t_list *pipeline, t_exec_control_block *exec_cb)
{
	t_uint	i;
	int		last_exit_code;

	exec_cb->pipeline = pipeline;
	exec_cb->pipes = create_pipes(num_pipes(exec_cb));
	if (!exec_cb->pipes)
		return (1);
	exec_cb->pids = malloc(exec_cb->num_commands * sizeof(pid_t));
	collect_malloc(exec_cb->pids, CHECK);
	ft_memset(exec_cb->pids, -1, exec_cb->num_commands * 4);
	i = 0;
	while (pipeline)
	{
		last_exit_code = execute_pipe_end(pipeline->content, exec_cb, i);
		pipeline = pipeline->next;
		i++;
	}
	close_pipes(exec_cb->pipes, exec_cb->num_commands - 1);
	if (!last_exit_code)
		last_exit_code = wait_children(exec_cb->pids, exec_cb->num_commands);
	handle_signals();
	return (last_exit_code);
}
