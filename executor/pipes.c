/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 20:50:08 by mouahman          #+#    #+#             */
/*   Updated: 2025/07/02 11:12:23 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/executor.h"

void	close_pipes(t_pipefd *pipes, int size)
{
	int	var;
	
	var = 0;
	while (var < size)
	{
		close(pipes[var].pipefds[0]);
		close(pipes[var].pipefds[1]);
		var++;
	}
}

t_pipefd	*create_pipes(int count)
{
	t_pipefd	*pipes;
	int			i;

	pipes = malloc(count * sizeof *pipes);
	collect_malloc(pipes, CHECK);
	i = 0;
	while (i < count)
	{
		if (pipe(pipes[i].pipefds))
		{
			perror("pipe");
			return (NULL);
		}
		i++;
	}
	return (pipes);
}
