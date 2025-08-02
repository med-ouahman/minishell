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

int		to_add(char *key)
{
	t_uint	i;
	size_t	len;

	i = 0;
	len = key_size(key);
	while (__environ[i])
	{
		if (!ft_strncmp(key, __environ[i], len))
			return (1);
		i++;
	}
	return (0);
}

long	find_nonexiting_var(char **args)
{
	t_uint	i;

	i = 0;
	while (args[i])
	{
		if (!to_add(args[i]))
			return (i);
		i++;
	}
	return (-1);
}

int	update_arg(char *varname)
{
	char	*dup_var;
	t_uint	iter;
	t_uint	l;

	iter = 0;
	l = key_size(varname);
	while (__environ[iter])
	{
		if (!ft_strncmp(varname, __environ[iter], l))
		{
			dup_var = ft_strdup(varname);
			collect_malloc(dup_var, ENV_CHECK);
			collect_malloc(__environ[iter], ENV_DELETE);
			__environ[iter] = dup_var;
		}
		iter++;
	}
	return (0);
}

static void	add_new_vars(char **new_env, char **varnames)
{
	t_uint	i;
	char	*dup_var;

	i = 0;
	while (varnames[i])
	{
		dup_var = ft_strdup(varnames[i]);
		collect_malloc(dup_var, ENV_CHECK);
		new_env[i] = dup_var;
		i++;
	}
}

int	add_args(char **args)
{
	char	***env;
	char	**new_env;
	t_uint	size;
	t_uint	i;
	
	env = &__environ;
	size = size_env(__environ) + size_env(args);
	new_env = malloc((size + 1) * sizeof(char *));
	collect_malloc(new_env, ENV_CHECK);
	i = 0;
	while (__environ[i])
	{
		new_env[i] = __environ[i];
		i++;
	}
	add_new_vars(new_env + i, args);
	new_env[size] = NULL;
	collect_malloc(__environ, ENV_DELETE);
	*env = new_env;
	return (0);
}

int	update_env_args(char **args, t_uint count)
{
	t_uint	end_index;
	t_uint	i;

	end_index = size_env(__environ) - count;
	i = 0;
	while (i < end_index)
	{
		update_arg(args[i]);
		i++;
	}
	return (0);
}

t_uint	sort_args(char **args)
{
	t_uint	add_count;
	t_uint	i;
	long	find_index;

	i = 0;
	add_count = 0;
	while (args[i])
	{
		if (to_add(args[i]))
		{
			find_index = find_nonexiting_var(args);
			printf("find index: %ld\n", find_index);
			if (find_index < 0)
			{
				printf("no args to update\n");
				return (size_env(__environ));
			}
			swap_ptrs(args + find_index, args + i);
			add_count++;
		}
		i++;
	}
	return (add_count);
}
