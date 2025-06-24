/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 12:08:45 by mouahman          #+#    #+#             */
/*   Updated: 2025/06/24 12:09:40 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

static AST *build_pipeline(AST *left, AST *right)
{
	AST	 *pipe_node;
	t_ast_binary	 *pip;

	pipe_node = malloc(sizeof(*pipe_node));
	if (!pipe_node)
		return (NULL);
	pipe_node->node_type = PIPE;
	pip = malloc(sizeof(t_ast_binary));
	if (!pip)
		return (NULL);
	pip->left = left;
	pip->right = right;
	pip->type = pipe_node->node_type = PIPE;
	pipe_node->data = pip;
	return (pipe_node);
}

AST *parse_pipeline(TOKEN **tokens)
{
	TOKEN	*token;
	AST		*left;
	AST		*right;

	left = parse_atom(tokens);
	token = peek(*tokens);
	while (token && token->type == PIPE)
	{
		consume(tokens);
		right = parse_atom(tokens);
		left = build_pipeline(left, right);
		token = peek(*tokens);
	}
	return (left);
}
