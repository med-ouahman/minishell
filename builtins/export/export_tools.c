/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aid-bray <aid-bray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 13:17:54 by aid-bray          #+#    #+#             */
/*   Updated: 2025/07/06 17:05:00 by aid-bray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

t_uint	size_env(void)
{
	t_uint	size;

	size = 0;
	while (__environ[size])
		size++;
	return (size);
}

int	check_valid_variable(char *str)
{
	t_uint	i;

	i = 0;
	if (ft_isalpha(*str) || *str == '_')
	{
		while (str[i] && (ft_isalnum(str[i]) || str[i] == '_') && str[i] != '=')
			i++;
		if (str[i] != '=' && str[i] != '\0')
			return (0);
		return (1);
	}
	return (0);
}

void	dup_env(void)
{
	char	**new_env;
	t_uint	size;
	t_uint	i;

	i = 0;
	size = size_env();
	new_env = malloc ((size + 1) * sizeof(char *));
	collect_malloc(new_env, ENV_CHECK);
	while (i < size)
	{
		new_env[i] = ft_strdup(__environ[i]);
		collect_malloc(new_env[i], ENV_CHECK);
		i++;
	}
	new_env[i] = NULL;
	__environ = new_env;
}

int	to_add(char *key)
{
	t_uint	i;
	size_t	l1;

	i = 0;
	l1 = key_size(key);
	while (__environ[i]
		&& ft_strncmp(key, __environ[i], max(l1, key_size(__environ[i]))))
	{
		i++;
	}
	if (!__environ[i])
		return (1);
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
