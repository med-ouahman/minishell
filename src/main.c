/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.1337.ma>          +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:19:14 by mouahman          #+#    #+#             */
/*   Updated: 2025/05/19 13:41:09 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(void)
{
	char	*line;
	TOKEN	*tokens;
	AST		*parse_t;
	int		code;
	t_list	*exec_list;
	
	code = 0;
	while (0x10)
	{
		line = readline("$ ");
		if (NULL == line)
			return (1);
		signal(SIGINT, signal_handler);
		if (!*line)
			continue ;
		add_history(line);
		tokens = tokenizer(line);
		// print_token_list(tokens);
		free(line);
		parse_t = parser(tokens);
		// print_tree(parse_t);
		// continue;
		exec_list = execution_list(parse_t);
		code = executor(exec_list);
	}
	return (0);
}
// NFA -> DFA -> mDFA

//Theory of computation??

// Prerequisites

/* 
symbol: (a, b, c, 0, 1, 2)

alpha: collection of symbols denoted by Sigma {a, b}, {d, e, f}, {0, 1, 2}



string: a sequnece of symbols, a, b, c, d, aba, 010


language: set of strings

L1: set of strings of length 2 => {00, 11, 01 }

L2: set of all strings of length 3 => {010, 000, 111}

L3: set of all strings that start with 0
*/