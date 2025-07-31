/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_exit_code.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 09:59:16 by mouahman          #+#    #+#             */
/*   Updated: 2025/07/13 09:59:37 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

void	add_exit_code(t_list **var_list, int code)
{
	t_list	*node;
	char	*s;

	s = ft_itoa(code);
	collect_malloc(s, CHECK);
	node = ft_lstnew(s);
	collect_malloc(node, CHECK);
	ft_lstadd_back(var_list, node);
}
