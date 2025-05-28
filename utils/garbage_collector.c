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
	int		i;
	static char	*list[P_MAX];

	if (ptr)
	{
		list[cursor] = ptr;
		cursor++;
	}
	if (0 == option)
		return (cursor);
	i = 0;
	while (i < cursor)
	{
		if (NULL == list[i])
			continue ;
		free(list[i]);
		list[i] = NULL;
	}
	return (cursor);
}
