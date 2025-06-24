/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 09:28:17 by mouahman          #+#    #+#             */
/*   Updated: 2025/06/23 09:29:22 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

t_redir  *create_redir_node(TOKEN *token)
{
    t_redir *redir;
    char    **split;

    split = NULL;
    if (NULL == token->next || token->next->type != WORD || token->type == -1)
    {
        printf("error\n");
        return (NULL);
        // erreur de syntax, Unexpected token near newline or >> or << or > or <;f (!curr)
    }
    redir = malloc(sizeof(*redir));
    garbage_collector(redir, ALLOC);
    redir->type = token->type;
    if (token->type == HEREDOC)
    {
        redir->target = token->next->token;
        redir->target = parse_heredoc(redir);
        return (redir);
    }
    token = token->next;
    expand(token, 0);
    if (token->split)
    {
        split = word_split(token, " \n\t\f\v\r");
        garbage_collector(split, ALLOC);
        if (!*split || *(split + 1))
        {
            printf("nunu\n");
            // ambiguous redirect;
        }
        redir->target = *split;
    }
    else
        redir->target = token->token;
    return (redir);
}

int is_redirection(int t)
{
    return (t == REDIN || t == REDOUT || t == HEREDOC || t == REDOUTAPP);
}


t_list  *get_redirs(TOKEN **tokens)
{
    t_redir *redir;
    t_list  *redirs;
    t_list  *redir_node;
    TOKEN   *curr;

    redirs = NULL;
    curr = peek(*tokens);
    if (!curr)
        return (NULL);
    if (!is_redirection(curr->type))
    {
        errno = PIPE_ERROR;
        return (NULL);
    }
    while (curr && is_redirection(curr->type))
    {
        redir = create_redir_node(curr);
        consume(tokens);
        if (!redir)
            return (NULL);
        redir_node = ft_lstnew(redir);
        ft_lstadd_back(&redirs, redir_node);
        consume(tokens);
        curr = peek(*tokens);
    }
    return (redirs);
}
