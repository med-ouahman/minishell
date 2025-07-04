/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 14:57:52 by mouahman          #+#    #+#             */
/*   Updated: 2025/07/04 15:57:06 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/tokenizer.h"

void	remove_quotes_from_token(char *_token, char quote)
{
	char	*f;
	char	*l;

	f = ft_strchr(_token, quote);
	l = ft_strrchr(_token, quote);
	if (!f || !l)
		return ;
	while (*f)
	{
		*(f - 1) = *f;
		f++;
	}
	while (*l)
	{
		*(l - 1) = *l;
		l++;
	}
}

int	quote_removal(TOKEN *tokens)
{
	while (tokens)
	{
		remove_quotes_from_token(tokens->token, tokens->p_quote);
		printf("Token: %s\n", tokens->token);
		tokens = tokens->next;
	}
	return (0);
}
