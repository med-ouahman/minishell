/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 12:08:45 by mouahman          #+#    #+#             */
/*   Updated: 2025/07/05 15:47:31 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

static AST *build_pipeline(AST *left, AST *right)
{
	AST	 			*pipe_node;
	t_ast_binary	*pip;

	pipe_node = malloc(sizeof *pipe_node);
	if (!pipe_node)
		return (NULL);
	pipe_node->node_type = PIPE;
	pip = malloc(sizeof(*pip));
	if (!pip)
		return (NULL);
	pip->left = left;
	pip->right = right;
	pipe_node->data = pip;
	return (pipe_node);
}

AST *parse_pipeline(TOKEN **tokens)
{
	TOKEN	*token;
	AST		*left;
	AST		*right;

	if (!peek(*tokens) || error(0, READ))
		return (NULL);
	left = parse_atom(tokens);
	if (!left)
		return (NULL);
	token = peek(*tokens);
	while (token && token->type == PIPE)
	{
		consume(tokens);
		right = parse_atom(tokens);
		if (error(0, READ))
			return (NULL);
		if (!right)
		{
			syntax_error(PIPE, peek(*tokens));
			return (NULL);
		}
		left = build_pipeline(left, right);
		token = peek(*tokens);
	}
	return (left);
}
