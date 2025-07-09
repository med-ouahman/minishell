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

	pid = fork();
	if (0 > pid)
		return (-1);
	if (0 == pid)
	{
		status = execute_builtin(builtin_cmd, exec_cb->stdio);
		exit(status);
	}
	exec_cb->pids[exec_cb->curr_pid] = pid;
	exec_cb->curr_pid++;
	close_stdio(exec_cb->stdio);
	return (0);
}

int	execute_builtin(t_cmd *cmd, int *stdio)
{
	int	old[2];
	int	code;

	preserve_stdio(old, stdio);
	dup_stdio(stdio);
	if (CD == cmd->is_buitlin)
		code = (cd(cmd));
	if (PWD == cmd->is_buitlin)
		code = (pwd(cmd));
	if (EXIT == cmd->is_buitlin)
		code = (exit_(cmd));
	if (ECHO == cmd->is_buitlin)
		code = (echo(cmd));
	if (EXPORT == cmd->is_buitlin)
		code = (export(cmd));
	if (UNSET == cmd->is_buitlin)
		code = (unset(cmd));
	if (ENV == cmd->is_buitlin)
		code = (env());
	restore_stdio(old);
	return (code);
}
