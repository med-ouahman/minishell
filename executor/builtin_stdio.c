/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_stdio.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 12:07:58 by mouahman          #+#    #+#             */
/*   Updated: 2025/07/01 12:12:42 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/executor.h"

int	preserve_stdio(int *old_stdio, int *stdio)
{
	old_stdio[0] = STDIN_FILENO;
	old_stdio[1] = STDOUT_FILENO;
	if (STDIN_FILENO != stdio[0])
	{
		old_stdio[0] = dup(STDIN_FILENO);
		if (old_stdio[0] < 0)
		{
			print_err1(strerror(errno));
			return (-1);
		}
	}
	if (STDOUT_FILENO != stdio[1])
	{
		old_stdio[1] = dup(STDOUT_FILENO);
		if (old_stdio[1] < 0)
		{
			print_err1(strerror(errno));
			return (-1);
		}
	}
	return (0);
}

int	restore_stdio(int *old)
{
	if (old[0] != STDIN_FILENO)
	{
		if (0 > dup2(old[0], STDIN_FILENO))
		{
			print_err1(strerror(errno));
			return (-1);
		}
		close(old[0]);
	}
	if (old[1] != STDOUT_FILENO)
	{
		if (0 > dup2(old[1], STDOUT_FILENO))
		{
			print_err1(strerror(errno));
			return (-1);
		}
		close(old[1]);
	}
	return (0);
}
