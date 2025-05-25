/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_capital.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 09:28:23 by mouahman          #+#    #+#             */
/*   Updated: 2025/02/01 21:24:02 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	handle_dot(char *s, int len, t_flags flags)
{
	int	count;
	int	i;

	count = 0;
	if (flags.c && flags.w <= 0)
		count += write(1, "0X", 2);
	if (flags.p <= len)
		return (write(1, s, len) + count);
	i = 0;
	while (i < flags.p - len)
	{
		count += ft_putchar('0', 0, 0);
		i++;
	}
	if (flags.p == 0 && s[0] == '0')
		return (count);
	count += write(1, s, len);
	return (count);
}

static int	handle_space(t_flags flags, int precision, int len, int p)
{
	int		count;
	int		width;
	char	c;

	c = '0';
	width = flags.w;
	count = 0;
	if (flags.c && width > 0)
		count += write(1, "0X", 2);
	if (width <= 0 || (width >= 0 && flags.p >= 0))
		c = ' ';
	if (width == 0)
		width = flags.fw;
	if (width < 0)
		width *= -1;
	width -= p;
	if (len >= precision)
		precision = len;
	while (width - (precision++) > 0)
		count += ft_putchar(c, 0, 0);
	return (count);
}

int	ft_putnbr_up(unsigned int n, t_flags flags)
{
	char	*s;
	int		len;
	int		p;
	int		count;

	if (n == 0 && flags.p == 0)
		s = ft_strdup("");
	else
		s = ft_itoa_base(n, "0123456789ABCDEF");
	if (!s)
		return (0);
	len = ft_strlen(s);
	p = 0;
	if (n == 0)
		flags.c = '\0';
	if (flags.c == '#')
		p = 2;
	count = 0;
	if (flags.w < 0)
		count += handle_dot(s, len, flags);
	count += handle_space(flags, flags.p, len, p);
	if (flags.w >= 0)
		count += handle_dot(s, len, flags);
	free(s);
	return (count);
}
