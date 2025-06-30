/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:36:37 by mouahman          #+#    #+#             */
/*   Updated: 2025/06/30 13:38:02 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/executor.h"

int	execute_or(AST *parse_t, t_exec_controll_block *exec_cb)
{
	t_ast_binary	*bin;
	int				stat;
	
	bin = (t_ast_binary *)parse_t->data;
	stat = executor(bin->left, exec_cb);
	if (stat)
		stat = executor(bin->right, exec_cb);
	return (stat);
}

int	execute_and(AST *parse_t, t_exec_controll_block *exec_cb)
{
	t_ast_binary	*bin;
	int				stat;
	
	bin = (t_ast_binary *)parse_t->data;
	stat = executor(bin->left, exec_cb);
	if (!stat)
		stat = executor(bin->right, exec_cb);
	return (stat);
}

int	execute_single_command(AST *parse_t, t_exec_controll_block *exec_cb)
{
	t_cmd	*cmd;
	pid_t	pid;

	cmd = (t_cmd *)parse_t->data;
	if (cmd->is_buitlin)
		return (execute_builtin(cmd, exec_cb->stdio));
	pid = simple_command(cmd, exec_cb->stdio, exec_cb->paths);
	if (pid < 0)
		return (access_exit_code(0, READ));
	exec_cb->pids = malloc(sizeof (pid_t));
	garbage_collector(exec_cb->pids, ALLOC);
	exec_cb->pid_size = 1;
	exec_cb->pids[0] = pid;
	return (0);
}

int executor(AST *parse_t, t_exec_controll_block *exec_cb)
{
	if (!parse_t)
		return (0);
	if (parse_t->node_type == CMD)
	{
		set_stdio((t_cmd *)parse_t->data, exec_cb->stdio);
		execute_single_command(parse_t, exec_cb);
		return (wait_children(exec_cb->pids, exec_cb->pid_size));
	}
	if (parse_t->node_type == PIPE)
	{
		exec_cb->pipeline = create_pipeline(parse_t);
		return (execute_pipeline(exec_cb));
	}
	if (parse_t->node_type == OR)
		return (execute_or(parse_t, exec_cb));
	if (parse_t->node_type == AND)
		return (execute_and(parse_t, exec_cb));
	if (parse_t->node_type == ATOM)
		return (executor((AST *)parse_t->data, exec_cb));
	return (0);
}

int	setup_execution(AST *parse_t)
{
	t_exec_controll_block	exec;

	exec.paths = split_path();
	exec.pids = NULL;
	exec.pipeline = NULL;
	exec.pid_size = 0;
	exec.stdio[0] = STDIN_FILENO;
	exec.stdio[1] = STDOUT_FILENO;
	return (executor(parse_t, &exec));
}
