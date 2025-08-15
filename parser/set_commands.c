/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aid-bray <aid-bray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 05:24:12 by aid-bray          #+#    #+#             */
/*   Updated: 2025/08/14 09:19:59 by aid-bray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

static void	add_to_args(t_list **args, t_token *token)
{
	t_list	*new;

	new = ft_lstnew(token->str);
	collect_malloc(new, CHECK);
	ft_lstadd_back(args, new);
}

static int	add_to_redirection(t_list **redir, t_token *token)
{
	t_list	*new;
	t_redir	*tmp;

	tmp = malloc (sizeof(t_redir));
	collect_malloc(tmp, CHECK);
	tmp->type = token->type;
	tmp->file = token->next->str;
	tmp->heredoc_fd = -1;
	if (tmp->type == RED_HERDOC)
	{
		tmp->heredoc_fd = parser_heredoc(tmp->file);
		if (tmp->heredoc_fd < 0)
		{
			helper_heredoc(NULL);
			return (-1);
		}
	}
	new = ft_lstnew(tmp);
	collect_malloc(new, CHECK);
	collect_malloc(token->str, DELETE);
	ft_lstadd_back(redir, new);
	return (0);
}

static t_list	*add_next_cmd(t_list **cmd, t_token *token)
{
	t_cmd	*new_cmd;
	t_list	*new_noued;

	new_cmd = ft_calloc(1, sizeof(t_cmd));
	collect_malloc(new_cmd, CHECK);
	new_noued = ft_lstnew(new_cmd);
	collect_malloc(new_noued, CHECK);
	if (token)
		collect_malloc(token->str, DELETE);
	ft_lstadd_back(cmd, new_noued);
	return (new_noued);
}

t_list	*set_cmd(t_token *token)
{
	t_list	*cmd;
	t_list	*tmp;
	t_cmd	*cur_cmd;

	cmd = NULL;
	tmp = add_next_cmd(&cmd, NULL);
	helper_heredoc(cmd);
	while (token)
	{
		cur_cmd = (t_cmd *)tmp->content;
		if (token->type == WORD)
			add_to_args(&cur_cmd->args, token);
		else if (token->type == PIPE)
			tmp = add_next_cmd(&cmd, token);
		else if (is_redirection(token))
		{
			if (add_to_redirection(&cur_cmd->redir, token))
				return (NULL);
			token = token->next;
		}
		token = token->next;
	}
	return (cmd);
}
