/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 09:59:14 by mouahman          #+#    #+#             */
/*   Updated: 2025/06/29 13:51:51 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/executor.h"

static int	preserve_stdio(int *old_stdio, int *stdio)
{
	old_stdio[0] = STDIN_FILENO;
	old_stdio[1] = STDOUT_FILENO;
	if (STDIN_FILENO != stdio[0])
		old_stdio[0] = dup(STDIN_FILENO);
	if (STDOUT_FILENO != stdio[1])
		old_stdio[1] = dup(STDOUT_FILENO);
	return (0);
}

int	dup_stdio(int *stdio)
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
	return (0);
}

int	restore_stdio(int *old)
{
	if (old[0] != STDIN_FILENO)
	{
		dup2(old[0], STDIN_FILENO);
		close(old[0]);
	}
	if (old[1] != STDOUT_FILENO)
	{
		dup2(old[1], STDOUT_FILENO);
		close(old[1]);
	}
	return (0);
}

int	execute_builtin(t_cmd *cmd, int *stdio)
{
	int	old[2];

	preserve_stdio(old, stdio);
	dup_stdio(stdio);
	if (CD == cmd->is_buitlin)
		return (cd(cmd));
	if (PWD == cmd->is_buitlin)
		return (pwd(cmd));
	if (EXIT == cmd->is_buitlin)
		return (exit_(cmd));
	if (ECHO == cmd->is_buitlin)
		return (echo(cmd));
	if (EXPORT == cmd->is_buitlin)
		return (export(cmd));
	if (UNSET == cmd->is_buitlin)
		return (unset(cmd));
	if (ENV == cmd->is_buitlin)
		return (env(cmd));
	restore_stdio(old);
	return (0);
}
