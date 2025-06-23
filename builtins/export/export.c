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

#include "../../include/builtins.h"

int	export(t_cmd *cmd)
{
	// Check if the command is a built-in command
	if (cmd->is_buitlin)
		return 0xd;
	else
	{
		return (1);
	}
	return (0);
}

