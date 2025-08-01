/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_redirs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 20:48:34 by mouahman          #+#    #+#             */
/*   Updated: 2025/07/06 11:06:51 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/executor.h"

static int	redirection_flags(int redir_type)
{
	if (AMBIGUES == redir_type)
		return (AMBIGUES);
	if (redir_type == RED_INP)
		return (O_RDONLY);
	if (redir_type == RED_OUT)
		return (O_CREAT | O_WRONLY | O_TRUNC);
	if (redir_type == RED_APPOUT)
		return (O_CREAT | O_WRONLY | O_APPEND);
	return (-1);
}

static int	_open_mode(int type)
{
	if (type == RED_APPOUT || type == RED_OUT)
		return (OPEN_MODE);
	return (-1);
}

static int	open_file(char *__filename, int _flags, int __mode__)
{
	int	fd;

	if (AMBIGUES == _flags)
	{
		print_err2(__filename, "ambiguous redirect");
		return (-1);
	}
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
		print_err2(__filename, strerror(errno));
		return (-1);
	}
	return (fd);
}

int	prepare_redirs(t_list *redirs, int *stdio)
{
	t_redir	*redir;
	int		fd;

	while (redirs)
	{
		redir = (t_redir *)redirs->content;
		if (redir->type == RED_HERDOC)
			fd = redir->heredoc_fd;
		else
			fd = open_file(redir->file,
					redirection_flags(redir->type), _open_mode(redir->type));
		if (fd < 0)
			return (-1);
		stdio[(redir->type == RED_OUT || redir->type == RED_APPOUT)] = fd;
		if (redirs->next)
			close(fd);
		redirs = redirs->next;
	}
	return (0);
}
