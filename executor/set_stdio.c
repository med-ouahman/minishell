/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_stdio.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 20:48:34 by mouahman          #+#    #+#             */
/*   Updated: 2025/06/20 20:49:15 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/executor.h"



int	set_stdio(t_cmd *cmd, int *stdio)
{
	t_redir	*redir;
	
	stdio[STDIN_FILENO] = STDIN_FILENO;
	stdio[STDOUT_FILENO] = STDOUT_FILENO;
	if (cmd->redirs == NULL)
		return (0);
	redir = (t_redir *)cmd->redirs->content;
	if (redir->type == REDIN || redir->type == HEREDOC)
	{
		stdio[0] = open(redir->target, O_RDONLY);
		if (0 > stdio[0])
			return (-1);
	}
	else if (redir->type == REDOUT)
	{
		stdio[1] = open(redir->target, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (0 > stdio[1])
			return (-1);
	}
	else if (redir->type == REDOUTAPP)
	{
		stdio[1] = open(redir->target, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (0 > stdio[1])
			return (-1);
	}
	return (0);
}
