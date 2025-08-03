/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 02:24:42 by mouahman          #+#    #+#             */
/*   Updated: 2025/08/03 02:24:46 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

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

int	add_env_vars(char **args)
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
