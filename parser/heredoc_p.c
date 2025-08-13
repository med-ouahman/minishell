/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aid-bray <aid-bray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 05:24:07 by aid-bray          #+#    #+#             */
/*   Updated: 2025/08/12 04:20:00 by aid-bray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

int	g_heredoc_sig;

static int	event_hook(void)
{
	return (0);
}

static void	heredoc_handler(int signum)
{
	rl_done = 1;
	g_heredoc_sig = signum;
	rl_prompt = ft_strdup(get_prompt());
	if (!rl_prompt)
		collect_malloc(rl_prompt, CHECK);
	access_exit_code(130, WRITE);
	signal(SIGINT, sigint_handler);
}

int	parser_heredoc(char *eof)
{
	int		writer;
	int		reader;
	char	filename[LENGTH + 1];
	char	*line;

	if (get_filename(filename) || open_heredoc(filename, &writer, &reader))
		return (-1);
	signal(SIGINT, heredoc_handler);
	rl_event_hook = event_hook;
	g_heredoc_sig = 0;
	while (!g_heredoc_sig)
	{
		line = readline(">");
		if (write_heredoc(line, writer, eof))
			break ;
	}
	rl_event_hook = NULL;
	close(writer);
	if (g_heredoc_sig)
	{
		close(reader);
		g_heredoc_sig = 0;
		return (-1);
	}
	return (reader);
}
