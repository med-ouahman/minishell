/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 21:21:18 by mouahman          #+#    #+#             */
/*   Updated: 2025/06/28 09:27:46 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/executor.h"

char	**split_path(void)
{
	char	*path;
	char	**pvs;

	path = getenv("PATH");
	pvs = ft_split(path + 5, ':');
	if (!pvs)
		return (NULL);
	return (pvs);
}
