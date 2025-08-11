/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aid-bray <aid-bray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 05:23:53 by aid-bray          #+#    #+#             */
/*   Updated: 2025/08/10 14:23:25 by aid-bray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

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
	t_token	*tmp;

	if (token->type != AMBIGUES && token->next && token->next->type == AMBIGUES
		&& token->next->str && is_space(token->next->str[0]))
		token->join = SPLIT;
	else
		token->join = JOIN;
	while (token)
	{
		tmp = token;
		token = token->next;
		if (!token)
			break ;
		if (tmp->type == AMBIGUES && tmp->str && token->type != AMBIGUES)
		{
			if (is_space(tmp->str[ft_strlen(tmp->str) - 1]))
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
		if (tmp->type == AMBIGUES && split)
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
