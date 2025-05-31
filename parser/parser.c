/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:58:42 by mouahman          #+#    #+#             */
/*   Updated: 2025/05/15 10:21:24 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

void	add_node(LIST **list, LIST *node)
{
	LIST	*last;

	if (NULL == *list)
	{
		*list = node;
		return ;
	}
	last = *list;
	while (last->next)
		last = last->next;
	last->next = node;
}

t_token_list	*create_node(t_token *token)
{
	t_token_list	*node;

	node = malloc(sizeof(*node));
	if (NULL == node)
		return (NULL);
	node->token = token;
	node->next = NULL;
	return (node);
}

int	add_token(t_token_list **list, char *line, int start, int end)
{
	t_token			*token;
	t_token_list	*node;

	if (start == end)
		return (0);
	token = malloc(sizeof(*token));
	if (NULL == token)
		return (-1);
	token->p_quote = is_quote(line[start - 1]) ? line[start - 1]: 0;
	token->token = ft_substr(line, start, end - start);
	token->start = start == 0 ? line[start]: line[start - 1];
	token->end = line[end];
	token->next = NULL;
	token->join_with = NULL;
	node = create_node(token);
	if (NULL == node)
		return (-1);
	add_node(list, node);
	return (0);
}

t_token_list	*create_token_list(char *line)
{
	t_token_list	*token_list;
	int	i, j;
	int	quote;
	
	i = 0;
	token_list = NULL;
	quote = 0;
	while (line[i])
	{
		if (is_quote(line[i]))
		{
			quote = line[i++];
			j = i;
			while (line[i] != quote && line[i])
				i++;
			if (!line[i])
				return (panic("Error: unclosed quote\n", 1), NULL);
			add_token(&token_list, line, j, i);
			if (line[i] == quote)
				i++;
		}
		else if (is_sep_char(line[i]) && !is_space(line[i]))
		{
			j = i;
			while (is_sep_char(line[i]))
				i++;
			add_token(&token_list, line, j, i);
		}
		else
		{
			while (is_space(line[i]))
				i++;
			j = i;
			while (!is_sep_char(line[i]) && !is_quote(line[i]) && line[i])
				i++;
			add_token(&token_list, line, j, i);
		}
	}
	return (token_list);
}
