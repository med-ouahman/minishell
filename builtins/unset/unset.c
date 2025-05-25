/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:38:20 by mouahman          #+#    #+#             */
/*   Updated: 2025/05/19 18:46:24 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/unset.h"

int	unset(char *key)
{
	int	index;
	int	i;

	index = index_of(__environ, key);
	if (-1 == index)
		return (0);
	i = 0;
	while (i < index)
		i++;
	while (__environ[i + 1])
	{
		__environ[i] = __environ[i + 1];
		i++;
	}
	return (0);
}
