/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index_of.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:48:37 by mouahman          #+#    #+#             */
/*   Updated: 2025/05/15 11:57:57 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/utils.h"

int	index_of(char *str_ptr[], char *key)
{
	size_t	len;
	int	index;

	len = ft_strlen(key);
	index = 0; 
	while (*str_ptr && ft_strncmp(*str_ptr, key, len))
	{
		str_ptr++;
		index++;
	}
	if (NULL == *str_ptr)
		return (-1);
	return (index);
}

int	min(int a, int b)
{
	if (a > b)
		return (b);
	return (a);
}