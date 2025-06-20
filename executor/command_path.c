/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_access.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:02:54 by mouahman          #+#    #+#             */
/*   Updated: 2025/03/21 05:31:00 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/executor.h"

static char	*get_cmdpath(int i, char **pvs, char *cmd)
{
	char	*cmdpath;
	size_t	size;

	if (i == -1)
		return (ft_strdup(cmd));
	size = ft_strlen(pvs[i]) + ft_strlen(cmd) + 2;
	cmdpath = malloc(size * sizeof(char));
	if (!cmdpath)
		return (NULL);
	cmdpath[0] = '\0';
	ft_strlcat(cmdpath, pvs[i], size);
	ft_strlcat(cmdpath, "/", size);
	ft_strlcat(cmdpath, cmd, size);
	return (cmdpath);
}

char    *check_access(char *path, char *cmd)
{
	char	**pvs;
	char    *cmdpath;
	int		i;

	pvs = ft_split(path + 5, ':');
	if (!pvs)
		return (NULL);
	i = -1;
	while (i == -1 || pvs[i])
	{
		cmdpath = get_cmdpath(i, pvs, cmd);
		if (!cmdpath)
			return (NULL);
		if (!access(cmdpath, F_OK))
		{
			if (!access(cmdpath, X_OK))
				return (cmdpath);
		}
		free(cmdpath);
		i++;
	}
	return (NulL);
}
