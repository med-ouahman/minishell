/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:02:54 by mouahman          #+#    #+#             */
/*   Updated: 2025/07/06 11:44:50 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/executor.h"

static char	*get_cmdpath(int i, char **paths, char *cmd)
{
	char	*cmdpath;
	size_t	size;

	if (i == -1)
		return (ft_strdup(cmd));
	size = ft_strlen(paths[i]) + ft_strlen(cmd) + 2;
	cmdpath = malloc(size * sizeof *cmdpath);
	if (!cmdpath)
		return (NULL);
	cmdpath[0] = '\0';
	ft_strlcat(cmdpath, paths[i], size);
	ft_strlcat(cmdpath, "/", size);
	ft_strlcat(cmdpath, cmd, size);
	return (cmdpath);
}

int	check_access(char **path, char **paths, char *cmd)
{
	int		i;

	i = -1;
	if (!*cmd)
		return (ENOENT);
	if (!paths)
	{
		*path = ft_strdup(cmd);
		return (0);
	}
	while (i == -1 || paths[i])
	{
		*path = get_cmdpath(i, paths, cmd);
		if (!*path)
			return (-1);
		if (!access(*path, F_OK))
		{
			if (!access(*path, X_OK))
				return (0);
			return (errno);
		}
		free(*path);
		*path = NULL;
		i++;
	}
	return (errno);
}

char	*command_path(char **paths, char *cmd)
{
	char	*path;
	int		c;

	path = NULL;
	c = check_access(&path, paths, cmd);
	if (0 > c)
		access_exit_code(1, WRITE);
	if (ENOENT == c)
	{
		access_exit_code(127, WRITE);
		printf("minishell: %s: command not found\n", cmd);
		return (NULL);
	}
	else if (EACCES == c)
	{
		access_exit_code(126, WRITE);
		printf("minishell: %s: Permission denied\n", path);
		return (NULL);
	}
	return (path);
}
