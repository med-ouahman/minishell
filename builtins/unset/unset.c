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

static int	check_equal(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '=')
			return (i);
		i++;
	}
	return (i);
}

static long	searsh_var(char *var)
{
	long	i;
	int		eq;

	i = 0;
	eq = check_equal(var);
	while (__environ[i])
	{
		if (ft_strncmp(__environ[i], var, eq) == 0)
		{
			if (!var[eq] &&
				(__environ[i][eq] == '=' || !__environ[i][eq]))
				return (i);
		}
		i++;
	}
	return (-1);
}

static int	del_from_env(char ***env, long n)
{
	long	i;
	long	j;
	long	size;
	char	**new_env;

	size = size_env(*env);
	new_env = malloc ((size + 1) * sizeof(char *));
	if (!new_env)
		return (print_file_error("unset", "memory allocation"), 1);
	i = 0;
	j = 0;
	while ((*env)[j])
	{
		if (j == n)
			j++;
		new_env[i] = (*env)[j];
		j++;
		i++;
	}
	new_env[i] = NULL;
	(*env) = new_env;
	return (0);
}

int	unset(char **args)
{
	long	i;

	args++;
	while (args)
	{
		i = searsh_var(*args);
		if (i >= 0)
		{
			if (del_from_env(&__environ, i))
				return (1);
		}
		args++;
	}
	return (0);

}
