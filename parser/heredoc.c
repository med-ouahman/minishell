/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aid-bray <aid-bray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 05:24:07 by aid-bray          #+#    #+#             */
/*   Updated: 2025/08/13 14:35:32 by aid-bray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

int	g_heredoc_sig;

static int	get_filename(char *file_name)
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

static int	open_heredoc(char *file_name, int *write_fd, int *read_fd)
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

static int	event_hook(void)
{
	return (0);
}

static void	heredoc_handler(int signum)
{
	rl_done = 1;
	g_heredoc_sig = signum;
	rl_prompt = ft_strdup(get_prompt());
	access_exit_code(130, WRITE);
	signal(SIGINT, sigint_handler);
}

int	parser_heredoc(char *delimiter)
{
	int		fd_io[2];
	char	filename[LENGTH + 1];
	char	*line;
	int		exp;

	if (get_filename(filename) || open_heredoc(filename, &fd_io[0], &fd_io[1]))
		return (-1);
	signal(SIGINT, heredoc_handler);
	rl_event_hook = event_hook;
	g_heredoc_sig = 0;
	exp = remove_quote(delimiter);
	while (!g_heredoc_sig)
	{
		line = readline(">");
		if (write_heredoc(line, fd_io[0], delimiter, exp))
			break ;
	}
	rl_event_hook = NULL;
	close(fd_io[0]);
	if (g_heredoc_sig)
	{
		g_heredoc_sig = 0;
		return (close(fd_io[1]), -1);
	}
	return (fd_io[1]);
}
