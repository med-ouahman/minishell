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

#include "../../includes/echo.h"

int	echo(char *args[], char *options[])
{
	char	newline;

	newline = '\n';
	if (NULL == *options)
		newline = '\0';
	while (*args)
	{
		printf("%s", *args);
		printf(" ");
		args++;
	}
	if (newline)
		printf("%c", newline);
	return (0);
}
