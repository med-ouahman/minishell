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
	t_uint	len;

	l1 = key_size(var);
	while (*argv)
	{
		len = ft_strlen(*argv);
		if (!ft_strncmp(var, *argv, max(l1, len)) && len == l1)
		{
			return (true);
		}
		argv++;
	}
	return (false);
}

static void	realloc_env(t_uint size, t_uint rm_count)
{
	char	**new_env;
	t_iter	i;
	t_iter	j;

	i = 0;
	j = 0;
	new_env = malloc((size - rm_count + 1) * sizeof * new_env);
	collect_malloc(new_env, ENV_CHECK);
	while (i < size)
	{
		if (__environ[i])
		{
			new_env[j] = __environ[i];
			j++;
		}		
		i++;
	}
	new_env[j] = NULL;
	collect_malloc(__environ, ENV_DELETE);
	__environ = new_env;
}

static t_uint	remove_invalid(char **args, t_uint env_size)
{
	t_uint	i;
	t_uint	rm_count;

	i = 0;
	rm_count = 0;
	while (i < env_size)
	{
		if (tobe_removed(__environ[i], args))
		{
			rm_count++;
			collect_malloc(__environ[i], ENV_DELETE);
			__environ[i] = NULL;
		}
		i++;
	}
	return (rm_count);
}

int	unset(char **args)
{
	t_uint	env_size;
	t_uint	rm_count;

	args++;
	if (!*args)
		return (0);
	env_size = size_env();
	rm_count = remove_invalid(args, env_size);
	if (rm_count == 0 || rm_count > env_size)
		return (0);
	realloc_env(env_size, rm_count);
	return (0);
}
