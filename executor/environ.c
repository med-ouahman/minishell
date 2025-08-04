/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 21:28:39 by mouahman          #+#    #+#             */
/*   Updated: 2025/07/31 21:28:43 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/executor.h"

#define INIT 0
#define ADD 1
#define REMOVE 2

static int	add_to_environ(char **env, char *key, char *value)
{
	(void)env;
	(void)key;
	(void)value;
	return (0);
}

static int	remove_from_environ(char **env, char *key)
{
	(void)env;
	(void)key;
	return (0);
}

char	**duplicate_env(void)
{
	char	**new_environ;
	t_uint	i;

	new_environ = malloc((1 + size_env()) * sizeof(char *));
	collect_malloc(new_environ, CHECK);
	i = 0;
	while (__environ[i])
	{
		new_environ[i] = ft_strdup(__environ[i]);
		collect_malloc(new_environ[i], CHECK);
		i++;
	}
	new_environ[i] = NULL;
	return (new_environ);
}

char	**environ(int opt, char *key, char *value)
{
	static char	**env;

	if (INIT == opt)
		env = duplicate_env();
	if (ADD == opt)
	{
		add_to_environ(env, key, value);
	}
	else if (REMOVE == opt)
	{
		remove_from_environ(env, key);
	}
	return (env);
}
