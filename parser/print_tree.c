/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 19:28:47 by mouahman          #+#    #+#             */
/*   Updated: 2025/06/28 10:05:01 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/utils.h"
#include "../include/parser.h"

void print_t(t_cmd *cmd)
{
    t_list *redirs = cmd->redirs;
    printf("Redirections: [");
    while (redirs)
    {
        t_redir *rd = (t_redir *)redirs->content;
        printf("{ type: %s, target: %s }%s", get_token_type(rd->type), rd->target, redirs->next ? ",\n":"");
        redirs = redirs->next;
    }
    printf("]\n");
}
void print_cmd(t_cmd *cmd)
{
    t_list *args = cmd->args;
    
    if (!args)
        return ;
    printf("command name: %s\n", (char *)args->content);
    args = args->next;
    printf("Arguments: [");
    while (args)
    {
        printf("%s%s", (char *)args->content, args->next ? ", " : "");
        args = args->next;
    }
    printf("]\n");
    print_t(cmd);
}


void print_tree(AST *ast)
{
   t_ast_binary *bin;
    t_cmd *cmd;
   
    if (!ast ||!ast->data)
    {
        printf("NULL\n");
        return ;
    }
     printf("Node Type: %s\n", ast->node_type == PIPE ? "PIPE" : 
                                ast->node_type == CMD ? "CMD" : ast->node_type == OR ? "OR" :
                                ast->node_type == AND ? "AND" : ast->node_type == ATOM ? "ATOM" : "UNKNOWN");
    switch (ast->node_type)
    {
        case PIPE:
            bin = (t_ast_binary *)ast->data;
            printf("Left:\n");
            print_tree(bin->left);
            printf("Right:\n");
            print_tree(bin->right);
            break;
        case OR:
            bin = (t_ast_binary *)ast->data;
            printf("Left:\n");
            print_tree(bin->left);
            printf("Right:\n");
            print_tree(bin->right);
            break;
        case AND:
            bin = (t_ast_binary *)ast->data;
            printf("Left:\n");
            print_tree(bin->left);
            printf("Right:\n");
            print_tree(bin->right);
            break;
        case CMD:
            cmd = (t_cmd *)ast->data;
            if (cmd)
                print_cmd((t_cmd *)ast->data);
            else
                printf("NULL is cmd\n");
            break;
        case ATOM:
            print_tree((AST *)ast->data);
            break;
        default:
            printf("Unknown node type: %d\n",  ast->node_type);
            break;
    }
}