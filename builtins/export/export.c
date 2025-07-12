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
	char			**new_env;
	unsigned int	i;

	new_env = malloc ((size_env(env) + 1) * sizeof(char *));
	if (!new_env)
		return (print_file_error("env", "memory allocation"), NULL);
	i = 0;
	while (env[i])
	{
		new_env[i] = env[i];
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

char	**sort_env(char **env)
{
	char			**new_env;
	char			*swap;
	unsigned int	j;
	unsigned int	i;

	i = 0;
	new_env = step_copy(env);
	if (!new_env)
		return (NULL);
	while (new_env[i])
	{
		j = i + 1;
		while (env[j])
		{
			if (ft_strcmp(new_env[i], new_env[j]) > 0)
			{
				swap = new_env[i];
				new_env[i] = new_env[j];
				new_env[j] = swap;
			}
			j++;
		}
		i++;
	}
	return (new_env);
}

int	print_env(void)
{
	char			**tmp;
	unsigned int	i;
	size_t			j;

	i = 0;
	tmp = sort_env(__environ);
	if (!tmp)
		return (1);
	while (tmp[i] != NULL)
	{
		printf("declare -x ");
		j = 0;
		while (tmp[i][j] && tmp[i][j] != '=')
			printf("%c", tmp[i][j++]);
		if (tmp[i][j] == '=')
			printf("=\"%s\"", &tmp[i][j + 1]);
		printf("\n");
		i++;
	}
	free(tmp);
	return (0);
}

int	export(char **args)
{
	// static int	is_set = 0;

	// if (!is_set)
	// {
	// 	if (dup_env(&__environ))
	// 		return (1);
	// 	is_set = 1;
	// }
	if (!args[1])
		return (print_env(), 0);
	if (export_add(args + 1))
	{
		destroy_env(&__environ);
		return (1);
	}
	return (0);
}
