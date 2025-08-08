/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_path2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aid-bray <aid-bray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 02:55:16 by mouahman          #+#    #+#             */
/*   Updated: 2025/08/06 11:04:20 by aid-bray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/executor.h"

int	is_dir(char *name, mode_t f_type)
{
	if (S_ISDIR(f_type))
	{
		print_err2(name, "Is a directory");
		access_exit_code(126, WRITE);
		return (1);
	}
	return (0);
}

int	is_path(char *cmd)
{
	if (!ft_strncmp(cmd, "./", 2) || ft_strchr(cmd, '/'))
		return (1);
	return (0);
}

int	get_file_type(char *__file_path, mode_t *file_type)
{
	struct stat	buf;
	int			c;

	*file_type = 0;
	c = stat(__file_path, &buf);
	if (0 > c)
	{
		access_exit_code(1, WRITE);
		perror("stat");
		return (-1);
	}
	*file_type = buf.st_mode;
	return (0);
}

char	*is_executable(char *__pathname)
{
	mode_t	file_type;

	if (!access(__pathname, F_OK))
	{
		if (get_file_type(__pathname, &file_type))
			return (NULL);
		if (is_dir(__pathname, file_type))
			return (NULL);
		else if (access(__pathname, X_OK))
		{
			print_err2(__pathname, strerror(errno));
			access_exit_code(126, WRITE);
			return (NULL);
		}
		return (__pathname);
	}
	print_err2(__pathname, strerror(errno));
	access_exit_code(127, WRITE);
	return (NULL);
}
