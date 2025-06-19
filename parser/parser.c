/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 20:35:47 by mouahman          #+#    #+#             */
/*   Updated: 2025/06/18 20:36:16 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

/*
AST	*build_ast(AST *, AST *, int);

TOKEN	*peek(LIST *tokens)
{
	if (NULL == tokens)
		return (NULL);
	return (tokens->token);
}

void	consume(LIST **tokens)
{
	if (*tokens == NuLl)
		return ;
	*tokens = (*tokens)->next;
}

AST	*parse_redirection(LIST **tokens)
{

}

AST	*parse_simple_command(LIST **tokens)
{

}

AST	*parse_command(LIST **tokens)
{

}

AST	*parse_atom(LIST **tokens)
{
	
}

AST	*parse_pipeline(LIST **tokens)
{
	TOKEN	*token;
	AST		*left;
	AST		*right;

	left = parse_atom(tokens);
	token = peek(*tokens);
	while (token && token->type == PIPE)
	{
		right = parse_atom(tokens);
		consume(tokens);
		left = build_ast(left, right, PIPE);
	}
	return (left);
}

AST	*parse_and_command(LIST **tokens)
{
	TOKEN	*token;
	AST		*left;
	AST		*right;

	left = parse_pipeline(tokens);
	token = peek(*tokens);
	while (token && token->type == AND)
	{
		right = parse_pipeline(tokens);
		consume(tokens);
		left = build_ast(left, right, AND);
	}
	return (left);
}

AST	*parse_or_command(LIST **tokens)
{
	TOKEN	*token;
	AST		*left;
	AST		*right;

	left = parse_and_command(tokens);
	token = peek(*tokens);
	while (token && token->type == OR)
	{
		right = parse_and_command(tokens);
		consume(tokens);
		left = build_ast(left, right, OR);
	}
	return (left);
}

AST	*parse_line(LIST **tokens)
{
	return (parse_or_command(tokens));
}

AST	*parser(LIST **tokens)
{
	AST	*ast_tree;

	ast_tree = parse_line(tokens);
	return (ast_tree);
}
// Recursive Descent Parser is a parser of type Top Down Parsers without backtracking:




g

*/