/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_argument_list.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 22:22:20 by mouahman          #+#    #+#             */
/*   Updated: 2025/07/12 22:23:11 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/executor.h"

char	**build_argument_list(t_list *lst)
{
	char	**args;
	int		i;

	if (!lst)
		return (NULL);
	args = malloc(ft_lstsize(lst) * sizeof * lst + sizeof * lst);
	i = 0;
	while (lst)
	{
		args[i] = lst->content;
		lst = lst->next;
		i++;
	}
	args[i] = NULL;
	return (args);
}
