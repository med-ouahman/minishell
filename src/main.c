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

int	main(void)
{	char	*line;
	TOKEN	*tokens;
	t_list	*pipeline;

	if (!isatty(STDOUT_FILENO) || !isatty(STDERR_FILENO))
		return (1);
	handle_signals();
	dup_env(&__environ);
	while (true)
	{
		line = readline(PROMPT);
		if (NULL == line)
			exit(!!errno);
		if (0 == *line)
			continue ;
		add_history(line);
		tokens = tokenizer(line);
		free(line);
		pipeline = parser(tokens);
		if (!pipeline)
			continue ;
		access_exit_code(setup_execution(pipeline), WRITE);
		// garbage_coellector(NULL, DESTROY);
	}
	return (0);
}
/*

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