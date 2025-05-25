/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:27:35 by mouahman          #+#    #+#             */
/*   Updated: 2025/05/19 13:41:11 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/export.h"

int	export(char *key, char *value)
{
	char	**new_env;
	char	*res;
	size_t	size;
	int		index;
	int		i;

	res = ft_strjoin(key, value);
	index = index_of(__environ, key);
	if (NULL == res)
		return (-1);
	size = env_size() + 1;
	new_env = malloc((size + 1) * sizeof(char *));
	if (NULL == new_env)
		return (-1);
	i = 0;
	while (__environ[i])
	{
		new_env[i] = __environ[i];
		i++;
	}
	new_env[i] = res;
	if (NULL == new_env[i])
		return (-1);
	new_env[size] = NULL;
	__environ = new_env;
	return (0);
}
