/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 14:57:52 by mouahman          #+#    #+#             */
/*   Updated: 2025/07/04 20:50:14 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/tokenizer.h"

int	remove_quotes(char *token, int start, int end)
{
	while (token[start])
	{
		token[start] = token[start + 1];
		start++;
	}
	end--;
	while (token[end])
	{
		token[end] = token[end + 1];
		end++;
	}
	return (0);
}

int	index_of_quote(char *token, int qt, int first)
{
	int	i;

	i = 0;
	while (token[i] && token[i] != qt)
		i++;
	if (!token[i])
		return (-1);
	if (first)
		return (i);
	i++;
	while (token[i] && token[i] != qt)
		i++;
	if (!token[i])
		return (-1);
	return (i);
}

char	find_next_quote(char *s)
{
	char	*dq;
	char	*sq;

	dq = ft_strchr(s, '"');
	sq = ft_strchr(s, *"'");
	if (!dq && !sq)
		return (0);
	if (!dq)
		return (*sq);
	if (!sq)
		return (*dq);
	if (dq < sq)
		return (*dq);
	return (*sq);
}

void	remove_quotes_from_token(char *_token)
{
	int	start;
	int	end;
	int	qt;

	qt = find_next_quote(_token);
	start = index_of_quote(_token, qt, 1);
	end = index_of_quote(_token, qt, 0);
	if (start == -1)
		return ;
	remove_quotes(_token, start, end);
	remove_quotes_from_token(_token + end - 1);
}

int	quote_removal(t_list *tokens)
{
	char	*f;
	char	*l;

	f = NULL;
	l = NULL;
	while (tokens)
	{
		remove_quotes_from_token(tokens->content);
		tokens = tokens->next;
	}
	return (0);
}


