/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 09:59:14 by mouahman          #+#    #+#             */
/*   Updated: 2025/07/02 10:17:53 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/executor.h"

int	run_builtin_in_subshell(t_cmd *builtin_cmd, t_exec_control_block *exec_cb)
{
	int		status;
	pid_t	pid;

	ignore_signals();
	pid = fork();
	if (0 > pid)
		return (-1);
	if (0 == pid)
	{
		default_signals();
		status = execute_builtin(builtin_cmd, exec_cb->stdio);
		close_pipes(exec_cb->pipes, exec_cb->pid_size - 1);
		cleanup(status);
	}
	exec_cb->pids[exec_cb->curr_pid] = pid;
	exec_cb->curr_pid++;
	close_stdio(exec_cb->stdio);
	return (0);
}

int	execute_builtin(t_cmd *cmd, int *stdio)
{
	int		old[2];
	int		code;
	char	**args;

	if (preserve_stdio(old, stdio) || dup_stdio(stdio))
		return (1);
	args = build_argument_list(cmd->args);
	if (CD == cmd->is_builtin)
		code = (cd(args));
	if (PWD == cmd->is_builtin)
		code = (pwd());
	if (EXIT == cmd->is_builtin)
		code = (exit_(args));
	if (ECHO == cmd->is_builtin)
		code = (echo(args));
	if (EXPORT == cmd->is_builtin)
		code = (export(args));
	if (UNSET == cmd->is_builtin)
		code = (unset(args));
	if (ENV == cmd->is_builtin)
		code = (env());
	restore_stdio(old);
	return (code);
}
