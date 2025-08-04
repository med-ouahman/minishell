/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_path2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 02:55:16 by mouahman          #+#    #+#             */
/*   Updated: 2025/07/31 02:55:19 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/executor.h"

int	is_path(char *cmd)
{
	if (!ft_strncmp(cmd, "./", 2) || ft_strchr(cmd, '/'))
		return (1);
	if (*cmd == '/')
		return (1);
	return (0);
}

static mode_t	get_file_type(char *__file_path)
{
	struct stat	buf;
	int			c;

	c = stat(__file_path, &buf);
	if (0 > c)
	{
		access_exit_code(1, WRITE);
		print_err1(strerror(errno));
	}
	return (buf.st_mode);
}

int	is_executable(char *__pathname)
{
	int	file_type;

	if (!access(__pathname, F_OK))
	{
		file_type = get_file_type(__pathname);
		if (access_exit_code(0, READ))
			return (-1);
		if (S_ISDIR(file_type))
		{
			print_err2(__pathname, "Is a directory");
			access_exit_code(126, WRITE);
			return (-1);
		}
		else if (access(__pathname, X_OK))
		{
			print_err2(__pathname, "Permission denied");
			access_exit_code(126, WRITE);
			return (-1);
		}
		return (0);
	}
	print_err2(__pathname, strerror(errno));
	access_exit_code(127, WRITE);
	return (errno);
}
