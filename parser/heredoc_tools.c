/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aid-bray <aid-bray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 03:00:23 by mouahman          #+#    #+#             */
/*   Updated: 2025/08/14 10:15:17 by aid-bray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

static void	close_heredoc(t_redir *redir)
{
	if (redir->type == RED_HERDOC && redir->heredoc_fd != -1)
	{
		close(redir->heredoc_fd);
		redir->heredoc_fd = -1;
	}
}

void	helper_heredoc(t_list *lst)
{
	static t_list	*lst_cmds = NULL;
	t_list			*cmd_redir;

	if (lst)
	{
		lst_cmds = lst;
		return ;
	}
	lst = lst_cmds;
	while (lst)
	{
		cmd_redir = (t_list *)((t_cmd *)lst->content)->redir;
		while (cmd_redir)
		{
			close_heredoc(cmd_redir->content);
			cmd_redir = cmd_redir->next;
		}
		lst = lst->next;
	}
	lst_cmds = NULL;
}

int	remove_quote(char *str)
{
	int		count;
	size_t	i;
	char	quote;

	i = 0;
	quote = 0;
	count = 0;
	while (str[i + count])
	{
		if (is_quote(str[i + count]) && quote == str[i + count])
		{
			count++;
			quote = 0;
			continue ;
		}
		else if (is_quote(str[i + count]) && !quote)
		{
			quote = str[i + count];
			count++;
			continue ;
		}
		str[i] = str[i + count];
		i++;
	}
	return (str[i] = '\0', count);
}
