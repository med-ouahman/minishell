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

static void	get_last_red(t_list *redirs, t_redir **last_in, t_redir **last_out)
{
	t_redir	*redir;

	*last_in = NULL;
	*last_out = NULL;
	while (redirs)
	{
		redir = redirs->content;
		if (redir->type == RED_INP || redir->type == RED_HERDOC)
			*last_in = redir;
		else if (redir->type == RED_OUT || redir->type == RED_APPOUT)
			*last_out = redir;
		redirs = redirs->next;
	}
}

int	prepare_redirs(t_list *redirs, int *stdio)
{
	t_redir	*redir;
	t_redir	*last_in;
	t_redir	*last_out;
	int		fd;

	get_last_red(redirs, &last_in, &last_out);
	while (redirs)
	{
		redir = redirs->content;
		fd = open_red(redir);
		if (fd < 0)
			return (-1);
		stdio[(redir->type == RED_OUT || redir->type == RED_APPOUT)] = fd;
		if (is_redin(redir->type) && redir != last_in)
			close(fd);
		else if (is_redout(redir->type) && redir != last_out)
			close(fd);
		redirs = redirs->next;
	}
	return (0);
}
