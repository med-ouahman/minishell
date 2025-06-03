/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 09:43:06 by mouahman          #+#    #+#             */
/*   Updated: 2025/05/29 09:43:47 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

static int	remove_joined_tokens(LIST *token_l);

static int	is_joinable(int c)
{
	return (('"' == c || *"'" == c) || (!is_space(c) && !is_sep_char(c)));
}

int	join_tokens(LIST *token_l)
{
	char	*tmp;
	LIST	*next;
	LIST	*curr;

	curr = token_l;
	while (curr && curr->next)
	{
		next = curr->next;
		if (is_joinable(curr->token->end)
			&& is_joinable(next->token->start))
		{
			if (NULL == curr->token->join_with)
			{
				tmp = curr->token->token;
				curr->token->token = ft_strjoin(curr->token->token, next->token->token);
				next->token->join_with = curr->token;
				free(tmp);
			}
			else
			{
				tmp = curr->token->join_with->token;
				curr->token->join_with->token = ft_strjoin(curr->token->join_with->token, next->token->token);
				next->token->join_with = curr->token->join_with;
				free(tmp);
			}
		}
		curr = curr->next;
	}
	remove_joined_tokens(token_l);
	return (0);
}
static int	remove_joined_tokens(LIST *token_l)
{
	LIST	*curr;
	LIST	*prev;

	curr = token_l->next;
	while (curr)
	{
		if (curr->token->join_with)
		{
			prev = get_prev_node(token_l, curr);
			if (prev)
				prev->next = curr->next;
			free(curr->token);
			free(curr);
		}
		curr = prev->next;
	}
	return (0);
}

LIST	*get_prev_node(LIST *token_l, LIST *node)
{
	while (token_l && token_l->next && token_l->next != node)
		token_l = token_l->next;
	return (token_l);
}
