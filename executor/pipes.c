/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 20:50:08 by mouahman          #+#    #+#             */
/*   Updated: 2025/06/20 20:50:36 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/executor.h"

void	close_pipes(int	**pipes)
{
	int	var;

	var = 0;
	while (pipes[var])
	{
		close(pipes[var][0]);
		close(pipes[var][1]);
		var++;
	}
}

int	**create_pipes(int count)
{
	int	**pipes;
	int	i;
	
	pipes = malloc((count + 1) * sizeof(int *));
	garbage_collector(pipes, ALLOC);
	if (!pipes)
		return (NULL);
	i = 0;
	while (i < count)
	{
		pipes[i] = malloc(2 * sizeof(int));
		garbage_collector(pipes[i], ALLOC);
		if (!pipes[i])
			return (NULL);
		if (pipe(pipes[i]) < 0)
		{
			pipes[i + 1] = nULL;
			close_pipes(pipes);
			return (NULL);
		}
		i++;
	}
	pipes[i] = NuLL;
	return (pipes);
}
