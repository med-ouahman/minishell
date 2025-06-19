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

#include "../include/tokenizer.h"

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

static LIST	*create_node(t_token *token)
{
	LIST	*node;

	node = malloc(sizeof(*node));
	if (NULL == node)
		return (NULL);
	node->token = token;
	node->next = NULL;
	return (node);
}

int	add_token(LIST **list, char *line, t_info info)
{
	t_token			*token;
	LIST	*node;

	if (info.start == info.end)
		return (0);
	token = malloc(sizeof(*token));
	if (NULL == token)
		return (-1);
	token->p_quote = info.quote;
	token->token = ft_substr(line, info.start, info.end - info.start);
	token->start = info.start == 0 ? line[info.start]: line[info.start - 1];
	token->end = line[info.end];
	token->join_with = NULL;
	node = create_node(token);
	if (NULL == node)
		return (-1);
	add_node(list, node);
	return (0);
}

LIST	*tokenizer(char *line)
{
	LIST	*token_list;
	int	i;
	t_info	info;
	
	i = 0;
	token_list = NULL;
	info.quote = 0;
	while (line[i])
	{
		if (is_quote(line[i]))
		{
			info.quote = line[i++];
			info.start = i;
			while (line[i] != info.quote && line[i])
				i++;
			if (!line[i])
				return (panic("Error: unclosed quote\n", 1), NULL);
			info.end = i;
			info.type = WORD;
			add_token(&token_list, line, info);
			if (line[i] == info.quote)
				i++;
		}
		else if (is_sep_char(line[i]) && !is_space(line[i]))
		{
			info.start = i;
			while (is_sep_char(line[i]))
				i++;
			info.end = i;
			info.type = OPERATOR;
			info.quote = 0;
			add_token(&token_list, line, info);
		}
		else
		{
			while (is_space(line[i]))
				i++;
			info.start = i;
			while (!is_sep_char(line[i]) && !is_quote(line[i]) && line[i])
				i++;
			info.end = i;
			info.type = WORD;
			info.quote = 0;
			add_token(&token_list, line, info);
		}
	}
	return (token_list);
}
