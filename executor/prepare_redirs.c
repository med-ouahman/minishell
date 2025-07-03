/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_redirs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 20:48:34 by mouahman          #+#    #+#             */
/*   Updated: 2025/07/01 12:23:18 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/executor.h"

static int	redirection_flags(int redir_type)
{
	if (redir_type == REDIN || redir_type == HEREDOC)
		return (O_RDONLY);
	if (redir_type == REDOUT)
		return (O_CREAT | O_WRONLY | O_TRUNC);
	if (redir_type == REDOUTAPP)
		return (O_CREAT | O_WRONLY | O_APPEND);
	return (-1);
}

static int	_open_mode(int type)
{
	if (type == REDOUTAPP || type == REDOUT)
		return (OPEN_MODE);
	return (-1);
}

static int	open_file(char *__filename, int _flags, int __mode__)
{
	int	fd;

	if (__mode__ < 0)
	{
		fd = open(__filename, _flags);
	}
	else
	{
		fd = open(__filename, _flags, __mode__);
	}
	if (fd < 0)
	{
		print_file_error(__filename, strerror(errno));
		return (-1);
	}
	return (fd);
}

int	prepare_redirs(t_cmd *cmd, int *stdio)
{
	t_redir	*redir;
	t_list	*redirs;
	int		fd;

	if (cmd->redirs == NULL)
		return (0);
	redirs = cmd->redirs;
	while (redirs)
	{
		redir = (t_redir *)cmd->redirs->content;
		fd = open_file(redir->target, redirection_flags(redir->type), _open_mode(redir->type));
		if (fd < 0)
		{
			access_exit_code(1, WRITE);
			return (-1);
		}
		if (redir->type == REDIN || redir->type == HEREDOC)
			stdio[0] = fd;
		else
			stdio[1] = fd;
		redirs = redirs->next;
	}
	return (0);
}
