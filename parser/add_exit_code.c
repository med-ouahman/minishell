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

#include "../include/tokenizer.h"

void	add_exit_code(t_list **var_list, int code)
{
	t_list	*node;
	char	*s;

	s = ft_itoa(code);
	garbage_collector(s, COLLECT);
	node = ft_lstnew(s);
	garbage_collector(node, COLLECT);
	ft_lstadd_back(var_list, node);
}
