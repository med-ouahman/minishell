/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 08:23:12 by mouahman          #+#    #+#             */
/*   Updated: 2025/08/02 08:23:16 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

int	sort_args(char **args)
{
	t_uint	i;
	long	find_index;

	i = 0;
	while (args[i])
	{
		if (to_add(args[i]))
		{
			find_index = find_nonexiting_var(args);
			if (find_index < 0)
			{
				return (array_size(args));
			}
			swap_ptrs(args + find_index, args + i);
		}
		i++;
	}
	return (0);
}

int	export_args(char **args)
{
	int		c;
	t_uint	count;

	count = 0;
	c = 0;
	check_valid(args, &c);
	sort_args(args);
	while (args[count] && to_add(args[count]))
		count++;
	print_arr(args);
	update_env_args(args + count);
	args[count] = NULL;
	add_env_vars(args);
	return (c);
}
