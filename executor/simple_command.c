/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 11:11:30 by mouahman          #+#    #+#             */
/*   Updated: 2025/07/06 14:31:58 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/executor.h"

int	simple_command(t_cmd *cmd, t_exec_control_block *exec_cb)
{
	char	**args;
	char	*path;
	pid_t	pid;

	if (!cmd->args)
		return (0);
	args = build_argument_list(cmd->args);
	if (!args)
		return (-1);
	path = command_path(exec_cb->paths, args[0]);
	if (!path)
		return (-1);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (0 > pid)
		return (-1);
	if (0 == pid)
	{
		signal(SIGINT, SIG_DFL);
		dup_stdio(exec_cb->stdio);
		close_pipes(exec_cb->pipes, exec_cb->pid_size - 1);
		execve(path, args, __environ);
		exit(EXIT_FAILURE);
	}
	exec_cb->pids[exec_cb->curr_pid] = pid;
	exec_cb->curr_pid++;
	close_stdio(exec_cb->stdio);
	return (0);
}
