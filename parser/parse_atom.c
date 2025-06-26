/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_atom.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 12:09:48 by mouahman          #+#    #+#             */
/*   Updated: 2025/06/26 20:52:05 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

static AST	*build_atom(AST *atom)
{
	AST	*atom_node;

	atom_node = malloc(sizeof(*atom_node));
	garbage_collector(atom_node, ALLOC);
	atom_node->node_type = ATOM;
	atom_node->data = atom;
	return (atom_node);
}
AST *parse_atom(TOKEN **tokens)
{
	TOKEN	*token;
	AST		*atom;

	token = peek(*tokens);
	if (!token || error(0, READ))
		return (NULL);
	if (token->type != OPENPAR)
	{
		atom = parse_command(tokens);
		if (error(0, READ))
			return (NULL);
		token = peek(*tokens);
		return (atom);
	}
	consume(tokens);
	atom = parse_or_command(tokens);
	if (error(0, READ))
		return (NULL);
	if (!atom)
	{
		token = peek(*tokens);
		error(1, WRITE);
		syntax_error(ATOM, token);
		return (NULL);
	}
	token = peek(*tokens);
	if (!token || token->type != CLOSEPAR)
	{
		error(1, WRITE);
		syntax_error(ATOM, token);
		return (NULL);
	}
	consume(tokens);
	return (build_atom(atom));
}
