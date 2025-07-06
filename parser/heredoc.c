/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 09:26:16 by mouahman          #+#    #+#             */
/*   Updated: 2025/07/06 20:14:24 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

static void	heredoc_exit(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
	{
		if (SIGINT == WTERMSIG(status))
		{
			rl_after_fork();
			error(1, WRITE);
			access_exit_code(130, WRITE);
		}
	}
}

static void  restore_signals(void)
{
	struct sigaction    act;

	act.sa_handler = SIG_DFL;
	sigaction(SIGINT, &act, NULL);
}

char    *create_heredoc_file(int length)
{
	char    *filename;
	int i;
	int random_char;
	int	fd;

	filename = malloc(sizeof(char) * length + 1);
	garbage_collector(filename, COLLECT);
	fd = open("/dev/random", O_RDONLY);
	i = 0;
	while (i < length)
	{
		read(fd, &random_char, 1);
		if (!ft_isprint(random_char))
			continue ;
		filename[i] = random_char;
		i++;
	}
	filename[i] = 0;
	printf("%s\n", filename);
	return (filename);
}

char    *parse_content(char *content, int __expand)
{
	t_list  *l;

	if (!__expand)
		return (content);
	l = get_var_list(content);
	content = expand_var_list(l);
	return (content);
}

void	__write_to_heredoc_file(int fd, char *_delim, int __expand)
{
	char	*line;
	char	*content;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			ft_printf_fd(2, "delim error\n");
			break ;
		}
		if (!ft_strcmp(line, _delim))
			break ;
		content = parse_content(line, __expand);
		if (!(content == line))
			free(line);
		write(fd, content, ft_strlen(content));
		free(content);
		write(fd, "\n", 1);
	}
}

char    *parse_heredoc(char *_delim, int __expand)
{
	char    *file;
	int     fd;
	pid_t    pid;

	file = create_heredoc_file(20);
	pid = fork();
	signal(SIGINT, SIG_IGN);
	if (pid == 0)
	{
		restore_signals();
		fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		__write_to_heredoc_file(fd, _delim, __expand);
		close(fd);
		exit(0);
	}
	heredoc_exit(pid);
	return (file);
}
