/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 15:57:33 by mouahman          #+#    #+#             */
/*   Updated: 2025/05/28 16:01:41 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/garbage_collector.h"

int	garbage_collector(void *ptr, int option)
{
	static int	cursor = 0;
	static char	*list[P_MAX];
	int		i;

	if (ALLOC == option)
	{
		if (!ptr)
			exit(EXIT_FAILURE);
		list[cursor] = ptr;
		cursor++;
	}
	else if (FREE == option)
	{
		free(ptr);
	}
	else if (FREE_U == option)
	{
		i = 0;
		while (i < cursor)
		{
			if (NULL == list[i])
				continue ;
			free(list[i]);
			list[i] = NULL;
			i++;
		}
	}
	return (cursor);
}
