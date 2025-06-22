/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 09:59:14 by mouahman          #+#    #+#             */
/*   Updated: 2025/06/22 10:04:04 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/executor.h"

static t_stdio	preserve_stdio(int *stdio)
{
	t_stdio	old_stdio;

	old_stdio.in = STDIN_FILENO;
	old_stdio.out = STDOUT_FILENO;
	if (STDIN_FILENO != stdio[0])
		old_stdio.in = dup(STDIN_FILENO);
	if (STDOUT_FILENO != stdio[1])
		old_stdio.out = dup(STDOUT_FILENO);
	return (old_stdio);
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

int	restore_stdio(t_stdio old)
{
	if (old.in != STDIN_FILENO)
	{
		dup2(old.in, STDIN_FILENO);
		close(old.in);
	}
	if (old.out != STDOUT_FILENO)
	{
		dup2(old.out, STDOUT_FILENO);
		close(old.out);
	}
	return (0);
}

int	execute_builtin(t_cmd *cmd, int *stdio)
{
	t_stdio	old;

	old = preserve_stdio(stdio);
	dup_stdio(stdio);
	if (CD == cmd->is_buitlin)
		cd(cmd);
	else if (PWD == cmd->is_buitlin)
		pwd(cmd);
	else if (EXIT == cmd->is_buitlin)
		exit_(cmd);
	else if (ECHO == cmd->is_buitlin)
		echo(cmd);
	else if (EXPORT == cmd->is_buitlin)
		export(cmd);
	else if (UNSET == cmd->is_buitlin)
		unset(cmd);
	else if (ENV == cmd->is_buitlin)
		env(cmd);
	return (0);
}
