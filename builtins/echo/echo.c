/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 13:58:02 by mouahman          #+#    #+#             */
/*   Updated: 2025/05/18 15:54:16 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

int	echo(t_cmd *cmd)
{
	t_list	*args;
	int		option;

	args = cmd->args->next;
	if (!args)
	{
		printf("\n");
		return (0);
	}
	option = 0;
	if (!ft_strcmp(args->content, "-n"))
	{
		option = 1;
		args = args->next;
	}
	while (args)
	{
		printf("%s", (char *)args->content);
		if (args->next)
			printf(" ");
		args = args->next;
	}
	if (!option)
		printf("\n");
	return (0);
}
