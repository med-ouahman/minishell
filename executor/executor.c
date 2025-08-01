/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:36:37 by mouahman          #+#    #+#             */
/*   Updated: 2025/07/07 14:21:04 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/executor.h"

static void	setup_exec_cb(t_exec_control_block *exec_cb)
{
	exec_cb->pids = NULL;
	exec_cb->pipeline = NULL;
	exec_cb->pipes = NULL;
	exec_cb->pid_size = 0;
	exec_cb->curr_pid = 0;
	reset_stdio(exec_cb->stdio);
}

void	reset_exec_cb(t_exec_control_block *exec_cb)
{
	free(exec_cb->pids);
	exec_cb->pids = NULL;
	exec_cb->curr_pid = 0;
	exec_cb->pid_size = 0;
	reset_stdio(exec_cb->stdio);
}

int	execute_single_command(t_cmd *cmd, t_exec_control_block *exec_cb)
{
	int		pid;
	int		stat;

	if (prepare_redirs(cmd->redir, exec_cb->stdio))
		return (1);
	if (!cmd->args)
		return (0);
	cmd->is_builtin = is_builtin(cmd->args->content);
	if (cmd->is_builtin)
		return (execute_builtin(cmd, exec_cb->stdio));
	exec_cb->pids = &pid;
	if (simple_command(cmd, exec_cb))
		return (access_exit_code(0, READ));
	stat = wait_children(exec_cb->pids, 1);
	signal(SIGINT, sigint_handler);
	return (stat);
}

int	executor(t_list *pipeline)
{
	int						exit_status;
	t_exec_control_block	exec_cb;

	setup_exec_cb(&exec_cb);
	if (!pipeline)
		return (0);
	if (NULL == pipeline->next)
	{
		exit_status = execute_single_command(pipeline->content, &exec_cb);
	}
	else
	{
		exit_status = execute_pipeline(pipeline, &exec_cb);
	}
	access_exit_code(exit_status, WRITE);
	return (exit_status);
}
