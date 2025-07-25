/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 15:54:43 by mouahman          #+#    #+#             */
/*   Updated: 2025/07/04 14:38:38 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/tokenizer.h"

TOKEN	*get_prev_node(TOKEN *token_l, TOKEN *node)
{
	while (token_l && token_l->next && token_l->next != node)
		token_l = token_l->next;
	return (token_l);
}

static TOKEN	*create_node(char *s)
{
	TOKEN	*node;

	node = malloc(sizeof *node);
	if (NULL == node)
		return (NULL);
	node->token = malloc(sizeof *node->token);
	if (NULL == node->token)
		return (NULL);
	node->token = s;
	node->split = 0;
	node->end = -1;
	node->start = -1;
	node->p_quote = -1;
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

t_list	*word_split(TOKEN *token)
{
	t_list	*list;
	char	**split;

	if (!token->split)
	{
		list = ft_lstnew(token->token);
		return (list);
	}
	list = NULL;
	split = ft_split2(token->token, IFS);
	while (*split)
	{
		ft_lstadd_back(&list, ft_lstnew(*split));
		split++;
	}
	return (list);
}
