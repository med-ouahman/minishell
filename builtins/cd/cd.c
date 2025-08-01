/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 11:51:06 by mouahman          #+#    #+#             */
/*   Updated: 2025/06/27 13:30:12 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

static int	change_pwd(char *new_val, char *key)
{
	t_uint	i;
	t_uint	len;

	i = 0;
	if (!new_val && ENOMEM == errno)
		collect_malloc(NULL, DESTROY);
	if (!new_val)
	{
		print_err2("cd", strerror(errno));
		return (1);
	}
	collect_malloc(new_val, ENV_CHECK);
	len = ft_strlen(key);
	while (__environ[i] && ft_strncmp(__environ[i], key, len))
		i++;
	if (__environ[i] == NULL)
		return (0);
	collect_malloc(__environ[i], ENV_DELETE);
	__environ[i] = ft_strjoin(key, new_val);
	collect_malloc(__environ[i], ENV_CHECK);
	return (0);
}

static int	change_dir(char *dirname)
{
	if (change_pwd(getcwd(NULL, 0), "OLDPWD="))
		return (1);
	if (chdir(dirname))
	{
		print_err2("cd", strerror(errno));
		return (1);
	}
	if (change_pwd(getcwd(NULL, 0), "PWD="))
		return (1);
	return (0);
}

int	cd(char **args)
{
	if (args[1] == NULL)
	{
		print_err2("cd", "too few arguments");
		return (1);
	}
	if (args[2] != NULL)
	{
		print_file_error("cd", "too many arguments");
		return (1);
	}
	return (change_dir(args[1]));
}
