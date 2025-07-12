/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 15:57:33 by mouahman          #+#    #+#             */
/*   Updated: 2025/07/04 20:34:26 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/garbage_collector.h"

// void	safe_free(void *_ptr)
// {
	
// }

static int		is_in_list(t_list *lst, void *ptr)
{
	while (lst)
	{
		if (lst->content == ptr)
			return (1);
		lst = lst->next;
	}
	return (0);
}

void	remove_ptr_from_list(t_list **_list, void *__ptr)
{
	t_list	*_curr;
	t_list	*_next;

	_next = *_list;
	while (_next && _next->content != __ptr)
	{
		_next = _next->next;
	}
	if (!_next)
		return ;
	_next = _next->next;
	_curr = *_list;
	while (_curr && _curr->next && _curr->content != __ptr)
	{
		_curr = _curr->next;
	}
	_curr->next = _next;
}

void	garbage_collector(void *__ptr, int __option)
{
	static t_list	*list;
	t_list			*node;

	if (COLLECT == __option)
	{
		if (!__ptr)
			exit(EXIT_FAILURE);
		if (is_in_list(list, __ptr))
			return ;
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
