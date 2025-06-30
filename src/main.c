/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:19:14 by mouahman          #+#    #+#             */
/*   Updated: 2025/06/29 21:10:54 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(void)
{
	char	*line;
	TOKEN	*tokens;
	AST		*parse_t;
	
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	while (true)
	{
		access_exit_code(0, WRITE);
		line = readline("$ ");
		if (NULL == line)
		{
			rl_clear_history();
			return (1);
		}
		if (0 == *line)
			continue ;
		add_history(line);
		tokens = tokenizer(line);
		free(line);
		parse_t = parser(tokens);
		if (!parse_t)
			continue ;
		setup_execution(parse_t);
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