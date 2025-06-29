/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 09:17:09 by mouahman          #+#    #+#             */
/*   Updated: 2025/06/26 21:19:16 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

AST *parser(TOKEN *tokens)
{
	AST *parse_t;

	error(0, WRITE);
	parse_t = parse_or_command(&tokens);
	if (error(0, READ))
		return (NULL);
	if (tokens != NULL)
	{
		syntax_error(-1, peek(tokens));
		return (NULL);
	}
	return (parse_t);
}
