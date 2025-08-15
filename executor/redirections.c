/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aid-bray <aid-bray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 02:17:14 by mouahman          #+#    #+#             */
/*   Updated: 2025/08/14 10:04:35 by aid-bray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/executor.h"

int	is_redin(int type)
{
	return (RED_INP == type || RED_HERDOC == type);
}

int	is_redout(int type)
{
	return (RED_OUT == type || RED_APPOUT == type);
}

int	open_red(t_redir *redir)
{
	int	fd;

	fd = 0;
	if (AMBIGUOUS == redir->type)
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

/*
 Do not confuse this function with Red flags. red is short for redirection.
*/

int	red_flags(int redir_type)
{
	if (redir_type == RED_OUT)
		return (O_CREAT | O_WRONLY | O_TRUNC);
	return (O_CREAT | O_WRONLY | O_APPEND);
}
