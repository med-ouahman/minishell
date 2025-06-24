/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_atom.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 12:09:48 by mouahman          #+#    #+#             */
/*   Updated: 2025/06/24 12:10:32 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

AST *parse_atom(TOKEN **tokens)
{
	TOKEN	*token;
	AST		*atom;

	token = peek(*tokens);
	if (token->type != OPENPAR)
		return (parse_command(tokens));
	consume(tokens);
	atom = parse_or_command(tokens);
	token = peek(*tokens);
	if (!token || token->type != CLOSEPAR)
	{
		printf("Error\n");
		return (NULL);
	}
	return (atom);
}
