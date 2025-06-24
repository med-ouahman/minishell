/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 16:58:39 by mouahman          #+#    #+#             */
/*   Updated: 2025/05/23 17:03:54 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/tokenizer.h"
#include "../include/parser.h"

char *get_token_type(int type)
{
	if (type == WORD)
		return ("WORD");
	if (type == PIPE)
		return ("PIPE");
	if (type == REDIN)
		return ("REDIN");
	if (type == REDOUT)
		return ("REDOUT");
	if (type == REDOUTAPP)
		return ("REDOUTAPP");
	if (type == HEREDOC)
		return ("HEREDOC");
	if (type == AND)
		return ("AND");
	if (type == OR)
		return ("OR");
	if (type == OPENPAR)
		return ("OPENPAR");
	if (type == CLOSEPAR)
		return ("CLOSEPAR");
	return ("UNKNOWN");
}
void	print_token_list(TOKEN *list)
{
	while (list)
	{
		printf("Token: '%s' Type: %s\n", list->token, get_token_type(list->type));
		list = list->next;
	}
}
