/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aid-bray <aid-bray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 12:26:34 by mouahman          #+#    #+#             */
/*   Updated: 2025/08/13 13:12:24 by aid-bray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, size_t start, size_t len)
{
	size_t	i;
	size_t	slen;
	size_t	max_len;
	char	*substr;

	i = 0;
	slen = ft_strlen(s);
	if (slen <= start)
		return (ft_strdup(""));
	max_len = ft_strlen(s + start);
	if (len > max_len)
		len = max_len;
	substr = malloc(len * sizeof(char) + 1);
	if (!substr)
		return (NULL);
	while (i < len && s[i])
	{
		substr[i] = s[i + start];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}
