/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_join_tokens.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aid-bray <aid-bray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 05:23:47 by aid-bray          #+#    #+#             */
/*   Updated: 2025/08/14 10:55:36 by aid-bray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

int	check_last_token_unexpanded(t_token *tokens)
{
	size_t	i;

	while (tokens->next)
		tokens = tokens->next;
	i = 0;
	if (tokens->type == AMBIGUOUS || tokens->type == D_QUOTE
		|| tokens->type == S_QUOTE)
		return (1);
	while (tokens->str && tokens->str[i])
	{
		if (tokens->str[i] == '$')
			return (0);
		i++;
	}
	return (1);
}

t_token	*prepar_args(t_list	**arg, t_token *tokens, int split)
{
	t_list	*new;
	char	*new_arg;

	new_arg = NULL;
	while (tokens)
	{
		new_arg = ft_join(new_arg, 1, tokens->str, 1);
		tokens = tokens->next;
		if (split && tokens && tokens->join == SPLIT)
			break ;
	}
	new = ft_lstnew(new_arg);
	collect_malloc(new, CHECK);
	ft_lstadd_back(arg, new);
	return (tokens);
}

void	join_tokens_redir(t_redir *redir, t_token *tokens)
{
	char	*new_token;

	new_token = NULL;
	while (tokens)
	{
		new_token = ft_join(new_token, 1, tokens->str, 1);
		tokens = tokens->next;
	}
	if (!new_token)
	{
		redir->type = AMBIGUOUS;
		return ;
	}
	collect_malloc(redir->file, DELETE);
	redir->file = new_token;
}

t_list	*join_tokens_args(t_list **arg, t_token *tokens, int split)
{
	t_list	*new_arg;
	t_list	*tmp_arg;
	t_list	*tmp_free;
	t_token	*tmp;

	tmp = tokens;
	new_arg = NULL;
	while (tmp)
		tmp = prepar_args(&new_arg, tmp, split);
	collect_malloc((*arg)->content, DELETE);
	(*arg)->content = new_arg->content;
	tmp_arg = (*arg)->next;
	tmp_free = new_arg;
	if (new_arg->next)
	{
		(*arg)->next = new_arg->next;
		while (new_arg->next)
			new_arg = new_arg->next;
		new_arg->next = tmp_arg;
		collect_malloc(tmp_free, DELETE);
		return (new_arg);
	}
	collect_malloc(tmp_free, DELETE);
	return (*arg);
}
