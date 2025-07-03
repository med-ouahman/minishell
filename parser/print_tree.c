/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 19:28:47 by mouahman          #+#    #+#             */
/*   Updated: 2025/07/03 11:09:38 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/utils.h"
#include "../include/parser.h"

void    print_redir(t_redir *redir)
{

 printf("Redirection: %s -> target: %s ",
                   redir->type == REDIN ? "REDIN" :
                   redir->type == REDOUT ? "REDOUT" :
                   redir->type == HEREDOC ? "HEREDOC" :
                   redir->type == REDOUTAPP ? "REDOUTAPP" : "UNKNOWN",
                   redir->target);
}

void print_redirs(t_list *redirs)
{
    t_list *current = redirs;
    while (current)
    {
        t_redir *redir = (t_redir *)current->content;
        print_redir(redir);
        current = current->next;
    }
    printf("\n");
}

void print_exc_list(t_list *exec_list)
{
    t_list  *current = exec_list;
    while (current)
    {
        t_cmd *cmd = (t_cmd *)current->content;
        printf("Command: ");
        t_list *arg = cmd->args;
        while (arg)
        {
            printf("'%s' ", (char *)arg->content);
            arg = arg->next;
        }
        arg = cmd->redirs;
        while (arg)
        {
            t_redir *redir = (t_redir *)arg->content;
            printf("Redirection: %s -> %s ",
                   redir->type == REDIN ? "REDIN" :
                   redir->type == REDOUT ? "REDOUT" :
                   redir->type == HEREDOC ? "HEREDOC" :
                   redir->type == REDOUTAPP ? "REDOUTAPP" : "UNKNOWN",
                   redir->target);
           arg = arg->next;
        }
        printf("\n");
        current = current->next;
    }
}

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

void print_atom(AST *atom)
{
    t_subshell *subshell;

    subshell = (t_subshell *)atom->data;

    if (subshell->ast_node->node_type == ATOM)
        return print_tree(subshell->ast_node);
    printf("type is %s\n", get_token_type(subshell->ast_node->node_type));
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
     printf("Node Type: %s\n", get_token_type(ast->node_type));
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
            print_atom(ast);
            break;
        default:
            printf("Unknown node type: %d\n",  ast->node_type);
            break;
    }
}