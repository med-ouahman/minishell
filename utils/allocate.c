/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:32:10 by mouahman          #+#    #+#             */
/*   Updated: 2025/07/02 11:23:45 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/garbage_collector.h"

void	*my_alloc(size_t __size)
{
	void	*ptr;

	ptr = malloc(__size);
	garbage_collector(ptr, COLLECT);
	return (ptr);
}
