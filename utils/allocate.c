/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:32:10 by mouahman          #+#    #+#             */
/*   Updated: 2025/05/28 16:34:32 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/garbage_collector.h"

void	*my_alloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (NULL == ptr)
	{
		garbage_collector(NULL, 1);
		exit(1);
	}
	return (ptr);
}
