/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aid-bray <aid-bray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 05:23:55 by aid-bray          #+#    #+#             */
/*   Updated: 2025/07/31 06:55:30 by aid-bray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

static int	expand_redir(t_list *list_redir)
{
	t_list	*tmp;
	t_redir	*redir;
	t_token	*tokens;

	tmp = list_redir;
	tokens = NULL;
	while (tmp)
	{
		redir = (t_redir *)tmp->content;
		if (redir->type == RED_HERDOC)
		{
			tmp = tmp->next;
			continue ;
		}
		tokens = split_token(redir->file);
		expand_tokens(tokens);
		split_after_expand(tokens);
		join_tokens_redir(redir, tokens);
		free_list_token(tokens);
		tmp = tmp->next;
	}
	return (0);
}

static int	expand_args(t_list *list_args)
{
	t_list	*tmp;
	t_token	*tokens;
	int		export;

	tmp = list_args;
	tokens = NULL;
	export = 0;
	if (list_args && ft_strcmp(list_args->content, "export") == 0)
		export = 1;
	while (tmp)
	{
		tokens = split_token((char *)tmp->content);
		expand_tokens(tokens);
		if (!export || !check_valid_variable((char *)tmp->content))
			split_after_expand(tokens);
		tmp = join_tokens_args(&tmp, tokens);
		free_list_token(tokens);
		tmp = tmp->next;
	}
	return (0);
}

static void	remove_null_args(t_cmd *cmd)
{
	t_list	*args;
	t_list	*tmp;

	args = cmd->args;
	while (args && !args->content)
	{
		cmd->args = args->next;
		collect_malloc(args, DELETE);
		args = cmd->args;
	}
	while (args)
	{
		tmp = args;
		args = args->next;
		if (args && !args->content)
		{
			tmp->next = args->next;
			collect_malloc(args, DELETE);
		}
	}
}

int	expand(t_list *list_cmd)
{
	t_list	*tmp;
	t_cmd	*cmd;

	tmp = list_cmd;
	while (tmp)
	{
		cmd = (t_cmd *)tmp->content;
		expand_redir(cmd->redir);
		expand_args(cmd->args);
		remove_null_args(cmd);
		tmp = tmp->next;
	}
	return (0);
}
