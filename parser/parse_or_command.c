/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_or_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 12:10:40 by mouahman          #+#    #+#             */
/*   Updated: 2025/06/24 12:11:35 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

static AST *build_or_command(AST *left, AST *right)
{
	AST				*or_node;
	t_ast_binary	*or;

	or = malloc(sizeof(*or));
	garbage_collector(or, ALLOC);
	or->left = left;
	or->right = right;
	or_node = malloc(sizeof(*or_node));
	garbage_collector(or_node, ALLOC);
	or_node->data = or;
	or_node->node_type = OR;
	return (or_node);
}

AST *parse_or_command(TOKEN **tokens)
{
	TOKEN	*token;
	AST	  *left;
	AST	  *right;

	left = parse_and_command(tokens);
	token = peek(*tokens);
	while (token && token->type == OR)
	{
		consume(tokens);
		right = parse_and_command(tokens);
		left = build_or_command(left, right);
		token = peek(*tokens);
	}
	return (left);
}
