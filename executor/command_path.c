/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:02:54 by mouahman          #+#    #+#             */
/*   Updated: 2025/07/06 15:15:21 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/executor.h"

int	is_executable(char *__pathname, char **path)
{
	if (!access(__pathname, F_OK) && !access(__pathname, X_OK))
	{
		*path = __pathname;
		return (0);
	}
	return (errno);
}

int	is_path(char *cmd)
{
	if (!ft_strncmp(cmd, "./", 2))
		return (1);
	if (*cmd == '/')
		return (1);
	return (0);
}

static int	__file_state_(char *__file_path)
{
	struct stat	buf;
	int			c;

	c = stat(__file_path, &buf);
	if (0 > c)
	{
		return (-1);
	}
	if (S_ISREG(buf.st_mode))
		return (0);
	return (-1);
}

static char	*join_paths(int i, char **paths, char *cmd)
{
	char	*cmdpath;
	size_t	size;

	size = ft_strlen(paths[i]) + ft_strlen(cmd) + 2;
	cmdpath = malloc(size * sizeof *cmdpath);
	if (!cmdpath)
		return (NULL);
	*cmdpath = 0;
	ft_strlcat(cmdpath, paths[i], size);
	ft_strlcat(cmdpath, "/", size);
	ft_strlcat(cmdpath, cmd, size);
	return (cmdpath);
}

int	check_access(char **path, char **paths, char *cmd)
{
	int		i;

	i = 0;
	if (!*cmd)
		return (ENOENT);
	if (is_path(cmd))
		return (is_executable(cmd, path));
	while (paths[i])
	{
		*path = join_paths(i, paths, cmd);
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
	if (ENOENT == c || __file_state_(path))
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
