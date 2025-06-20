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

void	print_token_list(TOKEN *list)
{
	while (list)
	{
		printf("%s\n", list->token);	
		list = list->next;
	}
}
