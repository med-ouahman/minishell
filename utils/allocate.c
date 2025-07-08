/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:32:10 by mouahman          #+#    #+#             */
/*   Updated: 2025/07/04 20:33:16 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/garbage_collector.h"

void	*my_alloc(size_t _size, int __opt)
{
	void	*ptr;

	ptr = malloc(_size);
	garbage_collector(ptr, __opt);
	return (ptr);
}
