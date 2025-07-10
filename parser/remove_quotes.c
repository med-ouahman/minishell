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

void	remove_quotes_from_token(char *_token, char quote, size_t len)
{
	char	*f;
	char	*l;

	if (!_token || !quote)
		return ;
	f = ft_strchr(_token, quote);
	if (!f)
		return ;
	l = ft_strchr(f + 1, quote);
	if (!l || f == l)
		return ;
	while (*f)
	{
		*f = *(f + 1);
		f++;
	}
	while (*l)
	{
		*(l - 1) = *l;
		l++;
	}
	_token[len -= 2] = 0;
	if (is_quote(*_token) && _token[len - 1] == *_token)
		return ;
	quote = find_next_quote(_token);
	f = ft_strchr(_token, quote);
	remove_quotes_from_token(f, quote, ft_strlen(f));	
}

int	quote_removal(TOKEN *token)
{
	remove_quotes_from_token(token->token,
			find_next_quote(token->token),
			ft_strlen(token->token));
	return (0);
}
