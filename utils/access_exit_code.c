/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access_exit_code.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aid-bray <aid-bray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 13:10:34 by mouahman          #+#    #+#             */
/*   Updated: 2025/08/06 11:06:19 by aid-bray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

int	access_exit_code(int new_val, int mode)
{
	static int	exit_code;

	if (mode == READ)
		return (exit_code);
	if (mode == WRITE)
		exit_code = new_val;
	return (exit_code);
}
