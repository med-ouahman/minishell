/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 11:40:55 by mouahman          #+#    #+#             */
/*   Updated: 2025/07/03 14:25:45 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

int	syntax_error(int claimer, TOKEN *token)
{
	char	*s;

	if (!token)
		s = "newline";
	else
		s = token->token;
	printf("error: claimer: %s\nminishell: syntax error near unexpected token `%s'\n",
		get_token_type(claimer), s);
	error(1, WRITE);
	return (0);
}

int	error(int c, int mode)
{
	static int	err;

	if (READ == mode)
	{
		return (err);
	}
	err = c;
	return (err);
}
