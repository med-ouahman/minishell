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

int	echo(char **args)
{
	int				option;
	unsigned int	i;

	if (!args[1])
	{
		printf("\n");
		return (0);
	}
	option = 0;
	i = 1;
	if (!ft_strcmp(args[1], "-n"))
	{
		option = 1;
		i++;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (!option)
		printf("\n");
	return (0);
}
