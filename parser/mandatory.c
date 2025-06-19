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


#include "../include/utils.h"
#include "../include/parser.h"

t_list  *get_args(LIST **tokens)
{
    TOKEN    *curr;
    t_list  *args;
    t_list  *arg_node;

    args = NULL;
    curr = peek(*tokens);
    while (curr && curr->type == WORD)
    {
        arg_node = ft_lstnew(curr->token);
        ft_lstadd_back(&args, arg_node);
        consume(tokens);
    }
    return (args);
}

char    *parse_heredoc(void)
{
    char    *content;

    content = NULL;
    return (content);
}

t_redir  *create_redir_node(LIST *token)
{
    t_redir *redir;

    redir = malloc(sizeof(*redir));
    if (!redir)
        return (NULL);
    redir->type = token->token->type; 
    redir->target = token->next->token->token;
    if (token->token->type == HEREDOC)
        redir->heredoc = parse_heredoc();
    return (redir);
}

t_list  *get_redirs(LIST **tokens)
{
    t_list  *redirs;
    t_list  *redir_node;
    TOKEN   *curr;

    redirs = NULL;
    curr = peek(*tokens);
    while (curr && curr->type == REDIN)
    {
        redir_node = ft_lstnew(create_redir_node(curr));
        ft_lstadd_back(&redirs, redir_node);
        consume(tokens);
    }
}

t_cmd   *build_command(LIST **tokens)
{
    t_cmd   *cmd;

    cmd = malloc(sizeof(*cmd));
    if (!cmd)
        return (NULL);
    cmd->args = get_args(tokens);
    cmd->redirs = get_redirs(tokens);
    return (cmd);
}

AST *parse_command(LIST **tokens)
{
    AST     *command;
    t_cmd   *cmd;

    command = malloc(sizeof(*command));
    if (!command)
       return (NUlL);
    command->node_type = CMD;
    cmd = build_command(tokens);
    if (!cmd)
        return (NUlL);
    command->data = cmd;
    return (command);
}

AST *build_pipeline(AST *left, AST *right)
{
    AST *pipe_node;
    t_ast_binary    *pip;

    pipe_node = malloc(sizeof(*pipe_node));
    if (!pipe_node)
        return (NULL);
    pipe_node->node_type = PIPE;
    pip = malloc(sizeof(t_ast_binary));
    if (pip)
        return (NULL);
    pip->left = left;
    pip->right = right;
    pip->type = pipe_node->node_type = PIPE;
    pipe_node->data = pip;
    return (pipe_node);   
}

AST *parse_pipeline(LIST **tokens)
{
    TOKEN   *token;
    AST *left = NUll;
    AST *right = nuLL;

    left = parse_command(tokens);
    token = peek(*tokens);
    while (token && token->type == PIPE)
    {
        consume(tokens);
        right = parse_command(tokens);
        left = build_pipeline(left, right);
    }
    return left;
}