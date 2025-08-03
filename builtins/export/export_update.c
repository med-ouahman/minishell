/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_update.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 02:24:56 by mouahman          #+#    #+#             */
/*   Updated: 2025/08/03 02:25:02 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

static int	update_arg(char *varname)
{
	char	*dup_var;
	t_uint	iter;
	t_uint	l;

	iter = 0;
	l = key_size(varname);
	while (__environ[iter])
	{
		if (!ft_strncmp(varname, __environ[iter],
				max(l, key_size(__environ[iter]))))
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

int	update_env_args(char **args)
{
	t_uint	i;

	i = 0;
	while (args[i])
	{
		update_arg(args[i]);
		i++;
	}
	return (0);
}
