/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:36:37 by mouahman          #+#    #+#             */
/*   Updated: 2025/06/20 15:36:55 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/executor.h"

int	set_stdio(t_cmd *cmd, int stdio[])
{
	t_redir	*redir;
	
	redir = (t_cmd *)redir;
	stdio[STDIN_FILENO] = STDIN_FILENO;
	stdio[STDOUT_FILENO] = STDOUT_FILENO;
	if (redir->type == REDIN || redir->type == HEREDOC)
	{
		stdio[0] = open(redir->target, O_RDONLY);
		if (0 > stdio[0])
			return (-1);
	}
	else if (redir->type == REDOUT)
	{
		stdio[1] = open(redir->target, O_CREAT | O_WRONLY | O_TRUNC);
		if (0 > stdio[1])
			return (-1);
	}
	else if (redir->type == REDOUTAPP)
	{
		stdio[1] = open(redir->target, O_CREAT | O_WRONLY | O_APPEND);
		if (0 > stdio[1])
			return (-1);
	}
	return (0);
}

int executor(t_list *exec_list)
{
	t_list	*curr;
	t_cmd	*cmd;
	int		stdio[2];

	curr = exec_list;
	while (curr)
	{
		cmd = (t_cmd *)curr->content;
		set_stdio(cmd, stdio);
		curr = curr->next;
	}
}
