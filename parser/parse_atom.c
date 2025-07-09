/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_atom.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 12:09:48 by mouahman          #+#    #+#             */
/*   Updated: 2025/07/03 12:22:55 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

static AST	*build_atom(AST *atom, t_list *redirs)
{
	t_subshell	*subshell_node;
	AST			*atom_node;

	subshell_node = malloc(sizeof *subshell_node);
	garbage_collector(subshell_node, COLLECT);
	subshell_node->ast_node = atom;
	subshell_node->redirs = redirs;
	atom_node = malloc(sizeof *atom_node);
	garbage_collector(atom_node, COLLECT);
	atom_node->data = subshell_node;
	atom_node->node_type = ATOM;
	return (atom_node);
}

static AST	*parse_parens(TOKEN **tokens)
{
	AST		*atom;
	TOKEN	*token;

	atom = parse_or_command(tokens);
	if (error(0, READ))
		return (NULL);
	if (!atom)
	{
		syntax_error(ATOM, peek(*tokens));
		return (NULL);
	}
	token = peek(*tokens);
	if (!token || token->type != CLOSEPAR)
	{
		syntax_error(ATOM, token);
		return (NULL);
	}
	consume(tokens);
	return (atom);
}

AST *parse_atom(TOKEN **tokens)
{
	TOKEN	*token;
	AST		*atom;
	t_list	*redirs;

	token = peek(*tokens);
	if (!token || error(0, READ))
		return (NULL);
	if (token->type != OPENPAR)
		return (parse_command(tokens));
	consume(tokens);
	atom = parse_parens(tokens);
	redirs = get_redirs(tokens);
	return (build_atom(atom, redirs));
}
