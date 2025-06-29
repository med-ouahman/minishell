/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 15:16:55 by mouahman          #+#    #+#             */
/*   Updated: 2025/06/29 10:56:00 by mouahman         ###   ########.fr       */
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


