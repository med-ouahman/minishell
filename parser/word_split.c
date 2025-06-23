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

char	**word_split(TOKEN *token, char *charset)
{
	char	**split;

	split = NULL;
	split = ft_split2(token->token, charset);
	garbage_collector(split, ALLOC);
	return (split);
}
