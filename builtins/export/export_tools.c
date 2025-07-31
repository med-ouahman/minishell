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

unsigned int	key_size(char *s1)
{
	unsigned int	l1;

	l1 = 0;
	while (s1[l1] && s1[l1] != '=')
		l1++;
	return (l1);
}

void	swap_ptrs(void **p1, void **p2)
{
	void	*tmp;

	tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
}

void	destroy_env(char ***env)
{
	long	i;

	i = 0;
	while ((*env)[i])
		free((*env)[i++]);
	free((*env));
	*env = NULL;
}

long	size_env(char **env)
{
	long	size;

	size = 0;
	while (env[size])
		size++;
	return (size);
}

int	dup_env(char ***env)
{
	char			**new_env;
	unsigned int	size;
	unsigned int	i;

	i = 0;
	size = size_env(*env);
	new_env = malloc ((size + 1) * sizeof(char *));
	if (!new_env)
		return (print_file_error("env", "memory allocation"), 1);
	ft_memset(new_env, 0, (size + 1) * sizeof(char *));
	while ((*env)[i])
	{
		new_env[i] = ft_strdup((*env)[i]);
		if (!new_env[i])
		{
			print_file_error("env", "memory allocation");
			destroy_env(&new_env);
			return (1);
		}
		i++;
	}
	new_env[i] = NULL;
	*env = new_env;
	return (0);
}
