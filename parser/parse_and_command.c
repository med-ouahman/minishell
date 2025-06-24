/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_and_command.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 12:11:47 by mouahman          #+#    #+#             */
/*   Updated: 2025/06/24 12:12:33 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

static AST *build_and_command(AST *left, AST *right)
{
	AST				*and_node;
	t_ast_binary	*and;

	and = malloc(sizeof(*and));
	garbage_collector(and, ALLOC);
	and->left = left;
	and->right = right;
	and_node = malloc(sizeof(*and_node));
	garbage_collector(and_node, ALLOC);
	and_node->data = and;
	and_node->node_type = AND;
	return (and_node);
}


AST *parse_and_command(TOKEN **tokens)
{
	TOKEN	*token;
	AST	  *left;
	AST	  *right;

	left = parse_pipeline(tokens);
	token = peek(*tokens);
	while (token && token->type == AND)
	{
		consume(tokens);
		right = parse_pipeline(tokens);
		left = build_and_command(left, right);
		token = peek(*tokens);
	}
	return (left);
}
