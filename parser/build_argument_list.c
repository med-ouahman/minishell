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

static t_list	*build_wildcard_args(t_list *words)
{
	t_list	*wildcard_lst;
	t_list	*wildcard_node;

	wildcard_lst = NULL;
	while (words)
	{
		wildcard_node = wildcard(words->content);
		ft_lstadd_back(&wildcard_lst, wildcard_node);
		words = words->next;
	}
	return (wildcard_lst);
}

static t_list	*build_list(TOKEN *arg_list)
{
	t_list	*lst;
	t_list	*node;
	t_list	*wildcard_args;

	lst = NULL;
	while (arg_list)
	{
		arg_list->split = is_splittable(arg_list->token);
		node = expand(arg_list);
		if (!node)
		{
			arg_list = arg_list->next;
			continue ;
		}
		wildcard_args = build_wildcard_args(node);
		quote_removal(node);
		ft_lstadd_back(&lst, wildcard_args);
		arg_list = arg_list->next;
	}
	return (lst);
}

char	**build_argument_list(TOKEN *arg_list)
{
	t_list	*lst;
	char	**args;
	int		i;

	lst = build_list(arg_list);
	if (!lst)
		return (NULL);
	args = malloc(ft_lstsize(lst) * sizeof *lst + sizeof *lst);
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
