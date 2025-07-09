/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_and_command.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 12:11:47 by mouahman          #+#    #+#             */
/*   Updated: 2025/07/05 15:48:09 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

static AST *build_and_command(AST *left, AST *right)
{
	AST				*and_node;
	t_ast_binary	*and;

	and = malloc(sizeof *and);
	garbage_collector(and, COLLECT);
	and->left = left;
	and->right = right;
	and_node = malloc(sizeof *and_node);
	garbage_collector(and_node, COLLECT);
	and_node->data = and;
	and_node->node_type = AND;
	return (and_node);
}


AST *parse_and_command(TOKEN **tokens)
{
	TOKEN	*token;
	AST	  *left;
	AST	  *right;

	if (!peek(*tokens) || error(0, READ))
		return (NULL);
	left = parse_pipeline(tokens);
	if (!left)
		return (NULL);
	token = peek(*tokens);
	while (token && token->type == AND)
	{
		consume(tokens);
		right = parse_pipeline(tokens);
		if (error(0, READ))
			return (NULL);
		if (!right)
		{
			syntax_error(AND, peek(*tokens));
			return (NULL);
		}
		left = build_and_command(left, right);
		token = peek(*tokens);
	}
	return (left);
}
