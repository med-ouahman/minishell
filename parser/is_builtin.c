/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 09:30:19 by mouahman          #+#    #+#             */
/*   Updated: 2025/07/06 15:38:55 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

int is_builtin(char *cmd)
{
    if (!ft_strcmp(cmd, "cd"))
		return (CD);
	else if (!ft_strcmp(cmd, "pwd"))
		return (PWD);
	else if (!ft_strcmp(cmd, "exit"))
		return (EXIT);
	else if (!ft_strcmp(cmd, "echo"))
		return (ECHO);
	else if (!ft_strcmp(cmd, "export"))
		return (EXPORT);
	else if (!ft_strcmp(cmd, "unset"))
		return (UNSET);
	else if (!ft_strcmp(cmd, "env"))
        return (ENV);
    return (NOT);
}
