/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:38:20 by mouahman          #+#    #+#             */
/*   Updated: 2025/05/19 18:46:24 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

static t_bool	tobe_removed(char *var, char **argv)
{
	t_uint	l1;

	l1 = key_size(var);
	while (*argv)
	{
		if (!ft_strncmp(var, *argv, max(l1, key_size(*argv))))
			return (true);
		argv++;
	}
	return (false);
}

static int	remove_vars(char **args, t_uint rm_count)
{
	char	**new_env;
	t_uint	size;
	t_uint	i;
	t_uint	j;

	size = size_env() - rm_count;
	if (size < 0)
		return (-1);
	new_env = malloc((1 + size) * sizeof * new_env);
	collect_malloc(new_env, ENV_CHECK);
	i = 0;
	j = 0;
	while (__environ[i])
	{
		if (!tobe_removed(__environ[i], args))
			new_env[j++] = __environ[i];
		else
			collect_malloc(__environ[i], ENV_DELETE);
		i++;
	}
	return (0);
}

static t_uint	remove_invalid(char **args)
{
	t_uint	rm_count;
	t_uint	i;

	i = 0;
	rm_count = 0;
	while (args[i])
	{
		if (!check_valid_variable(args[i]) || !getenv(args[i]))
		{
			rm_count++;
			args[i] = NULL;
		}
		i++;
	}
	return (rm_count);
}

int	unset(char **args)
{
	t_uint	count;
	t_uint	rm_count;

	args++;
	if (!*args)
		return (0);
	count = array_size(args);
	rm_count = remove_invalid(args);
	remove_vars(args, rm_count);
	return (0);
}
