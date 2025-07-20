/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 16:58:39 by mouahman          #+#    #+#             */
/*   Updated: 2025/07/05 16:09:09 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/tokenizer.h"
#include "../include/parser.h"

char *get_token_type(int type)
{
	if (type == WORD || type == CMD)
		return ("CMD");
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
	if (type == -1)
		return ("Parser");
	return ("UNKNOWN");
}
void	print_token_list(TOKEN *list)
{
	while (list)
	{
		printf("Token: %s Type: %s\n", list->token, get_token_type(list->type));
		list = list->next;
	}
}
