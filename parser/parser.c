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

int	add_prev_token(t_parse_tree *parse_t, t_token *token)
{
	if (parse_t->token == token)
	{
		token->prev = NULL;
		return (0);
	}
	while (parse_t && parse_t->left && parse_t->left->token != token)
	{
		parse_t = parse_t->left;
	}
	printf("chi 9alwa\n");
	token->prev = parse_t->token;
	return (0);
}

int	add_left(t_parse_tree *tree, t_parse_tree *node)
{
	t_parse_tree	*last;

	last = tree;
	while (last->left)
		last = last->left;
	last->left = node;
	return (0);
}

int	add_token(t_parse_tree **tree, char *line, int start, int end)
{
	t_token			*token;
	t_parse_tree	*node;

	if (start == end)
		return (-1);
	token = malloc(sizeof(*token));
	if (NULL == token)
		return (-1);
	token->p_quote = is_quote(line[start - 1]) ? line[start - 1]: 0;
	token->token = ft_substr(line, start, end - start);
	token->start = start;
	token->end = end;
	token->prev = NULL;
	node = malloc(sizeof(*node));
	if (NULL == node)
	{
		free(token);
		return (-1);
	}
	node->token = token;
	node->left = NULL;
	node->right = NULL;
	if (NULL == *tree)
	{
		*tree = node;
		return (0);
	}
	add_left(*tree, node);
	add_prev_token(*tree, token);
	return (0);
}

t_parse_tree	*parser(char *line)
{
	t_parse_tree	*parse_tree;
	int	i, j;
	int	quote;
	
	i = 0;
	parse_tree = NULL;
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
			add_token(&parse_tree, line, j, i);
			if (line[i] == quote)
				i++;
		}
		else if (is_sep_char(line[i]) && !is_space(line[i]))
		{
			j = i;
			// is_sep(line + i, &i);
			while (is_sep_char(line[i]))
				i++;
			add_token(&parse_tree, line, j, i);
		}
		else
		{
			while (is_space(line[i]))
				i++;
			j = i;
			while (!is_sep_char(line[i]) && !is_quote(line[i]) && line[i])
				i++;
			add_token(&parse_tree, line, j, i);
		}
	}
	return (parse_tree);
}
