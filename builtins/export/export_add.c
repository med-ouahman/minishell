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

#include "../../include/minishell.h"

void	remove_invalid(char **args, t_uint rem_index)
{
	t_uint	last;

	last = 0;
	while (args[last + 1])
	{
		last++;
	}
	swap_ptrs(args + last, rem_index + args);
	args[last] = NULL;
}

int	check_exist_var(char *str)
{
	int	i;
	int	eq;

	eq = (int)(ft_strchr(str, '=') - str);
	if (eq < 0)
		eq = ft_strlen(str);
	else
		eq--;
	i = 0;
	while (__environ[i])
	{
		if (ft_strncmp(__environ[i], str, eq) == 0)
			return (1);
		i++;
	}
	return (0);
}

void	change_var(char *new, int index)
{
	char	*dup_new;

	if (!ft_strchr(new, '='))
		return ;
	dup_new = ft_strdup(new);
	collect_malloc(dup_new, ENV_CHECK);
	collect_malloc(__environ[index], ENV_DELETE);
	__environ[index] = dup_new;
}

void	add_var(char ***env, char *new_var)
{
	int		i;
	int		size;
	char	*dup_new;
	char	**new_env;

	i = 0;
	size = size_env(*env);
	dup_new = ft_strdup(new_var);
	collect_malloc(dup_new, ENV_CHECK);
	new_env = malloc(sizeof(char *) * (size + 2));
	collect_malloc(new_env, ENV_CHECK);
	while ((*env)[i])
	{
		new_env[i] = (*env)[i];
		i++;
	}
	new_env[size] = dup_new;
	new_env[size + 1] = NULL;
	collect_malloc(*env, ENV_DELETE);
	__environ = new_env;
}

int	check_valid(char **args, int *c)
{
	t_uint	i;

	i = 0;
	while (args[i])
	{
		if (!check_valid_variable(args[i]))
		{
			if (c)
			{
				*c = 1;
				print_err3("export", args[i], "not a valid identifier");
			}
			remove_invalid(args, i);
			i = 0;
			continue ;
		}
		i++;
	}
	return (0);
}
