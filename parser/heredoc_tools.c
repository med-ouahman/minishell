/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 03:00:23 by mouahman          #+#    #+#             */
/*   Updated: 2025/08/13 03:00:27 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

static int	eof_exception(char *eof)
{
	ft_printf_fd(STDERR_FILENO, "heredoc delimited by EOF, required %s\n", eof);
	return (-1);
}

static int	remove_quote(char *str)
{
	int		count;
	size_t	i;
	char	quote;

	i = 0;
	quote = 0;
	count = 0;
	while (str[i + count])
	{
		if (is_quote(str[i + count]) && quote == str[i + count])
		{
			count++;
			quote = 0;
			continue ;
		}
		else if (is_quote(str[i + count]) && !quote)
		{
			quote = str[i + count];
			count++;
			continue ;
		}
		str[i] = str[i + count];
		i++;
	}
	return (str[i] = '\0', count);
}

int	get_filename(char *file_name)
{
	char	random_c[LENGTH + 1];
	int		i;
	int		fd;

	fd = open("/dev/random", O_RDONLY);
	if (fd < 0)
	{
		print_err1(strerror(errno));
		return (-1);
	}
	i = 0;
	while (i < LENGTH)
	{
		read(fd, random_c, LENGTH);
		if ('/' == random_c[i] || !ft_isprint(random_c[i]))
			continue ;
		file_name[i] = random_c[i];
		i++;
	}
	file_name[i] = '\0';
	close(fd);
	return (0);
}

int	open_heredoc(char *file_name, int *write_fd, int *read_fd)
{
	*write_fd = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (*write_fd < 0)
	{
		print_err2(file_name, strerror(errno));
		return (-1);
	}
	*read_fd = open(file_name, O_RDONLY);
	if (*read_fd < 0)
	{
		print_err1(strerror(errno));
		close(*write_fd);
		unlink(file_name);
		return (-1);
	}
	unlink(file_name);
	return (0);
}

int	write_heredoc(char *line, int writer, char *eof)
{
	char	*content;
	int		exp;

	if (!line)
		return (eof_exception(eof));
	exp = remove_quote(eof);
	content = parser_line(line, exp);
	exp = line == content;
	if (!ft_strcmp(eof, content))
	{
		if (!exp)
			collect_malloc(content, DELETE);
		free(line);
		return (-1);
	}
	write(writer, content, ft_strlen(content));
	write(writer, "\n", 1);
	if (!exp)
		collect_malloc(content, DELETE);
	free(line);
	return (0);
}
