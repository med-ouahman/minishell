/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:36:37 by mouahman          #+#    #+#             */
/*   Updated: 2025/07/02 16:47:18 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/executor.h"

void	reset_exec_cb(t_exec_control_block *exec_cb)
{
	free(exec_cb->pids);
	exec_cb->pids = NULL;
	exec_cb->curr_pid = 0;
	exec_cb->pid_size = 0;
	reset_stdio(exec_cb->stdio);
}

int	execute_or(AST *parse_t, t_exec_control_block *exec_cb)
{
	t_ast_binary	*bin;
	int				stat;
	
	bin = (t_ast_binary *)parse_t->data;
	stat = executor(bin->left, exec_cb);
	if (stat)
		stat = executor(bin->right, exec_cb);
	return (stat);
}

int	execute_and(AST *parse_t, t_exec_control_block *exec_cb)
{
	t_ast_binary	*bin;
	int				stat;

	bin = (t_ast_binary *)parse_t->data;
	stat = executor(bin->left, exec_cb);
	if (!stat)
		stat = executor(bin->right, exec_cb);
	return (stat);
}

int	execute_single_command(AST *parse_t, t_exec_control_block *exec_cb)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)parse_t->data;
	if (cmd->is_buitlin)
	{
		return (execute_builtin(cmd, exec_cb->stdio));
	}
	exec_cb->pid_size = 1;
	exec_cb->curr_pid = 0;
	exec_cb->pids = malloc(sizeof (pid_t) * exec_cb->pid_size);
	garbage_collector(exec_cb->pids, CHECK);
	if (0 > simple_command(cmd, exec_cb))
	{
		exec_cb->pid_size = 0;
		return (-1);
	}
	wait_children(exec_cb->pids, exec_cb->pid_size);
	return (0);
}

int executor(AST *parse_t, t_exec_control_block *exec_cb)
{
	if (!parse_t)
		return (0);
	if (parse_t->node_type == PIPE)
	{
		exec_cb->pipeline = create_pipeline(parse_t);
		return (execute_pipeline(exec_cb));
	}
	else if (parse_t->node_type == CMD)
	{
		if (0 > prepare_redirs((t_cmd *)parse_t->data, exec_cb->stdio))
			return (-1);
		return (execute_single_command(parse_t, exec_cb));
	}
	if (parse_t->node_type == OR)
		return (execute_or(parse_t, exec_cb));
	if (parse_t->node_type == AND)
		return (execute_and(parse_t, exec_cb));
	if (parse_t->node_type == ATOM)
	{
		reset_exec_cb(exec_cb);
		exec_cb->pids = malloc(sizeof (pid_t));
		garbage_collector(exec_cb->pids, CHECK);
		exec_cb->pid_size = 1;
		subshell(parse_t, exec_cb);
		garbage_collector(exec_cb->pids, FREE);
		return (wait_children(exec_cb->pids, exec_cb->pid_size));
	}
	return (0);
}

int	setup_execution(AST *parse_t)
{
	t_exec_control_block	exec_cb;

	exec_cb.paths = split_path();
	exec_cb.pids = NULL;
	exec_cb.pipeline = NULL;
	exec_cb.pipes = NULL;
	exec_cb.pid_size = 0;
	exec_cb.curr_pid = 0;
	exec_cb.stdio[0] = STDIN_FILENO;
	exec_cb.stdio[1] = STDOUT_FILENO;
	executor(parse_t, &exec_cb);
	return (0);
}
