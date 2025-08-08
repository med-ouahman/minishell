/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aid-bray <aid-bray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:02:54 by mouahman          #+#    #+#             */
/*   Updated: 2025/08/06 10:55:05 by aid-bray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/executor.h"

static int	is_regular(char *cmd)
{
	mode_t	file_type;

	if (get_file_type(cmd, &file_type))
		return (0);
	if (S_ISREG(file_type))
		return (1);
	return (0);
}

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
	if (!*cmd || (access(cmd, F_OK) == 0 && !is_regular(cmd)))
		return (ENOENT);
	next_path = get_next_path(getpath(0), 0);
	while (next_path)
	{
		*path = join_paths(next_path, cmd);
		if (!access(*path, F_OK))
		{
			if (!access(*path, X_OK))
			{
				get_next_path(NULL, 1);
				return (0);
			}
			get_next_path(NULL, 1);
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
		path = ft_join("./", 0, cmd, 1);
		return (path);
	}
	else
	{
		if (errno == EACCES)
			access_exit_code(PERMISSION_DENIED, WRITE);
		else if (errno == ENOENT)
			access_exit_code(NOT_FOUND, WRITE);
		print_err2(cmd, strerror(errno));
		return (NULL);
	}
	return (path);
}

char	*command_path(char *cmd)
{
	char	*path;
	int		c;

	if (is_path(cmd))
		return (is_executable(cmd));
	if (!getenv("PATH"))
		return (is_path_unset(cmd));
	c = check_access(&path, cmd);
	if (0 > c)
		access_exit_code(1, WRITE);
	if (ENOENT == c)
	{
		access_exit_code(NOT_FOUND, WRITE);
		print_err2(cmd, "command not found");
	}
	else if (EACCES == c)
	{
		access_exit_code(PERMISSION_DENIED, WRITE);
		print_err2(path, strerror(errno));
		return (NULL);
	}
	return (path);
}
