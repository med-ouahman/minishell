/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aid-bray <aid-bray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 09:59:14 by mouahman          #+#    #+#             */
/*   Updated: 2025/08/11 09:54:38 by aid-bray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/executor.h"

int	is_builtin(char *command)
{
	if (!command)
		return (0);
	if (!ft_strcmp("cd", command))
		return (CD);
	else if (!ft_strcmp("echo", command))
		return (ECHO);
	else if (!ft_strcmp("exit", command))
		return (EXIT);
	else if (!ft_strcmp("export", command))
		return (EXPORT);
	else if (!ft_strcmp("env", command))
		return (ENV);
	else if (!ft_strcmp("pwd", command))
		return (PWD);
	else if (!ft_strcmp("unset", command))
		return (UNSET);
	return (NOT);
}

int	run_builtin_in_subshell(t_cmd *builtin_cmd, t_exec_control_block *exec_cb)
{
	int		status;
	pid_t	pid;

	ignore_signals();
	pid = fork();
	if (0 > pid)
	{
		perror("fork");
		return (-1);
	}
	if (0 == pid)
	{
		default_signals();
		status = execute_builtin(builtin_cmd, exec_cb->stdio);
		close_pipes(exec_cb->pipes, exec_cb->num_commands - 1);
		close_stdio(exec_cb->stdio);
		cleanup(status);
	}
	exec_cb->pids[exec_cb->curr_pid++] = pid;
	close_stdio(exec_cb->stdio);
	return (0);
}

int	execute_builtin(t_cmd *cmd, int *stdio)
{
	int		old[2];
	int		code;
	char	**args;

	args = build_argument_list(cmd->args);
	if (EXIT == cmd->is_builtin)
		code = exit_(args, stdio);
	if (preserve_stdio(old, stdio) || dup_stdio(stdio))
		return (close_stdio(old), 1);
	if (CD == cmd->is_builtin)
		code = cd(args);
	else if (PWD == cmd->is_builtin)
		code = pwd(NULL);
	else if (ECHO == cmd->is_builtin)
		code = echo(args);
	else if (EXPORT == cmd->is_builtin)
		code = export(args);
	else if (UNSET == cmd->is_builtin)
		code = unset(args);
	else if (ENV == cmd->is_builtin)
		code = env(args);
	restore_stdio(old);
	return (code);
}
