/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aid-bray <aid-bray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 05:23:53 by aid-bray          #+#    #+#             */
/*   Updated: 2025/08/15 14:28:12 by aid-bray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

int	check_ambiguous(t_redir *redir, t_token *token)
{
	if (!check_last_token_unexpanded(token))
		return (0);
	while (token)
	{
		if (token->join == SPLIT)
		{
			redir->type = AMBIGUOUS;
			return (1);
		}
		token = token->next;
	}
	return (0);
}

size_t	check_for_expand(char *input, size_t i)
{
	if (input[i] != '$')
		return (0);
	i++;
	if (input[i] == '?')
		return (i + 1);
	if (!ft_isalpha(input[i]) && input[i] != '_')
		return (0);
	while (ft_isalnum(input[i]) || input[i] == '_')
		i++;
	return (i);
}

t_token	*split_token(char *str)
{
	size_t	i;
	t_token	*tokens;
	t_info	info;

	tokens = NULL;
	i = 0;
	while (str[i])
	{
		read_token_token(str, &info, &i);
		add_token(&tokens, str, info);
		i = info.end;
	}
	return (tokens);
}

void	check_join_split(t_token *token)
{
	t_token	*prev;

	if (token->type != AMBIGUOUS && token->next && token->next->str
		&& token->next->type == AMBIGUOUS && is_space(token->next->str[0]))
		token->join = SPLIT;
	else
		token->join = JOIN;
	while (token)
	{
		prev = token;
		token = token->next;
		if (!token)
			break ;
		if (prev->type == AMBIGUOUS && prev->str && token->type != AMBIGUOUS)
		{
			if (prev->str[0] && is_space(prev->str[ft_strlen(prev->str) - 1]))
				token->join = SPLIT;
			else
				token->join = JOIN;
		}
		else
			token->join = JOIN;
	}
}

void	split_after_expand(t_token *tokens)
{
	t_token	*tmp;
	t_token	*tmp2;
	t_token	*news;
	int		split;

	tmp = tokens;
	while (tmp)
	{
		split = check_last_token_unexpanded(tmp);
		if (tmp->type == AMBIGUOUS && split)
		{
			news = new_tokens_expanded(tmp);
			collect_malloc(tmp->str, DELETE);
			tmp->str = news->str;
			tmp->type = news->type;
			tmp->join = news->join;
			tmp2 = tmp->next;
			tmp->next = news->next;
			collect_malloc(news, DELETE);
			while (tmp && tmp->next)
				tmp = tmp->next;
			tmp->next = tmp2;
		}
		tmp = tmp->next;
	}
}
