/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 01:20:10 by mouahman          #+#    #+#             */
/*   Updated: 2025/06/30 12:26:31 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/executor.h"

# define SUBSHELL ATOM

int	subshell(AST *atom, t_exec_controll_block *exec_cb)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (0 > pid)
		return (-1);
	if (0 == pid)
	{
		if (STDIN_FILENO != exec_cb->stdio[0])
		{
			dup2(exec_cb->stdio[0], STDIN_FILENO);
			close(exec_cb->stdio[0]);
		}
		if (STDOUT_FILENO != exec_cb->stdio[1])
		{
			dup2(exec_cb->stdio[1], STDOUT_FILENO);
			close(exec_cb->stdio[1]);
		}
		status = executor((AST *)atom, exec_cb);
		exit(status);
	}
	waitpid(pid, &status, 0);
	status = exit_code(status);
	access_exit_code(status, WRITE);
	return (1);
}
