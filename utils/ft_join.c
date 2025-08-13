/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aid-bray <aid-bray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 12:57:49 by aid-bray          #+#    #+#             */
/*   Updated: 2025/08/13 12:58:31 by aid-bray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/utils.h"

char	*ft_join(char *str1, int free1, char *str2, int free2)
{
	char	*new;

	if (!str1 && !str2)
		return (NULL);
	if (!str1 && str2)
		str1 = "";
	if (str1 && !str2)
		str2 = "";
	new = ft_strjoin(str1, str2);
	collect_malloc(new, CHECK);
	if (free1 && str1)
		collect_malloc(str1, DELETE);
	if (free2 && str2)
		collect_malloc(str2, DELETE);
	return (new);
}
