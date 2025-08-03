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

	new_env = malloc((size_env(env) + 1) * sizeof(char *));
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

static void	sort_env(char **new_env)
{
	t_uint	i;
	t_uint	j;
	t_uint	l;

	i = 0;
	while (new_env[i])
	{
		j = i + 1;
		l = key_size(new_env[i]);
		while (new_env[j])
		{
			if (ft_strncmp(new_env[i], new_env[j],
					max(l, key_size(new_env[j]))) > 0)
				swap_ptrs(new_env + i, new_env + j);
			j++;
		}
		i++;
	}
}

int	print_env(void)
{
	char	**env;
	int		i;
	int		j;

	env = step_copy(__environ);
	sort_env(env);
	i = 0;
	while (env[i] != NULL)
	{
		printf("declare -x ");
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			printf("%c", env[i][j++]);
		if (env[i][j] == '=')
			printf("=\"%s\"", &env[i][j + 1]);
		printf("\n");
		i++;
	}
	collect_malloc(env, DELETE);
	return (0);
}
