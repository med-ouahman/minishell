/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aid-bray <aid-bray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 13:16:20 by aid-bray          #+#    #+#             */
/*   Updated: 2025/07/06 16:43:38 by aid-bray         ###   ########.fr       */
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
	int		i;
	char	*dup_new;

	i = 0;
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
	int		i;
	int		index;
	int		c;

	i = 0;
	c = 0;
	while (argv[i])
	{
		if (check_valid_variable(argv[i]))
		{
			index = var_exists(argv[i]);
			if (index)
				change_var(argv[i]);
			else
				add_var(argv[i]);
		}
		else
		{
			c = 1;
			print_err3("export", argv[i], "not a valid identifier");
		}
		i++;
	}
	return (c);
}
