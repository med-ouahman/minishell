/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_path3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 12:00:25 by mouahman          #+#    #+#             */
/*   Updated: 2025/08/10 12:01:22 by mouahman         ###   ########.fr       */
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

int	fill_path(char **path, char *try_path, char *cmd)
{
	mode_t	ftype;

	*path = join_paths(try_path, cmd);
	if (!access(*path, F_OK))
	{
		get_file_type(*path, &ftype);
		if (!S_ISREG(ftype))
			return (ENOENT);
	}
	if (!access(*path, F_OK))
	{
		if (!access(*path, X_OK))
		{
			get_next_path(NULL, 1);
			return (0);
		}
		return (errno);
	}
	return (errno);
}

int	save_path(char **save, char *path, int c)
{
	static int	err;

	if (!save && !path)
		return (err);
	if (c != -1 && !err)
		err = c;
	if (*save)
		return (err);
	*save = ft_strdup(path);
	collect_malloc(*save, CHECK);
	return (err);
}

int	access_denied(char *save, char **path)
{
	if (save)
	{
		*path = save;
		return (save_path(NULL, NULL, -1));
	}
	collect_malloc(save, DELETE);
	return (errno);
}
