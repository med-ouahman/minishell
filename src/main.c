/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aid-bray <aid-bray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:19:14 by mouahman          #+#    #+#             */
/*   Updated: 2025/08/09 11:43:03 by aid-bray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*get_prompt(void)
{
	if (access_exit_code(0, READ) && access_exit_code(0, READ) != 130)
	{
		return (ERROR_PROMPT);
	}
	return (PROMPT);
}

static void	init(void)
{
	handle_signals();
	dup_env();
	change_var("SHELL=minishell");
}

void	*r_line(void)
{
	char	*line;
	char	*rline;

	rline = NULL;
	if (isatty(STDIN_FILENO))
		rline = readline(get_prompt());
	else
	{
		line = get_next_line(STDIN_FILENO);
		if (line)
			rline = ft_strtrim(line, "\n");
		free(line);
	}
	return (rline);
}

static void	minishell(void)
{
	char	*line;
	t_list	*pipeline;

	line = readline(get_prompt());
	if (NULL == line)
	{
		if (isatty(STDIN_FILENO))
			ft_printf_fd(2, "exit\n");
		cleanup(access_exit_code(0, READ));
	}
	if (*line)
		add_history(line);
	pipeline = parser(line);
	free(line);
	executor(pipeline);
	collect_malloc(NULL, CLEAR);
}

int	main(void)
{
	access_exit_code(0, WRITE);
	init();
	while (true)
	{
		minishell();
	}
	return (EXIT_SUCCESS);
}

/*
	You have no intreset in here.
	
	NFA -> DFA -> mDFA

	Theory of computation??

	Prerequisites
 
	symbol: (a, b, c, 0, 1, 2)

	alpha: collection of symbols denoted by Sigma {a, b}, {d, e, f}, {0, 1, 2}

	string: a sequnece of symbols, a, b, c, d, aba, 010

	language: set of strings

	L1: set of strings of length 2 => {00, 11, 01 }

	L2: set of all strings of length 3 => {010, 000, 111}

	L3: set of all strings that start with 0
*/