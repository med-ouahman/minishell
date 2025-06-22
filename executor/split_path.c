/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 21:21:18 by mouahman          #+#    #+#             */
/*   Updated: 2025/06/20 21:26:00 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/executor.h"

char	*extract_path(char **envp)
{

	while (*envp)
	{
		if (!ft_strncmp(*envp, "PATH=", 5))
			return (*envp);
		envp++;
	}
	return (NULL);
}

char	**split_path(char **envp)
{
	char	*path;
	char	**pvs;

	path = extract_path(envp);
	pvs = ft_split(path + 5, ':');
	if (!pvs)
		return (NULL);
	return (pvs);
}
