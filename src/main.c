/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:19:14 by mouahman          #+#    #+#             */
/*   Updated: 2025/07/06 14:22:40 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	init(void)
{
	handle_signals();
	dup_env();
}

static void	minishell(void)
{
	char	*line;
	t_list	*pipeline;

	line = readline(PROMPT);
	if (NULL == line)
		cleanup(EXIT_SUCCESS);
	if (*line)
		add_history(line);
	pipeline = parser(line);
	free(line);
	if (pipeline)
		executor(pipeline);
	collect_malloc(NULL, CLEAR);
}

int	main(void)
{
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