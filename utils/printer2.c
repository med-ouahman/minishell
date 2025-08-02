/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aid-bray <aid-bray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 05:24:54 by aid-bray          #+#    #+#             */
/*   Updated: 2025/07/30 05:53:36 by aid-bray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

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
