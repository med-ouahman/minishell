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

static t_uint	get_red_count(t_list *redirs, int opt)
{
	t_uint	in_count;
	t_uint	out_count;
	int		type;

	in_count = 0;
	out_count = 0;
	while (redirs)
	{
		type = ((t_redir *)redirs->content)->type;
		if (type == RED_INP || type == RED_HERDOC)
			in_count++;
		else if (type == RED_OUT || type == RED_APPOUT)
			out_count++;
		redirs = redirs->next;
	}
	if (opt)
		return (out_count);
	return (in_count);
}

/*
 Do not confuse this function with Red flags. red is short for redirection.
*/

static int	red_flags(int redir_type)
{
	if (redir_type == RED_OUT)
		return (O_CREAT | O_WRONLY | O_TRUNC);
	if (redir_type == RED_APPOUT)
		return (O_CREAT | O_WRONLY | O_APPEND);
	return (-1);
}

static int	open_red(t_redir *redir)
{
	int	fd;

	fd = 0;
	if (AMBIGUES == redir->type)
	{
		print_err2(redir->file, "ambiguous redirect");
		return (-1);
	}
	if (redir->type == RED_HERDOC)
		return (redir->heredoc_fd);
	else if (redir->type == RED_INP)
		fd = open(redir->file, O_RDONLY);
	else if (redir->type == RED_OUT || redir->type == RED_APPOUT)
		fd = open(redir->file, red_flags(redir->type), OPEN_MODE);
	if (fd < 0)
	{
		print_err2(redir->file, strerror(errno));
		return (-1);
	}
	return (fd);
}

static t_uint	sss(int *stdio, int fd, t_uint count, int pos)
{
	stdio[pos] = fd;
	count--;
	if (count)
		close(fd);
	return (count);
}

int	prepare_redirs(t_list *redirs, int *stdio)
{
	t_redir	*redir;
	int		fd;
	t_uint	in_count;
	t_uint	out_count;

	in_count = get_red_count(redirs, 0);
	out_count = get_red_count(redirs, 1);
	while (redirs)
	{
		redir = (t_redir *)redirs->content;
		fd = open_red(redir);
		if (fd < 0)
			return (-1);
		if ((redir->type == RED_INP || redir->type == RED_HERDOC) && in_count)
		{
			in_count = sss(stdio, fd, in_count, 0);
		}
		else if ((redir->type == RED_OUT || redir->type == RED_APPOUT)
			&& out_count)
		{
			out_count = sss(stdio, fd, out_count, 1);
		}
		redirs = redirs->next;
	}
	return (0);
}
