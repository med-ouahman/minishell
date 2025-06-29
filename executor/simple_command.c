/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 11:11:30 by mouahman          #+#    #+#             */
/*   Updated: 2025/06/29 11:01:10 by mouahman         ###   ########.fr       */
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
	garbage_collector(args, ALLOC);
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

int	close_stdio(int stdio[])
{
	if (stdio[0] != STDIN_FILENO) {
		close(stdio[0]);
	}
	if (stdio[1] != STDOUT_FILENO) {
		close(stdio[1]);
	}
	return (0);
}

int	simple_command(t_cmd *cmd, int *stdio, char **pvs)
{
	int		pid;
	char	**args;
	char	*path;

	if (cmd->is_buitlin)
		return (execute_builtin(cmd, stdio));
	args = build_args(cmd->args);
	if (!args)
		return (-1);
	path = command_path(pvs, (char *)cmd->args->content);
	if (!path)
		return (-1);
	pid = fork();
	if (0 > pid)
		return (-1);
	if (0 == pid)
	{
		if (STDIN_FILENO != stdio[0])
		{
			dup2(stdio[0], STDIN_FILENO);
			close(stdio[0]);
		}
		if (STDOUT_FILENO != stdio[1])
		{
			dup2(stdio[1], STDOUT_FILENO);
			close(stdio[1]);
		}
		execve(path, args, __environ);
		exit(1);
	}
	close_stdio(stdio);
	return (pid);
}
