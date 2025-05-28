/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 11:51:06 by mouahman          #+#    #+#             */
/*   Updated: 2025/05/18 13:56:33 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cd.h"

int	change_dir(char *path)
{
	int		c;
	int		index;
	char	*cwd;

	c = chdir(path);
	if (0 != c)
		return (-1);
	cwd = getcwd(NULL, 0);
	if (NULL == cwd)
		return (-1);
	index = index_of(__environ, "PWD=");
	if (-1 == index)
	{
		free(cwd);
		return (-1);
	}
	__environ[index] = ft_strjoin("PWD=", cwd);
	if (NULL == __environ[index])
	{
		free(cwd);
		return (-1);
	}
	free(cwd);
	return (c);
}
