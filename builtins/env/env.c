/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aid-bray <aid-bray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:23:34 by mouahman          #+#    #+#             */
/*   Updated: 2025/08/07 05:07:11 by aid-bray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

static int	check(char *s)
{
	t_uint	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	env(char **args)
{
	t_uint	i;

	i = 0;
	if (args[1])
	{
		print_err2("env", "too many arguments");
		return (1);
	}
	while (__environ[i])
	{
		if (check(__environ[i]))
			printf("%s\n", __environ[i]);
		i++;
	}
	return (0);
}
