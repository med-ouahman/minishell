/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_argument_list.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aid-bray <aid-bray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 22:22:20 by mouahman          #+#    #+#             */
/*   Updated: 2025/08/06 10:09:51 by aid-bray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/executor.h"

char	**build_argument_list(t_list *lst)
{
	t_list	*tmp;
	char	**args;
	t_uint	i;

	args = malloc((1 + ft_lstsize(lst)) * sizeof(char *));
	collect_malloc(args, CHECK);
	i = 0;
	while (lst)
	{
		args[i] = lst->content;
		tmp = lst;
		lst = lst->next;
		collect_malloc(tmp, DELETE);
		i++;
	}
	args[i] = NULL;
	return (args);
}
