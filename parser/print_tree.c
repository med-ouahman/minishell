/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 19:28:47 by mouahman          #+#    #+#             */
/*   Updated: 2025/07/03 12:25:18 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/utils.h"
#include "../include/parser.h"

void print_cmd(t_cmd *cmd);
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
        break;
        current = current->next;
    }
    printf("\n");
}

void print_exc_list(t_list *exec_list)
{
    t_list  *current = exec_list;
    while (current)
    {
        print_cmd(current->content);
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
    TOKEN *args = cmd->args;
    
    if (!args)
        return ;
    printf("command name: %s\n", (char *)args->token);
    args = args->next;
    printf("Arguments: [");
    while (args)
    {
        printf("%s%s", (char *)args->token, args->next ? ", " : "");
        args = args->next;
    }
    printf("]\n");
    print_t(cmd);
}
