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

int execute_builtin_commands(char *line) {
    char *cmds[] = {"clear"};
    
    for (int i = 0; i < 1; i++) {
        if (strcmp(line, cmds[i]) == 0) {
            system(cmds[i]);
            return 1;
        }
    }
    return 0;
}

int	main(void)
{
	char	*line;
	LIST	*tokens;
	
	line = readline("$ ");
	while (line)
	{
		signal(SIGINT, signal_handler);
		if (!*line)
		{
			line = readline("$ ");
			continue ;
		}
		if (execute_builtin_commands(line) == 1) {
			line = readline("$ ");
			continue;
		}
		add_history(line);
		tokens = tokenize(line);
		expand(tokens);
		word_split(&tokens, " \t\n\f\r\v");
		print_token_list(tokens);
		join_tokens(tokens);
		free(line);
		line = readline("$ ");
		if (NULL == line)
			return (1);
	}
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