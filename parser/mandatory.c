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

t_list  *get_args(TOKEN **tokens)
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
        curr = peek(*tokens);
    }
    return (args);
}

char    *create_heredoc_file(int length)
{
    char    *filename;
    int i;
    int random_char;
    
    filename = malloc(sizeof(char) * length + 1);
    garbage_collector(filename, ALLOC);
    i = 0;
    while (i < length)
    {
        random_char = rand() % 127;
        random_char = random_char < 32 ? random_char + 32: random_char;
        filename[i] = random_char + 48;
        i++;
    }
    filename[i] = 0;
    return (filename);
}

char    *parse_content(char *input)
{
    t_list  *l;

    l = get_var_list(input);
    return (expand_var_list(l));
}

char    *parse_heredoc(t_redir *redir)
{
    char    *line;
    char    *file;
    char    *content;
    int     fd;

    file = create_heredoc_file(10);
    fd = open(file, O_CREAT | O_WRONLY, 0644);
    while (1)
    {
        line = readline("> ");
        if (!ft_strcmp(line, redir->target))
            break ;
        content = parse_content(line);
        free(line);
        write(fd, content, ft_strlen(content));
        free(content);
        write(fd, "\n", 1);
    }
    close(fd);
    unlink(file);
    file=NULL;
    return (file);
}

t_redir  *create_redir_node(TOKEN *token)
{
    t_redir *redir;

    redir = malloc(sizeof(*redir));
    if (!redir)
        return (NULL);
    redir->type = token->type; 
    redir->target = token->next->token;
    if (token->type == HEREDOC)
        redir->target = parse_heredoc(redir);
    return (redir);
}

int is_redirection(int t)
{
    return (t == REDIN || t == REDOUT || t == HEREDOC || t == REDOUTAPP);
}

t_list  *get_redirs(TOKEN **tokens)
{
    t_list  *redirs;
    t_list  *redir_node;
    TOKEN   *curr;

    redirs = NULL;
    curr = peek(*tokens);
    if (!curr)
        return (NuLL);
    while (curr && is_redirection(curr->type))
    {
        redir_node = ft_lstnew(create_redir_node(curr));
        consume(tokens);
        ft_lstadd_back(&redirs, redir_node);
        consume(tokens);
        curr = peek(*tokens);
    }
    return (redirs);
}

t_cmd   *build_command(TOKEN **tokens)
{
    t_cmd   *cmd;

    cmd = malloc(sizeof(*cmd));
    if (!cmd)
        return (NULL);
    cmd->args = get_args(tokens);
    cmd->redirs = get_redirs(tokens);
    return (cmd);
}

AST *parse_command(TOKEN **tokens)
{
    AST     *command;
    t_cmd   *cmd;

    if (*tokens == NULL)
        return (NULL);
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
    AST             *pipe_node;
    t_ast_binary    *pip;

    pipe_node = malloc(sizeof(*pipe_node));
    if (!pipe_node)
        return (NULL);
    pipe_node->node_type = PIPE;
    pip = malloc(sizeof(t_ast_binary));
    if (!pip)
        return (NULL);
    pip->left = left;
    pip->right = right;
    pip->type = pipe_node->node_type = PIPE;
    pipe_node->data = pip;
    return (pipe_node);
}

AST *parse_pipeline(TOKEN **tokens)
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
        token = peek(*tokens);
    }
    return (left);
}




AST *parser(TOKEN *tokens)
{
    return (parse_pipeline(&tokens));
}

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

void print_exc_list(t_list *exec_list)
{
    t_list  *current = exec_list;
    while (current)
    {
        t_cmd *cmd = (t_cmd *)current->content;
        printf("Command: ");
        if (cmd->args && cmd->args->content)
            printf("%s ", (char *)cmd->args->content);
        t_list *arg = cmd->args ? cmd->args->next : NULL;
        while (arg)
        {
            printf("%s ", (char *)arg->content);
            arg = arg->next;
        }
        printf("\n");
        current = current->next;
    }
}
