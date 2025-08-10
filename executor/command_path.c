/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aid-bray <aid-bray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:02:54 by mouahman          #+#    #+#             */
/*   Updated: 2025/08/09 14:18:58 by aid-bray         ###   ########.fr       */
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

static int	check_access(char **path, char *cmd)
{
	char	*save;
	char	*next_path;
	int		c;

	save = NULL;
	*path = NULL;
	if (!*cmd || (access(cmd, F_OK) == 0 && !is_regular(cmd)))
		return (ENOENT);
	next_path = get_next_path(getpath(0), 0);
	while (next_path)
	{
		c = fill_path(path, next_path, cmd);
		if (!c)
		{
			collect_malloc(save, DELETE);
			return (0);
		}
		if (c == EACCES)
			save_path(&save, *path);
		collect_malloc(*path, DELETE);
		*path = NULL;
		next_path = get_next_path(getpath(1), 0);
	}
	get_next_path(NULL, 1);
	return (access_denied(save, path));
}

static	char	*is_path_unset(char *cmd)
{
	char	*path;
	mode_t	ftype;

	if (access(cmd, F_OK | X_OK) == 0)
	{
		if (get_file_type(cmd, &ftype))
			return (NULL);
		if (is_dir(cmd, ftype))
			return (NULL);
		path = ft_join("./", 0, cmd, 1);
		return (path);
	}
	else
	{
		if (errno == EACCES)
			access_exit_code(PERMISSION_DENIED, WRITE);
		else if (errno == ENOENT)
			access_exit_code(NOT_FOUND, WRITE);
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
		print_err2(path, strerror(c));
		return (NULL);
	}
	return (path);
}
