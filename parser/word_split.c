/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 15:54:43 by mouahman          #+#    #+#             */
/*   Updated: 2025/06/02 15:55:17 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/tokenizer.h"

int	has_spaces(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (ft_isspace(s[i]))
			return (1);
		i++;
	}
	return (0);
}

static TOKEN	*create_node(char *s)
{
	TOKEN	*node;

	node = malloc(sizeof(*node));
	if (NULL == node)
		return (NULL);
	node->token = malloc(sizeof(*node->token));
	if (NULL == node->token)
		return (NULL);
	node->token = s;
	node->split = 0;
	node->end = -1;
	node->start = -1;
	node->join_with = NULL;
	node->p_quote = -1;
	node->line = NULL;
	return (node);
}

int	add_splitted_tokens(TOKEN **tokens, TOKEN *node, char **split)
{
	TOKEN	*prev;
	TOKEN	*next;
	TOKEN	*new_node;

	next = node->next;
	prev = get_prev_node(*tokens, node);
	while (*split)
	{
		new_node = create_node(*split);
		if (NULL == new_node)
			return (-1);
		prev->next = new_node;
		prev = new_node;
		split++;
	}
	prev->next = next;
	return (0);
}

int	word_split(TOKEN **tokens, char *charset)
{
	TOKEN	*curr;
	char	**split;

	curr = *tokens;
	while (curr)
	{
		if (curr->split)
		{
			if (0 == has_spaces(curr->token))
			{
				curr = curr->next;
				continue ;
			}
			split = ft_split2(curr->token, charset);
			if (NULL == split)
				return (-1);
			add_splitted_tokens(tokens, curr, split);
		}
		curr = curr->next;
	}
	return (0);
}
