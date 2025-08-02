/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdio.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 12:05:38 by mouahman          #+#    #+#             */
/*   Updated: 2025/07/01 21:03:41 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/executor.h"

int	set_stdio(t_exec_control_block *exec_cb, t_uint curr)
{
	if (exec_cb->stdio[0] == STDIN_FILENO && (curr > 0))
	{
		exec_cb->stdio[0] = exec_cb->pipes[curr - 1].pipefds[0];
	}
	if (exec_cb->stdio[1] == STDOUT_FILENO && (curr < exec_cb->pid_size - 1))
	{
		exec_cb->stdio[1] = exec_cb->pipes[curr].pipefds[1];
	}
	return (0);
}

int	reset_stdio(int *stdio)
{
	stdio[0] = STDIN_FILENO;
	stdio[1] = STDOUT_FILENO;
	return (0);
}

int	close_stdio(int stdio[])
{
	if (stdio[0] != STDIN_FILENO)
	{
		close(stdio[0]);
	}
	if (stdio[1] != STDOUT_FILENO)
	{
		close(stdio[1]);
	}
	return (0);
}

int	dup_stdio(int *stdio)
{
	if (STDIN_FILENO != stdio[0])
	{
		if (dup2(stdio[0], STDIN_FILENO) < 0)
		{
			print_err1(strerror(errno));
			return (-1);
		}
		close(stdio[0]);
	}
	if (STDOUT_FILENO != stdio[1])
	{
		if (0 > dup2(stdio[1], STDOUT_FILENO))
		{
			print_err1(strerror(errno));
			return (-1);
		}
		close(stdio[1]);
	}
	return (0);
}
