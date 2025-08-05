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

static char	*join_paths(char *path, char *cmd)
{
	char	*cmdpath;
	size_t	size;

	size = ft_strlen(path) + ft_strlen(cmd) + 2;
	cmdpath = malloc(size * sizeof * cmdpath);
	collect_malloc(cmdpath, CHECK);
	*cmdpath = 0;
	ft_strlcat(cmdpath, path, size);
	ft_strlcat(cmdpath, "/", size);
	ft_strlcat(cmdpath, cmd, size);
	return (cmdpath);
}

static int	check_access(char **path, char *cmd)
{
	char	*next_path;

	*path = NULL;
	if (!*cmd || (!access(cmd, F_OK) && !S_ISREG(get_file_type(cmd))))
		return (ENOENT);
	next_path = get_next_path(getpath(0), 0);
	while (next_path)
	{
		*path = join_paths(next_path, cmd);
		if (!access(*path, F_OK))
		{
			if (!access(*path, X_OK))
			{
				get_next_path(getpath(1), 1);
				return (0);
			}
			return (errno);
		}
		collect_malloc(*path, DELETE);
		*path = NULL;
		next_path = get_next_path(getpath(1), 0);
	}
	return (errno);
}

static	char	*is_path_unset(char *cmd)
{
	char	*path;

	if (access(cmd, F_OK | X_OK) == 0)
	{
		path = ft_strjoin("./", cmd);
		collect_malloc(cmd, DELETE);
		collect_malloc(path, CHECK);
		return (path);
	}
	else
	{
		if (errno == EACCES)
			access_exit_code(NOT_FOUND, WRITE);
		else if (errno == ENOENT)
			access_exit_code(PERMISSION_DENIED, WRITE);
		print_err2(cmd, strerror(errno));
		return (NULL);
	}
	return (path);
}

char	*command_path(char *cmd)
{
	char	*path;
	int		c;

	if (getenv("PATH") == NULL)
		return (is_path_unset(cmd));
	if (is_path(cmd))
	{
		if (!is_executable(cmd))
			return (cmd);
		return (NULL);
	}
	c = check_access(&path, cmd);
	if (0 > c)
		access_exit_code(EXIT_FAILURE, WRITE);
	if (ENOENT == c)
	{
		access_exit_code(NOT_FOUND, WRITE);
		print_err2(cmd, "command not found");
	}
	else if (EACCES == c)
	{
		access_exit_code(PERMISSION_DENIED, WRITE);
		print_err2(path, strerror(errno));
	}
	return (path);
}
