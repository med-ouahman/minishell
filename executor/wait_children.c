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

int	wait_children(pid_t *pids, int num_children)
{
	int	status;
	int	i;

	i = 0;
	while (i < num_children)
	{
		waitpid(pids[i], &status, 0);
		i++;
	}
	status = exit_code(status);
	return (status);
}
