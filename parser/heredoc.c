/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aid-bray <aid-bray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 05:24:07 by aid-bray          #+#    #+#             */
/*   Updated: 2025/07/30 06:25:51 by aid-bray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

#define LENGHT 20

static int	create_heredoc_name(char *file_name)
{
	char	random_c[LENGHT + 1];
	int		i;
	int		fd;

	fd = open("/dev/urandom", O_RDONLY);
	if (fd < 0)
	{
		print_err1(strerror(errno));
		return (-1);
	}
	i = 0;
	while (i < LENGHT)
	{
		read(fd, random_c, LENGHT);
		if ('/' == random_c[i])
			continue ;
		file_name[i] = random_c[i];
		i++;
	}
	file_name[i] = '\0';
	close(fd);
	return (0);
}

static int	heredoc_exit(pid_t pid)
{
	int	status;

	status = 0;
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		access_exit_code(WEXITSTATUS(status), WRITE);
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
		{
			rl_after_fork();
			access_exit_code(130, WRITE);
			return (-1);
		}
	}
	handle_signals();
	return (0);
}

static int	create_heredoc_file(char *file_name, int *write_fd, int *read_fd)
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

int	parser_heredoc(char *delim)
{
	char	file[LENGHT + 1];
	pid_t	pid;
	int		write_fd;
	int		read_fd;

	if (create_heredoc_name(file))
		return (-1);
	if (create_heredoc_file(file, &write_fd, &read_fd))
		return (-1);
	ignore_signals();
	pid = fork();
	if (pid < 0)
		return (print_err1(strerror(errno)), -1);
	if (!pid)
	{
		close(read_fd);
		read_heredoc(delim, write_fd);
		close(write_fd);
		cleanup(EXIT_SUCCESS);
	}
	close(write_fd);
	if (heredoc_exit(pid))
		return (-1);
	return (read_fd);
}
