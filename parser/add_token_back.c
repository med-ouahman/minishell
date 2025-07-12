/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_token_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 21:28:09 by mouahman          #+#    #+#             */
/*   Updated: 2025/07/10 21:31:41 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

size_t	token_list_size(TOKEN *list)
{
	size_t	list_size;

	list_size = 0;
	while (list)
	{
		list = list->next;
		list_size = list_size + 1;
	}
	return (list_size);
}

void	add_token_back(TOKEN **list, TOKEN *token)
{
	TOKEN 	*last;

	if (*list == NULL)
		*list = token;
	else
	{
		last = *list;
		while (last->next)
			last = last->next;
		last->next = token;
	}
}


