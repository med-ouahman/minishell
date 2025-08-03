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

int	check_equal(char *var1, char *var2)
{
	int	eq1;
	int	eq2;

	eq1 = ft_strchr(var1, '=') - var1;
	if (eq1 < 0)
		eq1 = ft_strlen(var1);
	eq2 = ft_strchr(var2, '=') - var2;
	if (eq2 < 0)
		eq2 = ft_strlen(var2);
	if (eq1 > eq2)
		return (eq2 - 1);
	return (eq1 - 1);
}

void	sort_env(char **new_env)
{
	char	*swap;
	int		j;
	int		i;
	int		eq;

	i = 0;
	while (new_env[i])
	{
		j = i + 1;
		while (new_env[j])
		{
			eq = check_equal(new_env[i], new_env[j]);
			if (ft_strncmp(new_env[i], new_env[j], eq) > 0)
			{
				swap = new_env[i];
				new_env[i] = new_env[j];
				new_env[j] = swap;
			}
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

int	export(char **args)
{
	if (!args[1])
	{
		print_env();
	}
	else
		export_add(args + 1);
	return (0);
}
