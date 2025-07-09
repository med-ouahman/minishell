/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_or_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 12:10:40 by mouahman          #+#    #+#             */
/*   Updated: 2025/07/02 11:09:51 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

static AST *build_or_command(AST *left, AST *right)
{
	AST				*or_node;
	t_ast_binary	*or;

	or = malloc(sizeof *or);
	garbage_collector(or, COLLECT);
	or->left = left;
	or->right = right;
	or_node = malloc(sizeof *or_node);
	garbage_collector(or_node, COLLECT);
	or_node->data = or;
	or_node->node_type = OR;
	return (or_node);
}

AST *parse_or_command(TOKEN **tokens)
{
	TOKEN	*token;
	AST	  *left;
	AST	  *right;

	if (!peek(*tokens) || error(0, READ))
		return (NULL);
	left = parse_and_command(tokens);
	if (!left)
		return (NULL);
	token = peek(*tokens);
	while (token && token->type == OR)
	{
		consume(tokens);
		right = parse_and_command(tokens);
		if (error(0, READ))
			return (NULL);
		if (!right)
		{
			syntax_error(OR, peek(*tokens));
			return (NULL);
		}
		left = build_or_command(left, right);
		token = peek(*tokens);
	}
	return (left);
}
