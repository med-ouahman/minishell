/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 11:40:55 by mouahman          #+#    #+#             */
/*   Updated: 2025/07/03 14:25:45 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

int	error(int c, int mode)
{
	static int	err;

	if (READ == mode)
	{
		return (err);
	}
	err = c;
	return (err);
}
