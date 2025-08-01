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

void	print_redirs(t_list	*redirs)
{
	t_redir	*radix;

	printf("end commands\n");
	printf("start redirections:\n");
	while (redirs)
	{
		radix = redirs->content;
		printf("TYPE: %d --- TARGET: %s\n", radix->type, radix->file);
		redirs = redirs->next;
	}
	printf("end redirections\n");
}

void	print_exec_list(t_list *lst)
{
	t_cmd	*axd;

	printf("start commands:\n");
	while (lst)
	{
		axd = lst->content;
		print_list(axd->args);
		print_redirs(axd->redir);
		lst = lst->next;
	}
}

int	main(void)
{
	char	*line;
	t_list	*pipeline;

	handle_signals();
	dup_env(&__environ);
	int i = 0;
	while (i < 10)
	{
		line = readline(PROMPT);
		if (NULL == line)
			cleanup(EXIT_SUCCESS);
		if (*line)
			add_history(line);
		pipeline = parser(line);
		free(line);
		executor(pipeline);
		collect_malloc(NULL, CLEAR);
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