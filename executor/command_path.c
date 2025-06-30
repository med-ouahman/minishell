/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:02:54 by mouahman          #+#    #+#             */
/*   Updated: 2025/06/29 14:33:37 by mouahman         ###   ########.fr       */
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
	cmdpath = malloc(size * sizeof *cmdpath);
	if (!cmdpath)
		return (NULL);
	cmdpath[0] = '\0';
	ft_strlcat(cmdpath, pvs[i], size);
	ft_strlcat(cmdpath, "/", size);
	ft_strlcat(cmdpath, cmd, size);
	return (cmdpath);
}

int	check_access(char **path, char **pvs, char *cmd)
{
	int		i;

	i = -1;
	while (i == -1 || pvs[i])
	{
		*path = get_cmdpath(i, pvs, cmd);
		if (!*path)
			return (access_exit_code(1, WRITE));
		if (!access(*path, F_OK))
		{
			if (!access(*path, X_OK))
			{
				*path = *path;
				return (0);
			}
			return (errno);
		}
		free(*path);
		*path = NULL;
		i++;
	}
	return (errno);
}

char	*command_path(char **pvs, char *cmd)
{
	char	*path;
	int		c;

	path = NULL;
	c = check_access(&path, pvs, cmd);
	if (ENOENT == c)
	{
		access_exit_code(127, WRITE);
		printf("minishell: %s: command not found\n", cmd);
		return (NuLL);
	}
	else if (EACCES == c)
	{
		access_exit_code(126, WRITE);
		printf("minishell: %s: Permission denied\n", path);
		return (NULL);
	}
	return (path);
}
