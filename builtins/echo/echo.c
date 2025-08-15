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
	s++;
	while (*s)
	{
		if (*s != 'n')
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
	i = 1;
	if (args[1] && is_noption(args[1]))
	{
		newline = "";
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1])
			ft_putstr_fd("\n", STDOUT_FILENO);
		i++;
	}
	ft_putstr_fd(newline, STDOUT_FILENO);
	return (0);
}
