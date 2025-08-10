/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aid-bray <aid-bray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 13:16:20 by aid-bray          #+#    #+#             */
/*   Updated: 2025/08/09 11:59:23 by aid-bray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

t_uint	size_env(void)
{
	t_uint	size;

	size = 0;
	while (__environ[size])
	{
		size++;
	}
	return (size);
}

int	var_exists(char *varname)
{
	t_uint	l1;
	t_iter	i;

	l1 = key_size(varname);
	i = 0;
	while (__environ[i])
	{
		if (!ft_strncmp(__environ[i], varname, max(l1, key_size(__environ[i]))))
		{
			return (1);
		}
		i++;
	}
	return (0);
}

void	change_var(char *new)
{
	t_uint	index;
	t_uint	l1;
	char	*dup_new;

	if (!ft_strchr(new, '='))
		return ;
	l1 = key_size(new);
	index = 0;
	while (__environ[index]
		&& ft_strncmp(__environ[index], new, max(l1, key_size(new))))
		index++;
	if (!__environ[index])
		return ;
	dup_new = ft_strdup(new);
	collect_malloc(dup_new, ENV_CHECK);
	collect_malloc(__environ[index], ENV_DELETE);
	__environ[index] = dup_new;
}

void	add_var(char *new_var)
{
	int		i;
	int		size;
	char	*dup_new;
	char	**new_env;

	i = 0;
	size = size_env();
	dup_new = ft_strdup(new_var);
	collect_malloc(dup_new, ENV_CHECK);
	new_env = malloc(sizeof(char *) * (size + 2));
	collect_malloc(new_env, ENV_CHECK);
	while (__environ[i])
	{
		new_env[i] = __environ[i];
		i++;
	}
	new_env[size] = dup_new;
	new_env[size + 1] = NULL;
	collect_malloc(__environ, ENV_DELETE);
	__environ = new_env;
}

int	export_add(char **argv)
{
	int		c;

	c = 0;
	while (*argv)
	{
		if (check_valid_variable(*argv))
		{
			if (var_exists(*argv))
				change_var(*argv);
			else
				add_var(*argv);
		}
		else
		{
			c = 1;
			print_err3("export", *argv, "not a valid identifier");
		}
		argv++;
	}
	return (c);
}
