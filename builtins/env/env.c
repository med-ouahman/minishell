/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aid-bray <aid-bray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:23:34 by mouahman          #+#    #+#             */
/*   Updated: 2025/07/05 16:28:56 by aid-bray         ###   ########.fr       */
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

int	env(void)
{
	t_uint	i;

	i = 0;
	while (__environ[i])
	{
		if (check(__environ[i]))
			printf("%s\n", __environ[i]);
		i++;
	}
	return (0);
}
