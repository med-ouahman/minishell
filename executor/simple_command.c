/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aid-bray <aid-bray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 11:11:30 by mouahman          #+#    #+#             */
/*   Updated: 2025/08/06 12:06:39 by aid-bray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/executor.h"

static void	child(char *path, char **args, t_exec_control_block *exec_cb)
{
	if (!path)
		cleanup(access_exit_code(0, READ));
	default_signals();
	if (dup_stdio(exec_cb->stdio))
		cleanup(EXIT_FAILURE);
	close_pipes(exec_cb->pipes, exec_cb->num_commands - 1);
	execve(path, args, __environ);
	perror("execve");
	cleanup(EXIT_FAILURE);
}

int	simple_command(t_cmd *cmd, t_exec_control_block *exec_cb)
{
	char	**args;
	char	*path;
	pid_t	pid;

	if (!cmd->args)
		return (0);
	args = build_argument_list(cmd->args);
	path = command_path(args[0]);
	ignore_signals();
	pid = fork();
	if (0 > pid)
	{
		perror("fork");
		return (1);
	}
	if (0 == pid)
		child(path, args, exec_cb);
	exec_cb->pids[exec_cb->curr_pid++] = pid;
	close_stdio(exec_cb->stdio);
	return (0);
}
