/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_exit_code.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 11:31:51 by mouahman          #+#    #+#             */
/*   Updated: 2025/06/26 11:35:30 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

int	last_exit_code(int new_value, int mode)
{
	static int	old_value;

	if (WRITE == mode)
	{
		old_value = new_value;
		return (old_value);
	}
	return (old_value);
}
