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

#include "../includes/parse.h"

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
	token->token = ft_substr(line, start, end - start);
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
	return (add_left(*tree, node));
}
int	is_space(int c)
{
	return (' ' == c);
}

int	is_sep(int c)
{
	return ('|' == c || '>' == c || '<' == c || ' ' == c || '&' == c);
}

static int is_quote(int c)
{
	return ('"' == c || '\'' == c);
}

t_parse_tree	*parser(char *line)
{
	t_parse_tree	*parse_tree;
	unsigned int	i, j;
	int	quote = 0;
	
	i = 0;
	parse_tree = NULL;
	while (line[i])
	{
		if (is_quote(line[i]))
		{
			quote = line[i++];
			j = i;
			while (line[i] != quote && line[i])
				i++;
			if (!line[i])
				return (panic("Error: unclosed quote", 1), NULL);
			add_token(&parse_tree, line, j, i);
			if (line[i] == quote)
				i++;
		}
		else if (is_sep(line[i]) && ' ' != line[i])
		{
			j = i;
			while (is_sep(line[i]))
				i++;
			add_token(&parse_tree, line, j, i);
		}
		else
		{
			while (is_space(line[i]))
				i++;
			j = i;
			while (!is_sep(line[i]) && !is_quote(line[i]) && line[i])
				i++;
			add_token(&parse_tree, line, j, i);
		}
	}
	return (parse_tree);
}
