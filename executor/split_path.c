/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 21:21:18 by mouahman          #+#    #+#             */
/*   Updated: 2025/07/03 09:43:47 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/executor.h"

char	**split_path(void)
{
	char	*path;
	char	**paths;

	path = getenv("PATH");
	if (!path)
		return (NULL);
	paths = ft_split(path, ':');
	garbage_collector(paths, COLLECT);
	return (paths);
}
