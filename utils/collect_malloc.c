/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_malloc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aid-bray <aid-bray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 05:24:46 by aid-bray          #+#    #+#             */
/*   Updated: 2025/07/30 05:52:46 by aid-bray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/utils.h"

int	cleanup(int code)
{
	rl_clear_history();
	collect_malloc(NULL, DESTROY);
	exit(code);
}

static void	clear_list(t_list **lst, t_list **env_list, int opt)
{
	t_list	**to_clear;

	to_clear = lst;
	if (opt == ENV_CLEAR)
		to_clear = env_list;
	ft_lstclear(to_clear, free);
}

void	ultimate_free(t_list **lst1, t_list **lst2)
{
	print_err1("memory");
	ft_lstclear(lst1, free);
	ft_lstclear(lst2, free);
	exit(EXIT_FAILURE);
}

static void	free_ptr(t_list **lst, t_list **env_list, void *ptr, int opt)
{
	t_list	**to_remove;
	t_list	*cur;
	t_list	*prev;

	to_remove = lst;
	if (opt == ENV_DELETE)
		to_remove = env_list;
	if (!ptr)
		return ;
	prev = *to_remove;
	cur = prev;
	while (cur && cur->content != ptr)
	{
		prev = cur;
		cur = cur->next;
	}
	if (!cur)
		return ;
	if (prev == cur)
		*to_remove = cur->next;
	else
		prev->next = cur->next;
	ft_lstdelone(cur, free);
}

static void	add_ptr(t_list **lst, t_list **env_list, void *ptr, int opt)
{
	t_list	**to_add;
	t_list	*node;

	to_add = lst;
	if (opt == ENV_CHECK)
		to_add = env_list;
	if (!ptr)
		collect_malloc(NULL, DESTROY);
	node = ft_lstnew(ptr);
	if (!node)
	{
		free(ptr);
		collect_malloc(NULL, DESTROY);
	}
	ft_lstadd_back(to_add, node);
}

void	collect_malloc(void *ptr, int option)
{
	static t_list	*lst = NULL;
	static t_list	*env_list = NULL;

	if (option == CHECK || option == ENV_CHECK)
		add_ptr(&lst, &env_list, ptr, option);
	else if (option == DELETE || option == ENV_DELETE)
		free_ptr(&lst, &env_list, ptr, option);
	else if (option == CLEAR || option == ENV_CLEAR)
		clear_list(&lst, &env_list, option);
	else if (option == DESTROY)
	{
		clear_list(&lst, &env_list, CLEAR);
		clear_list(&lst, &env_list, ENV_CLEAR);
	}
}
