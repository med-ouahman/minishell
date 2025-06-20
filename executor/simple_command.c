/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 11:11:30 by mouahman          #+#    #+#             */
/*   Updated: 2025/05/22 11:13:52 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/commands.h"

int	command(char *command, char *args[], int *stdio, char *envp[])
{
	int	pid;

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
		execve(command, args, envp);
		exit(1);
	}
	return (pid);
}
