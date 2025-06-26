/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 09:26:16 by mouahman          #+#    #+#             */
/*   Updated: 2025/06/26 21:07:16 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

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

char    *parse_content(char *content)
{
    t_list  *l;

    l = get_var_list(content, -1);
    return (expand_var_list(l));
}

char    *parse_heredoc(t_redir *redir)
{
    char    *line;
    char    *file;
    char    *content;
    int     fd;

    return (".heredoc");
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
    return (file);
}

