/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 15:57:33 by mouahman          #+#    #+#             */
/*   Updated: 2025/07/02 17:42:03 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/garbage_collector.h"

void	remove_ptr_from_list(t_list **__list, void *__ptr)
{
	t_list	*__curr;
	t_list	*__next;

	__next = *__list;
	while (__next && __next->content != __ptr)
	{
		__next = __next->next;
	}
	__next = __next->next;
	__curr = *__list;
	while (__curr && __curr->next && __curr->content != __ptr)
	{
		__curr = __curr->next;
	}
	__curr->next = __next;
}

void	garbage_collector(void *__ptr, int __option)
{
	static t_list	*list;
	t_list			*node;

	if (COLLECT == __option)
	{
		if (!__ptr)
			exit(EXIT_FAILURE);
		node = ft_lstnew(__ptr);
		if (!node)
			exit(EXIT_FAILURE);
		ft_lstadd_back(&list, node);
	}
	else if (CHECK == __option)
	{
		if (!__ptr)
			exit(EXIT_FAILURE);
	}
	else if (FREE == __option)
	{
		remove_ptr_from_list(&list, __ptr);
		free(__ptr);
	}
	else if (DESTROY == __option)
		ft_lstclear(&list, free);
}
