/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_properties.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:18:09 by mouahman          #+#    #+#             */
/*   Updated: 2025/05/28 11:18:46 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/utils.h"

size_t	get_lsize(t_list *var_list)
{
	size_t	lsize;

	lsize = 0;
	while (var_list)
	{
		lsize += ft_strlen((char *)var_list->content);
		var_list = var_list->next;
	}
	return (lsize);
}

int	copy_list(char *buff, t_list *var_list, size_t lsize)
{
	while (var_list)
	{
		ft_strlcat(buff, (char *)var_list->content, lsize);
		var_list = var_list->next;
	}
	return (0);
}
