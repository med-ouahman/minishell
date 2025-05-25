/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 08:52:17 by mouahman          #+#    #+#             */
/*   Updated: 2025/02/01 21:23:34 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	handle_space(int width, int fwidth)
{
	int	count;
	int	i;

	if (width < 0)
		width *= -1;
	if (width == 0)
		width = fwidth;
	i = 0;
	count = 0;
	while (i < width - 1)
	{
		count += write(1, " ", 1);
		i++;
	}
	return (count);
}

int	ft_putchar(char c, int width, int fwidth)
{
	int	count;

	count = 0;
	if (width < 0)
		count += write(1, &c, 1);
	count += handle_space(width, fwidth);
	if (width >= 0)
		count += write(1, &c, 1);
	return (count);
}
