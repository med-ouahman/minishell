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

void	swap_ptrs(char **p1, char **p2)
{
	char	*tmp;

	tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
}

void	destroy_env(char ***env)
{
	int	i;

	i = 0;
	if (!*env)
		return ;
	while ((*env)[i])
		free((*env)[i++]);
	free((*env));
	*env = NULL;
}

t_uint	size_env(char **env)
{
	int	size;

	size = 0;
	while (env[size])
		size++;
	return (size);
}

int	check_valid_variable(char *str)
{
	int		i;

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

void	dup_env(char ***env)
{
	char	**new_env;
	int		size;
	int		i;

	i = 0;
	size = size_env(*env);
	new_env = malloc ((size + 1) * sizeof(char *));
	collect_malloc(new_env, ENV_CHECK);
	while (i < size)
	{
		new_env[i] = ft_strdup((*env)[i]);
		collect_malloc(new_env[i], ENV_CHECK);
		i++;
	}
	new_env[i] = NULL;
	*env = new_env;
}
