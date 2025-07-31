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
	t_redir *rad;

	printf("end commands\n");
	printf("start redirections:\n");
	while (redirs)
	{
		rad = redirs->content;
		printf("TYPE: %d --- target: %s\n", rad->type, rad->file);
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
	while (true)
	{
		line = readline(PROMPT);
		if (NULL == line)
			exit(0);
		if (0 == *line)
			continue ;
		add_history(line);
		pipeline = parser(line);
		free(line);
		if (!pipeline)
			continue ;
		executor(pipeline);
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