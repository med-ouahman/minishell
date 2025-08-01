/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 13:58:02 by mouahman          #+#    #+#             */
/*   Updated: 2025/07/01 15:59:05 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"


static int	is_noption(char *s)
{
	if (*s != '-')
		return (0);
	while (*s)
	{
		if (s != 'n')
			return (0);
		s++;
	}
	return (1);
}

int	echo(char **args)
{
	t_uint	i;
	char	*newline;

	newline = "\n";
	if (is_noption(args[1]))
		newline = "";
	i = 0;
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	printf("%s", newline);
	return (0);
}
