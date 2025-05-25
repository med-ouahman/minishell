/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 09:01:13 by mouahman          #+#    #+#             */
/*   Updated: 2025/02/01 21:24:50 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	handle_dot(int precision, char *s)
{
	int	len;
	int	count;
	int	i;

	len = ft_strlen(s);
	if (precision >= len || precision < 0)
		precision = len;
	i = 0;
	count = 0;
	while (i < precision)
	{
		count += ft_putchar(s[i], 0, 0);
		i++;
	}
	return (count);
}

static int	handle_space(int width, int fwidth, int precision, int len)
{
	int	count;
	int	i;

	if (width < 0)
		width *= -1;
	if (width == 0)
		width = fwidth;
	if (precision >= len || precision < 0)
		precision = len;
	i = 0;
	count = 0;
	while (i < width - precision)
	{
		count += ft_putchar(' ', 0, 0);
		i++;
	}
	return (count);
}

int	ft_putstr(char *s, int width, int precision, int fwidth)
{
	int	count;
	int	len;

	if (!s && precision < 6 && precision >= 0)
		return (ft_putstr("", width, precision, fwidth));
	if (!s)
		return (ft_putstr("(null)", width, precision, fwidth));
	count = 0;
	len = ft_strlen(s);
	if (width < 0)
		count += handle_dot(precision, s);
	count += handle_space(width, fwidth, precision, len);
	if (width >= 0)
		count += handle_dot(precision, s);
	return (count);
}
