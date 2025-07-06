/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 11:11:30 by mouahman          #+#    #+#             */
/*   Updated: 2025/07/06 11:17:43 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/executor.h"

char	**build_args(t_list *arg_list)
{
	char	**args;
	int		i;

	if (!arg_list)
		return (NULL);
	args = malloc((ft_lstsize(arg_list) + 1) * sizeof(char *));
	garbage_collector(args, COLLECT);
	i = 0;
	while (arg_list)
	{
		args[i] = (char *)arg_list->content;
		arg_list = arg_list->next;
		i++;
	}
	args[i] = null;
	return (args);
}

int	simple_command(t_cmd *cmd, t_exec_control_block *exec_cb)
{
	char	**args;
	char	*path;
	pid_t	pid;

	args = build_args(cmd->args);
	if (!args)
		return (-1);
	path = command_path(exec_cb->paths, (char *)cmd->args->content);
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
