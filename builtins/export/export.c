/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aid-bray <aid-bray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:27:35 by mouahman          #+#    #+#             */
/*   Updated: 2025/07/06 16:55:32 by aid-bray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

static char	**step_copy(char **env)
{
	char	**new_env;
	int		i;

	new_env = malloc((size_env() + 1) * sizeof(char *));
	collect_malloc(new_env, CHECK);
	i = 0;
	while (env[i])
	{
		new_env[i] = env[i];
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

static t_bool	check_equal(char *var1, char *var2, t_uint l1)
{
	t_uint	l2;

	l2 = key_size(var2);
	if (ft_strncmp(var1, var2, max(l1, l2)) > 0)
		return (true);
	return (false);
}

void	sort_env(char **new_env)
{
	char	*swap;
	t_iter	i;
	t_iter	j;
	t_uint	l1;

	i = 0;
	while (new_env[i])
	{
		l1 = key_size(new_env[i]);
		j = i + 1;
		while (new_env[j])
		{
			if (check_equal(new_env[i], new_env[j], l1))
				swap_ptrs(new_env + i, new_env + j);
			j++;
		}
		i++;
	}
}

static int	print_env(char **env)
{
	char	old_val;
	t_uint	null_pos;
	t_uint	i;

	i = 0;
	while (env[i] != NULL)
	{
		printf("declare -x ");
		null_pos = key_size(env[i]);
		old_val = env[i][null_pos];
		env[i][null_pos] = 0;
		if (!old_val)
			printf("%s\n", env[i]);
		else
			printf("%s=\"%s\"\n", env[i], env[i] + null_pos + 1);
		env[i][null_pos] = old_val;
		i++;
	}
	return (0);
}

int	export(char **args)
{
	char	**tmp_env;

	if (!args[1])
	{
		tmp_env = step_copy(__environ);
		sort_env(tmp_env);
		print_env(tmp_env);
		collect_malloc(tmp_env, DELETE);
	}
	else
		export_add(args + 1);
	return (0);
}
