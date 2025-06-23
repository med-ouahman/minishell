/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 09:32:31 by mouahman          #+#    #+#             */
/*   Updated: 2025/06/23 09:32:58 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

t_list  *execution_list(AST *ast)
{
    t_list  *exec_list;
    t_list  *node;

    exec_list = NULL;
    if (!ast)
        return (exec_list);
    if (ast->node_type == PIPE)
    {
        t_ast_binary *pipe_data = (t_ast_binary *)ast->data;
        ft_lstadd_back(&exec_list, execution_list(pipe_data->left));
        ft_lstadd_back(&exec_list, execution_list(pipe_data->right));
    }
    else if (ast->node_type == CMD)
    {
        node = ft_lstnew(ast->data);
        ft_lstadd_back(&exec_list, node);
    }
    return (exec_list);
}

