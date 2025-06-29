/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 15:57:33 by mouahman          #+#    #+#             */
/*   Updated: 2025/06/26 12:25:08 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/garbage_collector.h"

void	garbage_collector(void *ptr, int option)
{
	static t_list	*list;
	t_list			*node;

	if (ALLOC == option)
	{
		if (!ptr)
			exit(EXIT_FAILURE);
		node = ft_lstnew(ptr);
		if (!node)
			exit(EXIT_FAILURE);
		ft_lstadd_back(&list, node);
	}
	else if (FREE == option)
	{
		free(ptr);
	}
	else if (FREE_U == option)
		ft_lstclear(&list, free);
}
