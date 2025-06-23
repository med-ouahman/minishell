/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandatory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 09:17:09 by mouahman          #+#    #+#             */
/*   Updated: 2025/06/19 09:17:11 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

AST *build_pipeline(AST *left, AST *right)
{
    AST             *pipe_node;
    t_ast_binary    *pip;

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
    TOKEN   *token;
    AST *left;
    AST *right;

    left = parse_command(tokens);
    if (!left)
    {
        errno = PARSE_ERROR;
        return (NULL);
    }
    token = peek(*tokens);
    while (token && token->type == PIPE)
    {
        consume(tokens);
        right = parse_command(tokens);
        if (!right)
        {
            errno = PARSE_ERROR;
            return (NULL);
        }
        left = build_pipeline(left, right);
        token = peek(*tokens);
    }
    return (left);
}

AST *parser(TOKEN *tokens)
{
    AST *parse_t;

    parse_t = parse_pipeline(&tokens);
    if (errno == PARSE_ERROR)
    {
        printf("Synatx Error\n");
        return (NULL);
    }
    return (parse_t);
}

