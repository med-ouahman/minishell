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

#include "../../include/minishell.h"

static t_bool	to_remove(char *var, char **argv)
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

static t_uint	add_nonremoved(char **new_env, char **args, t_uint i, t_uint j)
{
	if (!to_remove(__environ[i], args))
	{
		new_env[j] = __environ[i];
	}
	else
		collect_malloc(__environ[i], ENV_DELETE);
	return (++j);
}

static int	remove_vars(char **args)
{
	char	**new_env;
	long	size;
	t_uint	i;
	t_uint	j;

	size = size_env() - array_size(args);
	if (size < 0)
		return (0);
	new_env = malloc((1 + size) * sizeof(char *));
	collect_malloc(new_env, ENV_CHECK);
	i = 0;
	j = 0;
	while (__environ[i])
	{
		j = add_nonremoved(new_env, args, i, j);
		i++;
	}
	new_env[j] = NULL;
	collect_malloc(__environ, ENV_DELETE);
	__environ = new_env;
	return (0);
}

int	unset(char **args)
{
	args++;
	if (!*args)
		return (0);
	check_valid(args, NULL);
	sort_args(args);
	while (*args && to_add(*args))
	{
		args++;
	}
	if (!*args)
		return (0);
	remove_vars(args);
	return (0);
}
