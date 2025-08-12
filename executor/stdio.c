/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdio.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aid-bray <aid-bray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 12:05:38 by mouahman          #+#    #+#             */
/*   Updated: 2025/08/06 09:54:32 by aid-bray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/executor.h"

int	set_stdio(t_exec_control_block *exec_cb, t_uint curr)
{
	if (exec_cb->stdio[0] == STDIN_FILENO && (curr > 0))
	{
		exec_cb->stdio[0] = exec_cb->pipes[curr - 1].pipefds[0];
	}
	if (exec_cb->stdio[1] == STDOUT_FILENO
		&& (curr < exec_cb->num_commands - 1))
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

int	close_stdio(int *stdio)
{
	if (stdio[0] != STDIN_FILENO && stdio[0] != -1)
	{
		close(stdio[0]);
	}
	if (stdio[1] != STDOUT_FILENO && stdio[1] != -1)
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
			perror("dup2");
			return (-1);
		}
		close(stdio[0]);
	}
	if (STDOUT_FILENO != stdio[1])
	{
		if (0 > dup2(stdio[1], STDOUT_FILENO))
		{
			close(stdio[0]);
			perror("dup3");
			return (-1);
		}
		close(stdio[1]);
	}
	return (0);
}
