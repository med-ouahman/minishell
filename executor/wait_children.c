/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_children.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 14:16:38 by mouahman          #+#    #+#             */
/*   Updated: 2025/07/01 21:41:23 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/executor.h"

int	wait_children(pid_t *pids, t_uint num_children)
{
	int		first;
	int		status;
	t_uint	i;

	i = 0;
	first = 1;
	while (i < num_children)
	{
		if (-1 != pids[i])
		{
			waitpid(pids[i], &status, 0);
			if (WIFSIGNALED(pids[i]) && WTERMSIG(status) == SIGINT && first)
			{
				first = 0;
				rl_after_fork();
			}
		}
		i++;
	}
	status = exit_code(status);
	handle_signals();
	return (status);
}
