/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_pipeline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 09:32:31 by mouahman          #+#    #+#             */
/*   Updated: 2025/06/30 13:34:06 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

t_list  *create_pipeline(AST *ast)
{
    t_list  *pipeline;
    t_list  *node;
    t_ast_binary    *bin;

    pipeline = NULL;
    if (!ast)
        return (pipeline);
    if (ast->node_type == PIPE)
    {
        bin = (t_ast_binary *)ast->data;
        ft_lstadd_back(&pipeline, create_pipeline(bin->left));
        ft_lstadd_back(&pipeline, create_pipeline(bin->right));
    }
    else if (ast->node_type == CMD)
    {
        node = ft_lstnew(ast);
        ft_lstadd_back(&pipeline, node);
    }
    return (pipeline);
}

