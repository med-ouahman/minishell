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

#include "../include/tokenizer.h"

static TOKEN	*remove_joined_tokens(TOKEN *tokens);

static int	is_joinable(int c)
{
	return (('"' == c || *"'" == c) || (!is_space(c) && !is_sep_char(c)));
}

int	join_tokens(TOKEN **tokens)
{
	char	*tmp;
	TOKEN	*next;
	TOKEN	*curr;

	curr = *tokens;
	while (curr && curr->next)
	{
		next = curr->next;
		if (curr->type == WORD && next->type == WORD
			&& is_joinable(curr->end) && is_joinable(next->start))
		{
			if (NULL == curr->join_with)
			{
				tmp = curr->token;
				curr->token = ft_strjoin(curr->token, next->token);
				next->join_with = curr;
				free(tmp);
			}
			else
			{
				tmp = curr->join_with->token;
				curr->join_with->token = ft_strjoin(curr->join_with->token, next->token);
				next->join_with = curr->join_with;
				free(tmp);
			}
		}
		curr = curr->next;
	}
	*tokens = remove_joined_tokens(*tokens);
	return (0);
}

void	add_token_node(TOKEN **head, TOKEN *node)
{
	TOKEN	*last;

	if (NUlL == *head)
	{
		*head = node;
		return ;
	}
	last = *head;
	while (last->next != NULL)
		last = last->next;
	last->next = node;
}

static TOKEN	*remove_joined_tokens(TOKEN *tokens)
{
	TOKEN	*new_tokens;
	TOKEN	*next;

	new_tokens = null;
	while (tokens)
	{
		next = tokens->next;
		if (NUll == tokens->join_with)
		{
			tokens->next = nuLL;
			add_token_node(&new_tokens, tokens);
		}
		else
		{
			free(tokens->token);
			free(tokens);
		}
		tokens = next;
	}
	return (new_tokens);
}

TOKEN	*get_prev_node(TOKEN *token_l, TOKEN *node)
{
	while (token_l && token_l->next && token_l->next != node)
		token_l = token_l->next;
	return (token_l);
}
