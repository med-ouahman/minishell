/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putaddress.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 10:03:48 by mouahman          #+#    #+#             */
/*   Updated: 2025/02/01 21:25:00 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	handle_space(int width, int len)
{
	int	count;

	count = 0;
	if (width < 0)
		width *= -1;
	if (len > width)
		return (0);
	while (width - len)
	{
		count += ft_putchar(' ', 0, 0);
		len++;
	}
	return (count);
}

static int	print_addr(char *s, int len)
{
	int	count;

	count = write(1, "0x", 2);
	count += write(1, s, len);
	return (count);
}

int	ft_putaddress(void *addr, int width, int fwidth)
{
	size_t	n;
	char	*s;
	int		len;
	int		count;

	if (!addr)
		return (ft_putstr("(nil)", width, -1, fwidth));
	n = (unsigned long)addr;
	s = ft_itoa_base(n, "0123456789abcdef");
	if (!s)
		return (0);
	len = ft_strlen(s);
	count = 0;
	if (width == 0)
		width = fwidth;
	if (width < 0)
		count += print_addr(s, len);
	count += handle_space(width, len + 2);
	if (width >= 0)
		count += print_addr(s, len);
	free(s);
	return (count);
}
