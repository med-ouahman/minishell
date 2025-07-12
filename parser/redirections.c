/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 09:28:17 by mouahman          #+#    #+#             */
/*   Updated: 2025/07/06 14:09:00 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

static int  has_quotes(char *s)
{
    char    *f;
    char    *l;
    char    quote;

    quote = find_next_quote(s);
    if (!quote)
        return (1);
    f = ft_strchr(s, quote);
    l = ft_strrchr(s, quote);
    if (!l || !f || l == f)
        return (1);
    return (0);
}

t_redir  *create_redir_node(TOKEN *token)
{
    TOKEN   *tmp;
    t_redir *redir;
    char    **args;
    int     __expand;
    char	*save;

    if (NULL == token->next || token->next->type != WORD)
    {
        syntax_error(token->type, token->next);
        return (NULL);
    }
    redir = malloc(sizeof *redir);
    garbage_collector(redir, COLLECT);
    redir->type = token->type;
    if (token->type == HEREDOC)
    {
        token = token->next;
        __expand = has_quotes(token->token);
        remove_quotes_from_token(token->token);
        redir->heredoc_fd = parse_heredoc(token->token, __expand);
        return (redir);
    }
    token = token->next;
    save = ft_strdup(token->token);
    tmp = token->next;
    token->next = NULL;
    args = build_argument_list(token);
    token->next = tmp;
    if (args[1])
    {
        print_file_error(save, "ambigous redirect");
        return (NULL);
    }
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
    if (!curr || !is_redirection(curr->type) || error(0, READ))
        return (NULL);
    while (curr && is_redirection(curr->type))
    {
        redir = create_redir_node(curr);
        if (error(0, READ))
            return (NULL);
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
