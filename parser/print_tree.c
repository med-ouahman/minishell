/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 19:28:47 by mouahman          #+#    #+#             */
/*   Updated: 2025/06/19 19:28:49 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/utils.h"
#include "../include/parser.h"

void print_t(t_cmd *cmd)
{
    t_list *redirs = cmd->redirs;
    printf("Redirections:\n");
    while (redirs)
    {
        t_redir *rd = (t_redir *)redirs->content;
        printf("Redirection type: %d, Target: %s", rd->type, rd->target);
        if (rd->heredoc)
            printf(", Heredoc: %s", rd->heredoc);
        redirs = redirs->next;
    }
    printf("\n");
}
void print_cmd(t_cmd *cmd)
{
    t_list *args = cmd->args;
    
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
   
    printf("Node Type: %s\n", ast->node_type == PIPE ? "PIPE" : 
                                ast->node_type == CMD ? "CMD" : "UNKNOWN");
    if (!ast->data)
        return ;
    switch (ast->node_type)
    {
        case PIPE:
            printf("PIPE:\n");
            printf("Left:\n");
            print_tree(((t_ast_binary *)ast->data)->left);
            printf("Right:\n");
            print_tree(((t_ast_binary *)ast->data)->right);
            break;
        case CMD:
        
            print_cmd((t_cmd *)ast->data);
        
            break;
        default:
            printf("UNKNOWN NODE TYPE\n");
    }
}